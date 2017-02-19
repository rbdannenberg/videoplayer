//
//  VideoPlayer.cpp
//  videoplayer
//
//  Created by Roger Dannenberg on 1/27/17.
//
//  VideoPlayer capabilities:
//     load() -- load from a file
//     setSize()
//     setPosition()
//     draw() -- draw at current location and size
//     hide() -- hide and pause / unhide and unpause video
//     
//
#include "ofMain.h"
#include "VideoPlayer.h"

VideoPlayer::VideoPlayer() : ofVideoPlayer() {
    filename = "";
    dispX = 0;
    dispY = 0;
    hidden = false;
    // dispWidth and dispHeight get set when video is loaded
}

void VideoPlayer::load(const char *file)
{
    if (filename.compare(file) == 0) {
        return; // file is already loaded
    }
    filename = file; // coerce to string and save it
    ofVideoPlayer::load(file);
    // default is draw at normal size
    dispWidth = actualWidth = getWidth();
    dispHeight = actualHeight = getHeight();
}

void VideoPlayer::setSize(float width, float height)
{
    dispWidth = width;
    dispHeight = height;
}

void VideoPlayer::setPosition(float x, float y)
{
    dispX = x;
    dispY = y;
}

void VideoPlayer::draw()
{
    if (!hidden) {
        ofVideoPlayer::draw(dispX, dispY, dispWidth, dispHeight);
    }
}

void VideoPlayer::hide(bool flag)
{
    hidden = flag;
    setPaused(flag);
}



