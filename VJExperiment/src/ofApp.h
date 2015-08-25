#pragma once

#include "ofMain.h"
#include "ShapeClass.h"
#include "ofxGui.h"
#include "ofxPostProcessing.h"

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
        void exit();
    
    void audioIn(float * input, int bufferSize, int nChannels);
    
    // scene stuff
    ofxPostProcessing post;
    
    vector <float> left;
    vector <float> right;
    vector <float> volHistory;
    
    int 	bufferCounter;
    int 	drawCounter;
    
    float smoothedVol;
    float scaledVol;
    
    ofParameter<float> volume;
    ofParameter<float> speed;
    ofParameterGroup guiGroup;
    
    ShapeClass shape01;
    
    ofSoundStream soundStream;
    ofSoundPlayer beat;
    
    ofxPanel gui;
    
    
		
};
