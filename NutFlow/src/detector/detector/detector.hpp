#pragma once

#include <vector>

#include <opencv2/opencv.hpp>

namespace nf {

#define RATIO_BL_START 0.65
#define RATIO_BL_END 0.75

/* Colors. */
extern cv::Scalar RED;

/**
 * @brief Draws two bounding lines on frame.
 * @param frame frame to draw.
 */
void drawLines(cv::Mat& frame);

/**
 * @brief Crops frame along bounding lines.
 * @param frame frame to crop.
 * @return cv::Mat cropped frame.
 */
cv::Mat cropForLines(cv::Mat& frame);

/**
 * @brief Filters frame to detect nuts.
 * @param frame frame to filter.
 */
void filterFrame(cv::Mat& frame);

/**
 * @brief Detects and draws contours on frame.
 * @param gsFrame grayscale frame for contours detection.
 * @param frame frame for draw contours.
 * @param contours contours to draw.
 */
void detectndrawContours(cv::Mat& gsFrame, cv::Mat& frame, std::vector<std::vector<cv::Point>>& contours);

}  // namespace nf
