#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofEnableDepthTest();
    cam.setDistance(8000);
    cam.setFarClip(10000);
    
    // start kinect, open ports
    kin.setupKinect();
    
    // this "linking" should prevent having to pass it in below...
    gst.linkSkeleton(kin.skeleton, kin.activeSkeleton);
    

    
//    generalControls.setName("General Controls");
//    generalControls.add(reset.set("Reset", false));
    
//    audioControls.add(gst.gstControls);
    
//    panel.setup();
//    panel.add(generalControls);
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
    ofTranslate(0, -1250, 0);
    ofRotateX(270);
    plane.draw();
    ofPopMatrix();
    
    // draw the skeleton and the lines
    kin.drawSkeleton();
    gst.drawAudioPaths();
    
    cam.end();
    
//    panel.draw();
    
    ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), 10, 20);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if (key == 'f') ofToggleFullscreen();
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
