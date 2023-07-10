// -----------------------------------------------------------------------------
//
// Header for CaptureManager, WindowManager and main Cameo classes
//
// -----------------------------------------------------------------------------

#pragma once

#include <opencv2/opencv.hpp>

#include <string>

namespace Cameo {

class WindowManager {
public:
    WindowManager() = delete;

    /* Sets name for controlling window to `windowName`.
     * @param windowName name for named window.
     */
    WindowManager(const std::string& windowName);

    /* @return isWindowCreated parameter. */
    bool isWindowCreated() const;

    /* Creates window with `windowName` name attribute. */
    void createWindow();

    /* Shows `frame` into created window.
     * @param frame showing frame.
     */
    void show(const cv::Mat& frame) const;

    /* Destroys actual window. */
    void destroyWindow();

    /* @return ASCII keycode for pressed button. */
    int getProcessEvent();

private:
    bool _isWindowCreated;
    std::string _windowName;
};

class CaptureManager {
public:
    /* Main constructor.
     * @param cam camera for controlling.
     * @param winManager WindowManager object that controls window.
     * @param shouldMirrored true - if showing frame should be mirrored,
     * otherwise - false (default).
     */
    CaptureManager(cv::VideoCapture& cam, WindowManager& winManager,
                   const bool shouldMirrored = false);

    /* Sets shouldMirrored attribute to shMirrored.
     * @param shMirrored new value for attribute shouldMirrored.
     */
    void set_mirrored(const bool shMirrored);

    /* @return shouldMirrored attribute. */
    bool get_mirrored() const;

    /* @return channel attribute. */
    int get_channel() const;

    /* Writes image with `imgFilename`.
     * @param imgFilename name for image grabbing from camera.
     */
    void writeImage(const std::string& imgFilename);

    /* Sets new value for `channel` attribute.
     * @param new_channel new value for attribute `channel`.
     */
    void set_channel(const int new_channel);

    /* Returns frame retrieved from camera. If there're no frame - exit with
     * code -1.
     * @return cv::Mat frame grabbed from camera.
     */
    cv::Mat frame();

    /* @return isWritingImage attribute. */
    bool isWritingImage() const;

    /* @return isWritingVideo attribute. */
    bool isWritingVideo() const;

    /* Grabbed attribute enteredFrame from camera. */
    void enterFrame();

    /* Process all variables and events when frame is ready to close. */
    void exitFrame();

    /* Starts writing video with filename `filename` and codec `encoding`.
     * @param filename name for output file.
     * @param encoding file codec for video, default - I420.
     */
    void startWritingVideo(const std::string& filename,
                           int encoding = cv::VideoWriter::fourcc('I', '4', '2',
                                                                  '0'));

    /* This do what you think. */
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

    /* Creates `Cameo` with CaptureManager cM and WindowManager wM.
     * @param cM CaptureManager object.
     * @param wM WindowManager object.
     */
    Cameo(CaptureManager& cM, WindowManager& wM);

    /* Runs the application. */
    void run();

private:
    CaptureManager _captureManager;
    WindowManager _windowManager;

    /* Process events happened on keyboard.
     * @param keycode ASCII code of happened event.
     */
    void onKeypress(int keycode);
};

}  // namespace Cameo
