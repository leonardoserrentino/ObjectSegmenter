#pragma once
#include <opencv2/opencv.hpp>
#include "ObjectData.h"
#include <vector>

// ObjectSegmenter: A reusable and modular component for object segmentation using OpenCV
class ObjectSegmenter {
public:
    // Constructor
    ObjectSegmenter();

    // Main method: process an input image to detect and annotate objects
    void process(const cv::Mat& input, cv::Mat& output, std::vector<ObjectData>& objects);

private:
    // Internal method: applies grayscale, blur, threshold, morphology
    void preprocess(const cv::Mat& input, cv::Mat& binary);
};
