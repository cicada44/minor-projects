#include <detector/detector.hpp>

#include <opencv2/opencv.hpp>

#include <iostream>

namespace nf {

cv::Scalar RED(0, 0, 255);

void drawLines(cv::Mat& frame) {
    cv::Size size = frame.size();
    int hei_end = size.height * RATIO_BL_END;
    int hei_start = size.height * RATIO_BL_START;
    cv::line(frame, {0, hei_start}, {size.width, hei_start}, RED, 3);
    cv::line(frame, {0, hei_end}, {size.width, hei_end}, RED, 3);
}

cv::Mat cropForLines(cv::Mat& frame) {
    cv::Size size = frame.size();
    int hei_end = size.height * RATIO_BL_END;
    int hei_start = size.height * RATIO_BL_START;
    cv::Mat croppedFrame = frame(cv::Range(hei_start, hei_end), cv::Range(size.width * 0.3, size.width * 0.7));
    return croppedFrame;
}

void filterFrame(cv::Mat& frame) {
    frame = nf::cropForLines(frame);
    cv::GaussianBlur(frame, frame, {5, 5}, 0);
    cv::threshold(frame, frame, 100, 255, cv::THRESH_BINARY);
}

void detectndrawContours(cv::Mat& gsFrame, cv::Mat& frame, std::vector<std::vector<cv::Point>> &contours) {
    cv::findContours(gsFrame, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);
    cv::drawContours(frame, contours, -1, nf::RED, 3);
}

}  // namespace nf
