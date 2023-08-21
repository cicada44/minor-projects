#include <detector/detector.hpp>

#include <opencv2/opencv.hpp>

#include <iostream>

namespace nf {

cv::Scalar RED(0, 0, 255);
cv::Scalar GREEN(0, 255, 0);

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
    cv::Mat croppedFrame = frame(cv::Range(hei_start, hei_end),
                                 cv::Range(size.width * 0.3, size.width * 0.7));
    return croppedFrame;
}

void filterFrame(cv::Mat& frame) {
    cv::GaussianBlur(frame, frame, {5, 5}, 0);
    cv::threshold(frame, frame, 100, 255, cv::THRESH_BINARY_INV);
}

void detectndrawContours(cv::Mat& gsFrame, cv::Mat& frame, pointMat& contours) {
    cv::findContours(gsFrame, contours, cv::RETR_EXTERNAL,
                     cv::CHAIN_APPROX_SIMPLE);
    cv::drawContours(frame, contours, -1, nf::RED, 3);
}

bool isIntersect(const cv::Rect& bbox1, const cv::Rect& bbox2) {
    int x1 = bbox1.x, y1 = bbox1.y, x2 = bbox2.x, y2 = bbox2.y;
    return (x1 < x2 + bbox2.width && x1 + bbox1.width > x2 &&
            y1 < y2 + bbox2.height && y1 + bbox1.height > y2);
}

void updateBboxMap(pointMat& contours, std::map<int, cv::Rect>& nutsBboxes,
                   int& nutId, const int yStart, const int yEnd) {
    cv::Rect bbox;
    for (const auto& contour : contours) {
        nutId = NUT_NONE_ID;
        bbox = cv::boundingRect(contour);
        int y2 = bbox.y + bbox.height;

        /* Update id of nut. */
        for (const auto& nutBbox : nutsBboxes) {
            if (nf::isIntersect(bbox, nutBbox.second)) {
                nutId = nutBbox.first;
                nutsBboxes[nutId] = bbox;
            }
        }

        /* Add new nut to map. */
        if (y2 > yStart + OFFSET_NUTS_DETECTION &&
            y2 < yEnd - OFFSET_NUTS_DETECTION && nutId == NUT_NONE_ID) {
            nutId = nutsBboxes.size();
            nutsBboxes[nutId] = bbox;
        }
    }
}

}  // namespace nf
