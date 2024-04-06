#include <iostream>

#include <map>
#include <string>
#include <vector>

#include <opencv2/opencv.hpp>

#include <detector/detector.hpp>

#define BUTTON_ESC 27
#define BUTTON_SPACE 32

using Contour = std::vector<cv::Point>;
using pointMat = std::vector<Contour>;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage:\n\n\t./detector <video>\n\n";
        exit(-1);
    }

    std::string windowName(argv[1]);

    cv::VideoCapture video(windowName);
    cv::Mat frameFromVideo, gsFrame;
    std::map<int, Contour> nuts;
    std::map<int, cv::Rect> nutsBboxes;
    std::vector<cv::Vec4i> hierarchy;
    pointMat contours, contoursExternal;

    int keycode = -1, nutId = -1, yStart = -1, yEnd = -1;

    while (video.read(frameFromVideo)) {
        yStart = frameFromVideo.rows * 0.60;
        yEnd = frameFromVideo.rows * 0.75;

        /* Filter frame binary. */
        nf::filterFrame(frameFromVideo);

        /* Detect and draw contours. */
        cv::cvtColor(frameFromVideo, gsFrame, cv::COLOR_BGR2GRAY);
        nf::detectndrawContours(gsFrame, frameFromVideo, contours);

        /* Update map of nuts. */
        nf::updateMapNuts(contours, nutsBboxes, nuts, nutId, yStart, yEnd);

        /* Draw lines. */
        nf::drawLines(frameFromVideo);

        /* Show frame. */
        cv::imshow(windowName, frameFromVideo);

        /* Process keyboard actions. */
        keycode = cv::waitKey(1);
        if (keycode == BUTTON_ESC) {
            cv::destroyAllWindows();
            break;
        }
    }

    for (auto& c : nuts) {
        std::cout << nf::isSuitable(c.second);
    }
}
