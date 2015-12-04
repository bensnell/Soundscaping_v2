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
        joints[jointNames[i]] = joint();
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
        if (joints.find(jointName) == joints.end()) continue;

        // find type of first argument
        ofxOscArgType thisType = msg.getArgType(0);
        
        // update the hits or physics depending on the type
        if (thisType == OFXOSC_TYPE_STRING) { // hits
            
            string hitDirection = msg.getArgAsString(0);
            
            joints[jointName].hits[hitDirection] = true;
            
        } else if (thisType == OFXOSC_TYPE_FLOAT) { // physics
            
            // if this joint wasn't active, set new values and reset the averages
            if (!joints[jointName].bActive) {
                
                // reset all values related to position / velocity / acceleration
                joints[jointName].resetPhysics();
                
                // find new position
                ofVec3f thisPosition = ofVec3f(msg.getArgAsFloat(0), msg.getArgAsFloat(1), msg.getArgAsFloat(2));
                
                joints[jointName].position = thisPosition;
                joints[jointName].avgPosition = thisPosition;
                
                // now the joint is active
                joints[jointName].bActive = true;
            }
            // otherwise, calculate averages, velocities, and accelerations
            else {
                
                // find new position
                ofVec3f thisPosition = ofVec3f(msg.getArgAsFloat(0), msg.getArgAsFloat(1), msg.getArgAsFloat(2));
                
                // find this velocity from the last position
                ofVec3f thisVelocity = thisPosition - joints[jointName].position;
                
                // find this acceleration from the last velocity
                ofVec3f thisAcceleration = thisVelocity - joints[jointName].velocity;
                
                // set new values and averages with weights
                joints[jointName].position = thisPosition;
                joints[jointName].avgPosition = joints[jointName].avgPosition * (1. - joints[jointName].avgWeight) + thisPosition * joints[jointName].avgWeight;
                
                joints[jointName].velocity = thisVelocity;
                joints[jointName].avgVelocity = joints[jointName].avgVelocity * (1. - joints[jointName].avgWeight) + thisVelocity * joints[jointName].avgWeight;
                
                joints[jointName].acceleration = thisAcceleration;
                joints[jointName].avgAcceleration = joints[jointName].avgAcceleration * (1. - joints[jointName].avgWeight) + thisAcceleration * joints[jointName].avgWeight;
                
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

