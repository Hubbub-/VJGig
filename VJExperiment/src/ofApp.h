#pragma once

#include "ofMain.h"
#include "ShapeClass.h"
#include "ofxGui.h"
#include "ofxPostProcessing.h"
#include "ofxBeat.h"
#include "ofxSyphon.h"


class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void randomise();
    void exit();
    
    void audioReceived(float*, int, int);
    
    // scene stuff
    ofxPostProcessing post;
    
    
    bool kickHit;
    bool snareHit;
    bool cymbalHit;
    
    
    ofxSyphonServer syphonOut;
    
    
    
    ofParameter<float> volume;
    ofParameter<float> speed;
    ofParameterGroup guiGroup;
    
    ShapeClass shape01;
    ShapeClass shape02, shape03;
    
    ofSoundPlayer player;
    
    ofxBeat beat;
    
    ofxPanel gui;
    
    
    
};
