# Cameo

Cameo is a Python3 project that captures video frames from a webcam using OpenCV and provides functionality to take screenshots and record screencasts.

## Files

- cameo.py
- main.py
- managers.py

## Usage

To run the Cameo application, execute the following command:

    python main.py


When the application is running, it will display the webcam feed in a window. You can perform the following actions:

- Press the spacebar to take a screenshot. The screenshot will be saved as "screenshot.png" in the current directory.
- Press the tab key to start/stop recording a screencast. The screencast will be saved as "screenvideo.avi" in the current directory.
- Press the escape key to quit the application.

## Code Structure

The project consists of the following files:

- `cameo.py`: Contains the main class `Cameo` that handles webcam capturing, frame processing, and user input handling.
- `main.py`: The entry point of the application. It creates an instance of the `Cameo` class and runs the main loop.
- `managers.py`: Defines the `CaptureManager` and `WindowManager` classes used by the `Cameo` class for managing video capturing and window management.
