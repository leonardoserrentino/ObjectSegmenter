#pragma once
#include <opencv2/opencv.hpp>

// Structure to store geometric and positional information for each segmented object
struct ObjectData {
    int id;                    // Unique object ID (index)
    cv::Point centroid;        // Centroid of the contour
    cv::Rect boundingBox;      // Bounding box of the object
    double area;               // Area of the contour in pixels
    double perimeter;          // Perimeter length of the contour
};
