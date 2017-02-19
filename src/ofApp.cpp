#include "ofMain.h"
#include "VideoPlayer.h"
#include "ofApp.h"
#include "o2.h"

void ofApp::video_count(int n)
{
    for (std::vector<VideoPlayer *>::iterator it = vplist.begin();
         it < vplist.end(); it++) {
        delete *it;
    }
    vplist.resize(n);
    for (std::vector<VideoPlayer *>::iterator it = vplist.begin();
         it < vplist.end(); it++) {
        *it = new VideoPlayer();
    }
}

void ofApp::video_hide(int n)
{
    //check n is in bounds
    if (n >= 0 && n < vplist.size()) {
        //hide the video
        vplist[n]->hide(true);
    }
    
}

void ofApp::video_stop(int n)
{
    //check n is in bounds
    if (n >= 0 && n < vplist.size()){
        //freezes the frame
        vplist[n]->setPaused(true);
    }
}

void ofApp::video_prepare(int id, const char *filename,
                          double x, double y,
                          double width, double height)
{
    if (id < 0 || id >= vplist.size()) {
        return;
    }
    vplist[id]->load(filename);
    vplist[id]->setSize(width, height);
    vplist[id]->setPosition(x, y);
    vplist[id]->hide(true);
}


void count_handler(const o2_msg_data_ptr msg, const char *types,
                   o2_arg_ptr *argv, int argc, void *user_data)
{
    ofApp *app = (ofApp *) user_data;
    cout << "o2 says: video_count " << argv[0]->i << endl;
    app->video_count(argv[0]->i);
}


//--------------------------------------------------------------
void ofApp::setup()
{
	ofBackground(255,255,255);
	ofSetVerticalSync(true);

    // set up O2:
    o2_initialize("o2app");
    o2_service_new("videoplayer");
    o2_method_new ("/videoplayer/count", "i", &count_handler, this, true, true);

    // the following is here for testing, not part of the final server

    video_count(2);

    VideoPlayer *vpmovie1 = vplist[0];
    VideoPlayer *vpmovie2 = vplist[1];

	// Uncomment this to show movies with alpha channels
	// vplist[0]->setPixelFormat(OF_PIXELS_RGBA);

    video_prepare(0, "movies/7D#5aV_METRONOMESf.mov", 20, 20, 320, 320);
    vpmovie1->hide(false);
	vpmovie1->setLoopState(OF_LOOP_NORMAL);
	vpmovie1->play();

    video_prepare(1, "movies/fingers.mov", 360, 20, 320, 320);
    vpmovie2->hide(false);
    vpmovie2->setLoopState(OF_LOOP_NORMAL);
    vpmovie2->play();


    cout << "vpmovie1 Width: " << vplist[0]->getWidth() << " Height: " << vplist[0]->getHeight() << endl;
    cout << "vpmovie2 Width: " << vplist[1]->getWidth() << " Height: " << vplist[1]->getHeight() << endl;
}

//--------------------------------------------------------------
void ofApp::update()
{
    for (std::vector<VideoPlayer *>::iterator it = vplist.begin();
         it < vplist.end(); it++) {
        (*it)->update();
    }
    o2_poll();
}

//--------------------------------------------------------------
void ofApp::draw()
{

	ofSetHexColor(0xFFFFFF);

    for (std::vector<VideoPlayer *>::iterator it = vplist.begin();
         it < vplist.end(); it++) {
        (*it)->draw();
    }
    /*
    ofSetHexColor(0x000000);
    ofPixels & pixels = vplist[0]->getPixels();

    int vidWidth = pixels.getWidth();
    int vidHeight = pixels.getHeight();
    int nChannels = pixels.getNumChannels();
    
    // let's move through the "RGB(A)" char array
    // using the red pixel to control the size of a circle.
    for (int i = 4; i < vidWidth; i+=8){
        for (int j = 4; j < vidHeight; j+=8){
            unsigned char r = pixels[(j * 320 + i)*nChannels];
            float val = 1 - ((float)r / 255.0f);
			ofDrawCircle(400 + i,20+j,10*val);
        }
    }


    ofSetHexColor(0x000000);
	ofDrawBitmapString("press f to change",20,320);
    if(frameByframe) ofSetHexColor(0xCCCCCC);
    ofDrawBitmapString("mouse speed position",20,340);
    if(!frameByframe) ofSetHexColor(0xCCCCCC); else ofSetHexColor(0x000000);
    ofDrawBitmapString("keys <- -> frame by frame " ,190,340);
    ofSetHexColor(0x000000);

    ofDrawBitmapString("frame: " + ofToString(vplist[0]->getCurrentFrame()) + "/"+ofToString(vplist[0]->getTotalNumFrames()),20,380);
    ofDrawBitmapString("duration: " + ofToString(vplist[0]->getPosition()*vplist[0]->getDuration(),2) + "/"+ofToString(vplist[0]->getDuration(),2),20,400);
    ofDrawBitmapString("speed: " + ofToString(vplist[0]->getSpeed(),2),20,420);

    if(vplist[0]->getIsMovieDone()){
        ofSetHexColor(0xFF0000);
        ofDrawBitmapString("end of movie",20,440);
    }
     */
}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key)
{
    if (vplist.size() == 0) {
        return;
    }
    switch (key) {
        case 'H':
            video_hide(0);
            break;
        case 'h':
            vplist[0]->hide(false);
            break;
        case 'M':
            vplist[0]->setPosition(30, 100);
            break;
        case 'm':
            vplist[0]->setPosition(20, 20);
            break;
        case 'F':
            video_stop(0);
            break;
        case 'f':
            vplist[0]->setPaused(false);
            break;
        case OF_KEY_LEFT:
            vplist[0]->previousFrame();
            break;
        case OF_KEY_RIGHT:
            vplist[0]->nextFrame();
            break;
        case '0':
            vplist[0]->firstFrame();
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
{
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{    
    
}


//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{

}
