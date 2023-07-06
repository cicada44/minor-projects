
#include <cameo.hpp>

#include <ctime>

#include <string>

#include <iostream>

Cameo::WindowManager::WindowManager(const std::string& windowName,
                                    const int keypressCallback)
    : _keypressCallback(keypressCallback), _windowName(windowName) {}

bool Cameo::WindowManager::isWindowCreated() const { return _isWindowCreated; }

void Cameo::WindowManager::createWindow() {
    cv::namedWindow(_windowName);
    _isWindowCreated = true;
}

void Cameo::WindowManager::show(const cv::Mat& frame) const {
    cv::imshow(_windowName, frame);
}

void Cameo::WindowManager::destroyWindow() {
    cv::destroyWindow(_windowName);
    _windowName.clear();
    _isWindowCreated = false;
}

void Cameo::WindowManager::processEvent() {
    int keycode = cv::waitKey(1);
    if (_keypressCallback != -1 && keycode != -1) {
        keycode = 0xff;
        _keypressCallback = keycode;
    }
}

Cameo::CaptureManager::CaptureManager(cv::VideoCapture& cam,
                                      WindowManager& winManager,
                                      const bool shouldMirrored)
    : _winManager(winManager), _camera(cam), _shouldMirrored(shouldMirrored) {}

int Cameo::CaptureManager::get_channel() const { return _channel; }

void Cameo::CaptureManager::writeImage(const std::string& imgFilename) {
    _imgFilename = imgFilename;
}

void Cameo::CaptureManager::set_channel(const int new_channel) {
    if (_channel != new_channel) {
        _channel = new_channel;
        _frame.release();
    }
}

cv::Mat Cameo::CaptureManager::frame() {
    if (_enteredFrame == false && _frame.empty() == true) {
        if (_camera.retrieve(_frame) == false) {
            std::cerr << "Can't detect camera!" << '\n';
            exit(-1);
        }
        std::cout << "smt wrong with frame\n";
    }

    return _frame;
}

bool Cameo::CaptureManager::isWritingImage() const {
    return !_imgFilename.empty();
}

bool Cameo::CaptureManager::isWritingVideo() const {
    return !_vidFilename.empty();
}

void Cameo::CaptureManager::enterFrame() {
    // CV_Assert(_enteredFrame == false);
    if (_camera.isOpened()) _enteredFrame = _camera.grab();
}

void Cameo::CaptureManager::exitFrame() {
    if (_frame.empty()) {
        _enteredFrame = false;
    } else {
        if (_framesElapled == 0) {
            _startTime = std::time(nullptr);
        } else {
            std::time_t timeElapsed =
                std::difftime(std::time(nullptr), _startTime);
            _fpsEstimate = _framesElapled / timeElapsed;
        }
        ++_framesElapled;

        if (_winManager.isWindowCreated() != false) {
            std::cerr << "window created!\n";
            if (_shouldMirrored) {
                cv::Mat mirroredFrame;
                cv::flip(_frame, mirroredFrame, 1);
                _winManager.show(mirroredFrame);
            } else {
                _winManager.show(_frame);
            }
        } else {
            std::cerr << "window hasn't created\n";
        }

        if (isWritingImage()) {
            cv::imwrite(_imgFilename, _frame);
        }

        writeVideoFrame();

        _frame.release();
        _enteredFrame = false;
    }
}

void Cameo::CaptureManager::startWritingVideo(const std::string& filename,
                                              int encoding) {
    _vidFilename = filename;
    _vidEncoding = encoding;
}

void Cameo::CaptureManager::stopWritingVideo() {
    _vidEncoding = -1;
    _vidFilename.clear();
    _vidWriter.release();
}

void Cameo::CaptureManager::writeVideoFrame() {
    if (isWritingVideo()) {
        if (!_vidWriter.isOpened()) {
            static double fps = _camera.get(cv::CAP_PROP_FPS);
            if (fps == 0.0) {
                if (_framesElapled < 20) {
                    return;
                } else {
                    fps = _fpsEstimate;
                }
            }
            cv::Size winSize(int(_camera.get(cv::CAP_PROP_FRAME_WIDTH)),
                             int(_camera.get(cv::CAP_PROP_FRAME_HEIGHT)));

            _vidWriter =
                cv::VideoWriter(_vidFilename, _vidEncoding, fps, winSize);
        }
        _vidWriter.write(_frame);
    }
}

Cameo::Cameo::Cameo(CaptureManager& cM, WindowManager& wM)
    : _captureManager(cM), _windowManager(wM) {}

void Cameo::Cameo::run() {
    _windowManager.createWindow();
    while (_windowManager.isWindowCreated()) {
        _captureManager.enterFrame();
        std::cout << "Frame ezntered\n";
        cv::Mat frame = _captureManager.frame();
        std::cout << frame.empty() << '\n';
        _captureManager.exitFrame();
        _windowManager.processEvent();
    }
}

void Cameo::Cameo::onKeypress(int keycode) {
    switch (keycode) {
        case 32:
            _captureManager.writeImage("screenshot.png");
            break;

        case 9:
            if (!_captureManager.isWritingVideo())
                _captureManager.startWritingVideo("screenvideo.avi");
            else
                _captureManager.stopWritingVideo();
            break;

        case 27:
            _windowManager.destroyWindow();
            break;

        default:
            break;
    }
}
