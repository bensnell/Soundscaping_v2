//
//  kinectOsc.cpp
//  soundscaping_v2_0
//
//  Created by Ben Snell on 12/2/15.
//
//

#include "kinectOsc.h"

// constructor
kinectRecorder::kinectRecorder() {
    
    // setup all joints
    for (int i = 0; i < 15; i++) {
        skeleton[jointNames[i]] = joint();
    }
}

// --------------------------------------------------------------------

// setup the OSC receivers and senders for communicating with the kinect
void kinectRecorder::setupKinect() {
    
    receiver.setup(synapseIn);
    
    sender.setup("localhost", synapseOut);
}

// --------------------------------------------------------------------

// update all of the joints
void kinectRecorder::updateAllJoints() {
    
    // retrieve the waiting messages
    while (receiver.hasWaitingMessages()) {
        
        // get the message
        ofxOscMessage msg;
        receiver.getNextMessage(&msg);
        
        // check for which joint has been received
        string thisAddress = msg.getAddress();
    
        // remove beginning "/" and anything after first "_"
        int endIndex = thisAddress.find_first_of('_') - 1;
        string jointName = thisAddress.substr(1, endIndex);
        
        // only continue if joint exists
        if (skeleton.find(jointName) == skeleton.end()) continue;

        // find type of first argument
        ofxOscArgType thisType = msg.getArgType(0);
        
        // update the hits or physics depending on the type
        if (thisType == OFXOSC_TYPE_STRING) { // hits
            
            string hitDirection = msg.getArgAsString(0);
            
            skeleton[jointName].hits[hitDirection] = true;
            
        } else if (thisType == OFXOSC_TYPE_FLOAT) { // physics
            
            // if this joint wasn't active, set new values and reset the averages
            if (!skeleton[jointName].bActive) {
                
                // reset all values related to position / velocity / acceleration
                skeleton[jointName].resetPhysics();
                
                // find new position
                ofVec3f thisPosition = ofVec3f(msg.getArgAsFloat(0), msg.getArgAsFloat(1), msg.getArgAsFloat(2));
                
                skeleton[jointName].setPosition(thisPosition);
                skeleton[jointName].avgPosition = thisPosition;
                
                // now the joint is active
                skeleton[jointName].bActive = true;
            }
            // otherwise, calculate averages, velocities, and accelerations
            else {
                
                // find new position
                ofVec3f thisPosition = ofVec3f(msg.getArgAsFloat(0), msg.getArgAsFloat(1), msg.getArgAsFloat(2));
                
                // find this velocity from the last position
                ofVec3f thisVelocity = thisPosition - skeleton[jointName].position;
                
                // find this acceleration from the last velocity
                ofVec3f thisAcceleration = thisVelocity - skeleton[jointName].velocity;
                
                // set new values and averages
                skeleton[jointName].setAllPhysics(thisPosition, thisVelocity, thisAcceleration);
                
            }
        }
    }
}

// --------------------------------------------------------------------

// request data from all the joints
void kinectRecorder::requestAllJoints(int coordinateSystem) {
    
    // request data for all joints a little less than every 2 seconds
    unsigned long thisTime = ofGetElapsedTimeMillis();
    if (thisTime - lastTime >= 1990) {

        // reset the last time
        lastTime = thisTime;
        
        // send a keepalive message to synapse for all joints
        for (int i = 0; i < 15; i++) {
            ofxOscMessage outMess;
            string tempString = "/" + jointNames[i] + "_trackjointpos";
            outMess.setAddress(tempString);
            outMess.addIntArg(coordinateSystem);
            
            sender.sendMessage(outMess);
        }
    }
}

// --------------------------------------------------------------------

// returns whether skeleton is actively being tracked (more than 1/2 of new data is coming in) and has been updated within the last second
// also updates bActive for each joint
bool kinectRecorder::updateState(unsigned long maxTime) {
    
    // number of active Joints
    int nActiveJoints = 0;
    
    // iterate through all elements in map
    map<string, joint>::iterator it;
    
    // get current time
    unsigned long thisTime = ofGetElapsedTimeMillis();
    
    for (it == skeleton.begin(); it != skeleton.end(); it++) {
        
        // This is how you access the pair's elements:
//        string thisString = it->first;  // key
//        joint thisJoint = it->second;   // value
        
        // if the joint was last updated more than maxTime ago, set its active state to false
        if (it->second.lastUpdateTime < (thisTime - maxTime)) {
            
            it->second.bActive = false;
        } else {
            
            // otherwise, we have one more active joint
            nActiveJoints++;
        }
    }
    
    // if more than half of the joints are active
    activeSkeleton = (nActiveJoints >= ceil((double)skeleton.size()));
    return activeSkeleton;
    
}

