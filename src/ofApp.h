#pragma once


class ofApp : public ofBaseApp {
    
public:
    void setup();
    void update();
    void draw();

    // the Server API
    void video_count(int n); // set the number of videos
    void video_hide(int n); //hide the video with id n
    void video_stop(int n); //freeze the video with id n
    void video_prepare(int id, const char *filename,
                       double x, double y,
                       double width, double height);


    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    vector<VideoPlayer *> vplist;
};

