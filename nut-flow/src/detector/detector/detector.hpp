#pragma once

#include <map>
#include <vector>

#include <opencv2/opencv.hpp>

namespace nf {

using Contour = std::vector<cv::Point>;
using pointMat = std::vector<Contour>;

#define RATIO_BL_START 0.65
#define RATIO_BL_END 0.75

#define NUT_NONE_ID -1

#define OFFSET_NUTS_DETECTION 12

/* Colors. */
extern cv::Scalar RED;
extern cv::Scalar GREEN;

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
void detectndrawContours(cv::Mat& gsFrame, cv::Mat& frame, pointMat& contours);

/**
 * @brief Finds intersention of 2 cv::Rect objects.
 * @param r1 First rectangle.
 * @param r2 Second rectangle.
 * @return true if there is an intersection.
 * @return false if there isn't an intersection.
 */
bool isIntersect(const cv::Rect& r1, const cv::Rect& r2);

/**
 * @brief Updates maps of contours.
 * @param contours contours in frame.
 * @param extContours map of IDs and contours of nuts.
 * @param nutsBboxes bounding boxes of nuts.
 * @param nutId nut Id for use in map.
 * @param yStart start height position of bounding line.
 * @param yEnd end height position of bounding line.
 */
void updateMapNuts(pointMat& contours, std::map<int, cv::Rect>& nutsBboxes,
                   std::map<int, Contour>& extContours, int& nutId, const int yStart,
                   const int yEnd);

/**
 * @brief Checks is the contour is the nut or not.
 * @param contour Contour of nut.
 * @return true If contour is the nut.
 * @return false If contour isn't the nut.
 */
bool isSuitable(Contour& contour);

}  // namespace nf
