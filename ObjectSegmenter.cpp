#include "ObjectSegmenter.h"

ObjectSegmenter::ObjectSegmenter() {}

// Applies preprocessing to prepare the image for segmentation
void ObjectSegmenter::preprocess(const cv::Mat& input, cv::Mat& binary) {
    cv::Mat gray, blurred;

    // Step 1: Convert input to grayscale
    cv::cvtColor(input, gray, cv::COLOR_BGR2GRAY);

    // Step 2: Apply Gaussian blur to reduce noise and improve thresholding
    cv::GaussianBlur(gray, blurred, cv::Size(5, 5), 0);

    // Step 3: Apply Otsu's thresholding to binarize the image
    cv::threshold(blurred, binary, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);

    // Step 4 (optional): Invert if background is white and objects are black
    int whitePixels = cv::countNonZero(binary);
    if (whitePixels < (binary.cols * binary.rows) / 2) {
        cv::bitwise_not(binary, binary);  // invert so objects are white
    }

    // Step 5: Apply morphological closing to remove small holes and join close regions
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
    cv::morphologyEx(binary, binary, cv::MORPH_CLOSE, kernel);
}

// Detects and analyzes objects in the image
void ObjectSegmenter::process(const cv::Mat& input, cv::Mat& output, std::vector<ObjectData>& objects) {
    cv::Mat binary;
    preprocess(input, binary);

    // Vector of contours and hierarchy (parent/child relationships)
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;

    // Extract external contours only (suitable for counting individual objects)
    cv::findContours(binary, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // Prepare output image and clear the object list
    output = input.clone();
    objects.clear();

    // Iterate over all contours found
    for (size_t i = 0; i < contours.size(); ++i) {
        // Ignore small noise regions (area threshold)
        if (cv::contourArea(contours[i]) < 100.0) continue;

        ObjectData obj;
        obj.id = static_cast<int>(i);                              // assign object index
        obj.boundingBox = cv::boundingRect(contours[i]);           // get bounding box
        obj.area = cv::contourArea(contours[i]);                   // area in pixels
        obj.perimeter = cv::arcLength(contours[i], true);          // closed curve length

        // Calculate centroid from image moments
        cv::Moments M = cv::moments(contours[i]);
        obj.centroid = (M.m00 != 0) ? cv::Point(M.m10 / M.m00, M.m01 / M.m00)
                                    : cv::Point(0, 0);

        // --- Draw diagnostics on the output image ---
        cv::drawContours(output, contours, static_cast<int>(i), cv::Scalar(0, 255, 0), 2);       // green contour
        cv::rectangle(output, obj.boundingBox, cv::Scalar(255, 255, 0), 1);                      // cyan bounding box
        cv::circle(output, obj.centroid, 4, cv::Scalar(0, 0, 255), -1);                          // red centroid
        cv::putText(output, std::to_string(i + 1), obj.centroid + cv::Point(10, 0),
                    cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 0, 0), 1);                    // blue ID label

        // Add to results vector
        objects.push_back(obj);
    }
}
