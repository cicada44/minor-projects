# Cameo

Cameo is a C++ application for controlling and displaying camera frames and handling events on them.

## Usage

Follow this steps:

### Build & Run

    make && make run

## Features

- **ESC**: Close application.
- **TAB**: Start/stop writing video.
- **Space**: Write image.
- **'m'**: Set/unset frames to mirrored state.

## Components

- `WindowManager` - manages capturing window
- `CaptureManager` - manages captured slides
