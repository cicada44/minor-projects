#pragma once

#include <opencv2/opencv.hpp>

#include <string>

namespace Cameo {

class WindowManager {
public:
    WindowManager() = delete;

    WindowManager(const std::string& windowName,
                  const int keypressCallback = -1);

    bool isWindowCreated() const;

    void createWindow();

    void show(const cv::Mat& frame) const;

    void destroyWindow();

    void processEvent();

private:
    int _keypressCallback;
    bool _isWindowCreated;
    std::string _windowName;
};

class CaptureManager {
public:
    CaptureManager(cv::VideoCapture& cam, WindowManager& winManager, const bool shouldMirrored = false);

    int get_channel() const;

    void writeImage(const std::string& imgFilename);

    void set_channel(const int new_channel);

    cv::Mat frame();

    bool isWritingImage() const;
    bool isWritingVideo() const;

    void enterFrame();
    void exitFrame();

    void startWritingVideo(const std::string& filename,
                           int encoding = cv::VideoWriter::fourcc('I', '4', '2',
                                                                  '0'));

    void stopWritingVideo();

private:
    WindowManager _winManager;
    cv::VideoWriter _vidWriter;
    cv::VideoCapture _camera;
    cv::Mat _frame;
    std::time_t _startTime;
    std::string _imgFilename, _vidFilename;
    int _channel, _framesElapled, _fpsEstimate, _vidEncoding;
    bool _enteredFrame, _shouldMirrored;

    void writeVideoFrame();
};

class Cameo {
public:
    Cameo() = delete;

    Cameo(CaptureManager& cM, WindowManager& wM);

    void run();

    void onKeypress(int keycode);

private:
    CaptureManager _captureManager;
    WindowManager _windowManager;
};

}  // namespace Cameo
