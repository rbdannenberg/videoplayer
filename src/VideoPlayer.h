//
//  VideoPlayer.h
//  videoplayer
//
//  Created by Roger Dannenberg on 1/27/17.
//
//

#ifndef VideoPlayer_h
#define VideoPlayer_h

class VideoPlayer: public ofVideoPlayer {
public:
    string filename;
    float actualWidth;     // "natural" size of video
    float actualHeight;
    float dispWidth;       // requested display size of video
    float dispHeight;
    float dispX;           // requested display location
    float dispY;
    bool hidden;
    VideoPlayer();
    void load(const char *file);
    // setSize controls the draw size. It can be set on-the-fly, but it must
    //    be set *after* load(). The load() method will effectively setSize()
    //    to the "natural" full-size dimensions of the loaded video.
    void setSize(float width, float height);
    void setPosition(float x, float y);
    void draw(); // overrides draw in ofVideoPlayer!
    void hide(bool flag);
};

#endif /* VideoPlayer_h */
