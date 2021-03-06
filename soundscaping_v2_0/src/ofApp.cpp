#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofEnableDepthTest();
    cam.setDistance(8000);
    cam.setFarClip(20000);
    
    // start kinect, open ports
    kin.setupKinect();
    
    // this "linking" should prevent having to pass it in below...
    gst.linkSkeleton(kin.skeleton, kin.activeSkeleton);
    

    
    generalControls.setName("General Controls");
    generalControls.add(reset.set("Reset", false));
//    generalControls.add(bset.set("what", 0., 0., 1.));
//    generalControls.add(myButton.setup("Rese the system"));
    
//    audioControls.add(gst.gstControls);
    panel.setup();
    panel.add(generalControls);

//    panel.add(audioControls);
    
    plane.set(4000., 4000.);
    plane.setPosition(0, 0, 0);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    // request all joints from max every 2 sec
    kin.requestAllJoints(2);
    
    // update the physics and hits of all joints
    kin.updateAllJoints();
    
    // re-evaluate the state of the skeleton / joints (actively being tracked?)
    kin.updateState();
    
    // process gestures and notify max of begin / end of recording
    gst.processSkeleton(kin.skeleton, kin.activeSkeleton);
    
    // update spatialized audio --> send to max volume levels for each buffer
    gst.playLineSpace(kin.skeleton, kin.activeSkeleton);
    

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
    cam.begin();
    
    ofPushMatrix();
    ofSetColor(100);
    ofTranslate(0, -1250, 2000);
    ofRotateY(10. * sin((double)(ofGetElapsedTimeMillis() / 5000.)));
    ofRotateX(270);
    plane.draw();
    ofPopMatrix();
    
    ofPushMatrix();
    ofSetColor(200);
    ofTranslate(-200, 0, 0);
    ofRotateY(10. * sin((double)(ofGetElapsedTimeMillis() / 5000.)));
//    ofRotateX(270);
    ofRect(0, 0, 200, 200);
    ofPopMatrix();

    
    ofPushMatrix();
    ofRotateY(10. * sin((double)(ofGetElapsedTimeMillis() / 5000.)));
    
    // draw the skeleton and the lines
    kin.drawSkeleton();
    
    if (gst.recordingState) {
        ofSetColor(255, 0, 0);
    } else {
        ofSetColor(255);
    }
    ofCircle(kin.skeleton["righthand"].position, 40);
    
    gst.drawAudioPaths();
    
    ofPopMatrix();

    
    
    cam.end();
    
//    panel.draw();
    
    ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), 10, 20);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if (key == 'f') ofToggleFullscreen();
    
    // reset the system
    if (key == 'r') {
        gst.resetSystem();
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
