#include <iostream>

#include <vector>

#include <opencv2/opencv.hpp>

#include <detector/detector.hpp>

#define BUTTON_ESC 27
#define BUTTON_SPACE 32

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage:\n\n\t./detector <video>\n\n";
        exit(-1);
    }

    cv::VideoCapture video(argv[1]);
    cv::Mat frameFromVideo, gsFrame;
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;

    int keycode = -1;

    while (video.read(frameFromVideo)) {
        /* Filter frame binary. */
        nf::filterFrame(frameFromVideo);

        /* Detect and draw contours. */
        cv::cvtColor(frameFromVideo, gsFrame, cv::COLOR_BGR2GRAY);
        nf::detectndrawContours(gsFrame, frameFromVideo, contours);

        /* Show frame. */
        cv::imshow(argv[1], frameFromVideo);

        keycode = cv::waitKey(17);
        if (keycode == BUTTON_ESC) {
            cv::destroyAllWindows();
            break;
        }
    }
}
