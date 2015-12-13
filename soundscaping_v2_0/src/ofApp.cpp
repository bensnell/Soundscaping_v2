#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSetFrameRate(60);
    
    // start kinect, open ports
    kin.setupKinect();
    
    // this "linking" should prevent having to pass it in below...
    gst.linkSkeleton(kin.skeleton, kin.activeSkeleton);
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
    
    ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), 10, 20);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
