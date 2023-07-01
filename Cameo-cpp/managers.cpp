#include <opencv2/opencv.hpp>

#include <string>

class CaptureManager {
public:
private:
};

class WindowManager {
public:
    WindowManager(
            const std::string& windowName,
            const bool isWindowCreated,
            const int keypressCallback = -1)
        : _keypressCallback(keypressCallback),
          _isWindowCreated(isWindowCreated),
          _windowName(windowName)
    {
    }

    bool isWindowCreated()
    {
        return _isWindowCreated;
    }

    void createWindow()
    {
        cv::namedWindow(_windowName);
        _isWindowCreated = true;
    }

    void show(const cv::Mat& frame)
    {
        cv::imshow(_windowName, frame);
    }

    void destroyWindow()
    {
        cv::destroyWindow(_windowName);
        _windowName.clear();
        _isWindowCreated = false;
    }

    void processEvent()
    {
        int keycode = cv::waitKey(1);
        if (_keypressCallback != -1 && keycode != -1) {
            keycode = 0xff;
            _keypressCallback = keycode;
        }
    }

private:
    int _keypressCallback;
    bool _isWindowCreated;
    std::string _windowName;
};

class CaptureManager {
public:
    CaptureManager() :
    {
    }

private:
};
