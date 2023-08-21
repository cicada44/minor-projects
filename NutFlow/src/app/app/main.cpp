#include <iostream>

#include <map>
#include <string>
#include <vector>

#include <opencv2/opencv.hpp>

#include <detector/detector.hpp>

#define BUTTON_ESC 27
#define BUTTON_SPACE 32

using pointMat = std::vector<std::vector<cv::Point>>;
using pairContHier = std::pair<std::vector<cv::Vec4i>, pointMat>;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage:\n\n\t./detector <video>\n\n";
        exit(-1);
    }

    std::string windowName(argv[1]);

    cv::VideoCapture video(windowName);
    cv::Mat frameFromVideo, gsFrame;
    std::map<int, pairContHier> nuts;
    std::map<int, cv::Rect> nutsBboxes;
    pointMat contours;
    std::vector<cv::Vec4i> hierarchy;

    int keycode = -1, nutId = 0, yStart = -1, yEnd = -1;

    while (video.read(frameFromVideo)) {
        yStart = frameFromVideo.rows * 0.65;
        yEnd = frameFromVideo.rows * 0.75;

        /* Filter frame binary. */
        nf::filterFrame(frameFromVideo);

        /* Detect and draw contours. */
        cv::cvtColor(frameFromVideo, gsFrame, cv::COLOR_BGR2GRAY);
        nf::detectndrawContours(gsFrame, frameFromVideo, contours);

        /* Draw lines. */
        nf::drawLines(frameFromVideo);

        /* Show frame. */
        cv::imshow(windowName, frameFromVideo);

        /* Update map of nuts. */
        nf::updateBboxMap(contours, nutsBboxes, nutId, yStart, yEnd);

        std::cout << nutsBboxes.size() << '\n';

        /* Process keyboard actions. */
        keycode = cv::waitKey(17);
        if (keycode == BUTTON_ESC) {
            cv::destroyAllWindows();
            break;
        }
    }
}
