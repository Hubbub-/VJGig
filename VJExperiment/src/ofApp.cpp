#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetVerticalSync(true);
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    // print input ports to console
    midiIn.listPorts(); // via instance
    //ofxMidiIn::listPorts(); // via static as well
    
    // open port by number (you may need to change this)
    midiIn.openPort(1);
    //midiIn.openPort("IAC Pure Data In");	// by name
    //midiIn.openVirtualPort("ofxMidiIn Input"); // open a virtual port
    
    // don't ignore sysex, timing, & active sense messages,
    // these are ignored by default
    midiIn.ignoreTypes(false, false, false);
    
    // add ofApp as a listener
    midiIn.addListener(this);
    
    // print received messages to the console
    midiIn.setVerbose(true);
    
    ofSoundStreamSetup(0, 1, this, 44100, beat.getBufferSize(), 4);
    
    kickHit = false;
    snareHit = false;
    cymbalHit = false;
    
    ofBackground(0,0,0,0);
    
    shape01.setup();
    shape02.setup();
    shape03.setup();
    
    guiGroup.setName("CONTROLS");
    guiGroup.add(shape01.shapeParams);
    guiGroup.add(shape02.shapeParams);
    guiGroup.add(shape03.shapeParams);
    
    
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
    post.createPass<PixelatePass>()->setEnabled(false);
    post.createPass<GodRaysPass>()->setEnabled(false);
    post.createPass<ContrastPass>()->setEnabled(false);
    post.createPass<FakeSSSPass>()->setEnabled(false);
    post.createPass<HorizontalTiltShifPass>()->setEnabled(false);
    //post.createPass<LUTPass>()->setEnabled(false);
    post.createPass<RGBShiftPass>()->setEnabled(false);
    post.createPass<RimHighlightingPass>()->setEnabled(false);
    post.createPass<ZoomBlurPass>()->setEnabled(false);
    post.createPass<SSAOPass>()->setEnabled(false);
    

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
    shape03.update();
    
    //drum hit bools
    if (beat.kick() > 0) {
        shape01.expanding = true;
        shape02.expanding = true;
        //cout << "Kick "<< endl;
    }
    
    if (beat.snare() > 0) {
        shape02.expanding = true;
        snareHit = true;
        //cout << "Snare "<< endl;
    }
    
    if (beat.hihat() > 0) {
        shape03.expanding = true;
        cymbalHit = true;
        //cout << "Hat "<< endl;
    }

    postChainToggle();
}

//--------------------------------------------------------------
void ofApp::draw(){
    // begin scene to post process
    post.begin();
    shape01.draw();
    shape02.draw();
    shape03.draw();
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
    // clean up
    midiIn.closePort();
    midiIn.removeListener(this);
}

//--------------------------------------------------------------
void ofApp::newMidiMessage(ofxMidiMessage& msg) {
    
    // make a copy of the latest message
    midiMessage = msg;
}

//--------------------------------------------------------------
void ofApp::randomise(){
    shape01.randomise();
    shape02.randomise();
    shape03.randomise();
    for (unsigned i = 0; i < post.size(); i++){
        if(ofRandom(10.0) < 3) post[i]->setEnabled(true);
        else post[i]->setEnabled(false);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    unsigned idx = key - '0';
    if (idx < post.size()) post[idx]->setEnabled(!post[idx]->getEnabled());
    
    if (key == 'r') randomise();
}

//--------------------------------------------------------------
void ofApp::postChainToggle() {
    
    //cout << ofxMidiMessage::getStatusString(midiMessage.status) << endl;
    //cout << "pitch: " << midiMessage.pitch;
    
    if (ofxMidiMessage::getStatusString(midiMessage.status) == "Note On"){
    
        if (midiMessage.pitch == 9) {
            cout << "Toggle: 1" << endl;
            for (unsigned i = 0; i < post.size(); i++){
                post[i]->setEnabled(false);
            }
            post[0]->setEnabled(true);
            post[1]->setEnabled(true);
            post[3]->setEnabled(true);
            post[4]->setEnabled(true);
            post[5]->setEnabled(true);
            post[6]->setEnabled(true);
        }
        else if (midiMessage.pitch == 10) {
            cout << "Toggle: 2" << endl;
            for (unsigned i = 0; i < post.size(); i++){
                post[i]->setEnabled(false);
            }
            post[3]->setEnabled(true);
            post[4]->setEnabled(true);
            post[5]->setEnabled(true);
            post[7]->setEnabled(true);

        }
        else if (midiMessage.pitch == 11) {
            cout << "Toggle: 3" << endl;
            for (unsigned i = 0; i < post.size(); i++){
                post[i]->setEnabled(false);
            }
            post[0]->setEnabled(true);
            post[1]->setEnabled(true);
            post[3]->setEnabled(true);
            post[4]->setEnabled(true);
            post[5]->setEnabled(true);
            post[7]->setEnabled(true);

        }
        else if (midiMessage.pitch == 12) {
            cout << "Toggle: 4" << endl;
            for (unsigned i = 0; i < post.size(); i++){
                post[i]->setEnabled(false);
            }
            post[0]->setEnabled(true);
            post[7]->setEnabled(true);
            post[8]->setEnabled(true);
            post[15]->setEnabled(true);
            post[16]->setEnabled(true);

        }
        else if (midiMessage.pitch == 25) {
            cout << "Toggle: 5" << endl;
            for (unsigned i = 0; i < post.size(); i++){
                post[i]->setEnabled(false);
            }
            post[0]->setEnabled(true);
            post[1]->setEnabled(true);
            post[3]->setEnabled(true);
            post[4]->setEnabled(true);
            post[5]->setEnabled(true);
            post[11]->setEnabled(true);
            post[12]->setEnabled(true);
            post[15]->setEnabled(true);
            post[16]->setEnabled(true);

        }
        else if (midiMessage.pitch == 26) {
            cout << "Toggle: 6" << endl;
            for (unsigned i = 0; i < post.size(); i++){
                post[i]->setEnabled(false);
            }
            post[1]->setEnabled(true);
            post[5]->setEnabled(true);
            post[7]->setEnabled(true);
            post[8]->setEnabled(true);
            post[12]->setEnabled(true);
            post[13]->setEnabled(true);
            post[14]->setEnabled(true);
            post[15]->setEnabled(true);

        }
        else if (midiMessage.pitch == 27) {
            cout << "Toggle: 7" << endl;
            for (unsigned i = 0; i < post.size(); i++){
                post[i]->setEnabled(false);
            }
            post[0]->setEnabled(true);
            post[13]->setEnabled(true);
            post[14]->setEnabled(true);
            post[16]->setEnabled(true);

        }
        else if (midiMessage.pitch == 28) {
            cout << "Toggle: 8" << endl;
            for (unsigned i = 0; i < post.size(); i++){
                post[i]->setEnabled(false);
            }
            post[1]->setEnabled(true);
            post[4]->setEnabled(true);
            post[5]->setEnabled(true);
            post[6]->setEnabled(true);
            post[10]->setEnabled(true);
            post[12]->setEnabled(true);
            post[13]->setEnabled(true);
            post[14]->setEnabled(true);
            post[16]->setEnabled(true);
            post[17]->setEnabled(true);

        }
    }
    
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
