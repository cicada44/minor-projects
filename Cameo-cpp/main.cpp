#include <cameo.hpp>
#include <opencv2/opencv.hpp>

int main() {
    cv::VideoCapture videoCap(0);
    Cameo::WindowManager winManager("Cameo");
    Cameo::CaptureManager capManager(videoCap, winManager, false);
    Cameo::Cameo cam{capManager, winManager};

    cam.run();
}
