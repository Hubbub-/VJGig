//
//  ShapeClass.h
//  VJTest
//
//  Created by Student on 25/08/15.
//
//

#pragma once

#include "ofMain.h"

class ShapeClass {
public:
    void setup();
    void draw();
    void update();
    
    ofParameterGroup shapeParams;
    ofParameter<int> circleRes;
    ofParameter<float> release;
    ofParameter<float> size;
    
    ofParameter<int> posX;
    ofParameter<int> posY;
    
    ofParameter<float> rotateX;
    ofParameter<float> rotateY;
    ofParameter<float> rotateZ;
    
    ofParameter<int> red;
    ofParameter<int> green;
    ofParameter<int> blue;
    ofParameter<int> alpha;
    
    float rotationX = 0.0;
    float rotationY = 0.0;
    float rotationZ = 0.0;
    
    float shapeRad = 10.0;
    
    bool expanding = false;
    
//    float * fftSmooth;
//    int bands;
};


