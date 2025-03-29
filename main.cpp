#include <opencv2/opencv.hpp>
#include "ObjectSegmenter.h"
#include "ObjectData.h"
#include <iostream>

int main() {
    // Load an input image from disk
    cv::Mat img = cv::imread("oggetti.jpg");  // replace with your actual image
    if (img.empty()) {
        std::cerr << "Error: input image not found.\n";
        return -1;
    }

    // Declare the segmentation module and results
    ObjectSegmenter segmenter;
    std::vector<ObjectData> objects;
    cv::Mat output;

    // Run the object segmentation process
    segmenter.process(img, output, objects);

    std::cout << "Detected " << objects.size() << " object(s).\n";

    // Print analysis data for each object
    for (const auto& obj : objects) {
        std::cout << "Object " << obj.id
                  << " | Area: " << obj.area
                  << " | Perimeter: " << obj.perimeter
                  << " | Centroid: (" << obj.centroid.x << "," << obj.centroid.y << ")\n";
    }

    // Display result
    cv::imshow("Segmented Output", output);
    cv::waitKey(0);
    return 0;
}
