#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetVerticalSync(true);
    
    ofSoundStreamSetup(0, 1, this, 44100, beat.getBufferSize(), 4);
    
    kickHit = false;
    snareHit = false;
    cymbalHit = false;
    
    ofBackground(0,0,0,0);
    
    shape01.setup();
    shape02.setup();
    
    guiGroup.setName("CONTROLS");
    guiGroup.add(shape01.shapeParams);
    guiGroup.add(shape02.shapeParams);
    
    
    gui.setup(guiGroup);
    gui.add(volume.set("volume", 0.3, 0.0, 0.6));
    gui.add(speed.set("speed", 1.0, -3.0, 3.0));
    
//    player.loadSound("beat.wav");
//    player.setLoop(true);
//    player.play();
    
    // Setup post-processing chain
    post.init(ofGetWidth(), ofGetHeight());
    post.createPass<FxaaPass>()->setEnabled(false);
    post.createPass<LimbDarkeningPass>()->setEnabled(false);
    post.createPass<BloomPass>()->setEnabled(false);
    post.createPass<DofPass>()->setEnabled(true);
    post.createPass<KaleidoscopePass>()->setEnabled(true);
    post.createPass<NoiseWarpPass>()->setEnabled(true);
    post.createPass<BleachBypassPass>()->setEnabled(false);
    post.createPass<EdgePass>()->setEnabled(true);
    post.createPass<VerticalTiltShifPass>()->setEnabled(false);
    
    post.createPass<GodRaysPass>()->setEnabled(false);
    post.createPass<ContrastPass>()->setEnabled(false);
    post.createPass<FakeSSSPass>()->setEnabled(false);
    post.createPass<HorizontalTiltShifPass>()->setEnabled(false);
    
    post.createPass<LUTPass>()->setEnabled(false);
    post.createPass<RGBShiftPass>()->setEnabled(false);
    post.createPass<RimHighlightingPass>()->setEnabled(false);
    post.createPass<ZoomBlurPass>()->setEnabled(false);
    post.createPass<SSAOPass>()->setEnabled(false);
    
    post.createPass<PixelatePass>()->setEnabled(false);

    syphonOut.setName("HubbubVJ");
    

}

//--------------------------------------------------------------
void ofApp::update(){
    
    beat.update(ofGetElapsedTimeMillis());
    //cout << beat.kick() << "," << beat.snare() << "," << beat.hihat() << endl;
    
    ofSoundUpdate();
    player.setVolume(volume);
    player.setSpeed(speed);
    shape01.update();
    shape02.update();
    
    //drum hit bools
    if (beat.kick() > 0) {
        shape01.expanding = true;
        shape02.expanding = true;
        cout << "Kick "<< endl;
    }
    
    if (beat.snare() > 0) {
        snareHit = true;
        cout << "Snare "<< endl;
    }
    
    if (beat.hihat() > 0) {
        cymbalHit = true;
        cout << "Hat "<< endl;
    }
    
    

}

//--------------------------------------------------------------
void ofApp::draw(){
    // begin scene to post process
    post.begin();
    shape01.draw();
    shape02.draw();
    post.end();
    
    syphonOut.publishScreen();
    
    
    
    // draw help
    ofSetColor(0, 255, 255);
    ofDrawBitmapString("Number keys toggle effects, mouse rotates scene", ofGetWidth() -400, 20);

    for (unsigned i = 0; i < post.size(); ++i)
    {
        if (post[i]->getEnabled()) ofSetColor(0, 255, 255);
        else ofSetColor(255, 0, 0);
        ostringstream oss;
        oss << i << ": " << post[i]->getName() << (post[i]->getEnabled()?" (on)":" (off)");
        ofDrawBitmapString(oss.str(), ofGetWidth() -400, 20 * (i + 2));
    }
    
    gui.draw();
}

//--------------------------------------------------------------
void ofApp::audioReceived(float* input, int bufferSize, int nChannels) {
    beat.audioReceived(input, bufferSize, nChannels);
}



//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    unsigned idx = key - '0';
    if (idx < post.size()) post[idx]->setEnabled(!post[idx]->getEnabled());
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
