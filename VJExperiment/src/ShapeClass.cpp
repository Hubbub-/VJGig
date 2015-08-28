//
//  ShapeClass.cpp
//  VJTest
//
//  Created by Student on 25/08/15.
//
//

#include "ShapeClass.h"

//--------------------------------------------------------------
void ShapeClass::setup() {
    shapeParams.add(circleRes.set("res", 60, 3, 60));
    shapeParams.add(release.set("release", 0.8, 0.0, 1.0));
    shapeParams.add(size.set("size", 15.0, 0.0, 30.0));
    
    shapeParams.add(posX.set("posX", 0, -900, 900));
    shapeParams.add(posY.set("posY", 0, -900, 900));
    
    shapeParams.add(rotateX.set("rotX", 0.0, -1.0, 1.0));
    shapeParams.add(rotateY.set("rotY", 0.0, -1.0, 1.0));
    shapeParams.add(rotateZ.set("rotZ", 0.0, -1.0, 1.0));
    
    shapeParams.add(red.set("red", 255, 0, 255));
    shapeParams.add(green.set("green", 255, 0, 255));
    shapeParams.add(blue.set("blue", 255, 0, 255));
    shapeParams.add(alpha.set("alpha", 255, 0, 255));
    
}

//--------------------------------------------------------------
void ShapeClass::update() {
    rotationX = rotationX +rotateX;
    rotationY = rotationY +rotateY;
    rotationZ = rotationZ +rotateZ;
    
    if (expanding == true) {
        shapeRad += 10;
        if (shapeRad > size * 10 ) {
            expanding = false;
        }
    }
    
    if (!expanding && shapeRad > 10) {
        shapeRad *= release;
    }
    
}

//--------------------------------------------------------------
void ShapeClass::draw() {
    
    ofPushMatrix();
    
    ofSetCircleResolution(circleRes);
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    ofRotateX(rotationX);
    ofRotateY(rotationY);
    ofRotateZ(rotationZ);
        
    ofSetColor(red, green, blue, alpha);
    ofCircle(posX, posY, shapeRad);

    
    ofPopMatrix();
    
}

//--------------------------------------------------------------
void ShapeClass::randomise(){
    
    circleRes = ofRandom(3.0, 60.0);
    release = ofRandom(1.0);
    size = ofRandom(30.0);
    
    posX = ofRandom(-500.0, 500.0);
    posY = ofRandom(-300.0, 300.0);
    
    rotateX = ofRandom(-1.0, 1.0);
    rotateY = ofRandom(-1.0, 1.0);
    rotateZ = ofRandom(-1.0, 1.0);
    
    red = ofRandom(255);
    green = ofRandom(255);
    blue = ofRandom(255);
    alpha = ofRandom(150, 255);
}





