#include <cameo.hpp>

#include <ctime>

#include <string>

#include <iostream>

Cameo::WindowManager::WindowManager(const std::string& windowName)
    : _windowName(windowName) {}

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

int Cameo::WindowManager::getProcessEvent() { return cv::waitKey(1); }

Cameo::CaptureManager::CaptureManager(cv::VideoCapture& cam,
                                      WindowManager& winManager,
                                      const bool shouldMirrored)
    : _winManager(winManager), _camera(cam), _shouldMirrored(shouldMirrored) {}

void Cameo::CaptureManager::set_mirrored(const bool shMirrored) {
    _shouldMirrored = shMirrored;
}

bool Cameo::CaptureManager::get_mirrored() const { return _shouldMirrored; }

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
    if (_enteredFrame == true) {
        if (_camera.retrieve(_frame) == false) {
            exit(-1);
        }
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
            if (timeElapsed != 0) _fpsEstimate = _framesElapled / timeElapsed;
        }
        ++_framesElapled;

        if (_winManager.isWindowCreated()) {
            if (_shouldMirrored) {
                cv::Mat mirroredFrame;
                cv::flip(_frame, mirroredFrame, 1);
                _winManager.show(mirroredFrame);
            } else {
                _winManager.show(_frame);
            }
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
        cv::Mat frame = _captureManager.frame();
        _captureManager.exitFrame();
        onKeypress(_windowManager.getProcessEvent());
    }
}

void Cameo::Cameo::onKeypress(int keycode) {
    switch (keycode) {
        case 32: /* Space. */
            _captureManager.writeImage("screenshot.png");
            break;

        case 9: /* Tab. */
            if (!_captureManager.isWritingVideo())
                _captureManager.startWritingVideo("screenvideo.avi");
            else
                _captureManager.stopWritingVideo();
            break;

        case 27: /* Escape. */
            _windowManager.destroyWindow();
            break;

        case 109: /* 'm' key. */
            (_captureManager.get_mirrored() == true)
                ? _captureManager.set_mirrored(false)
                : _captureManager.set_mirrored(true);
            break;

        default:
            break;
    }
}
