//
//  gestureRecognition.cpp
//  soundscaping_v2_0
//
//  Created by Ben Snell on 12/6/15.
//
//

#include "gestureRecognition.h"

void gestureProcessor::linkSkeleton(map<string, joint> skeleton_, bool activeSkeleton_) {
    
    // get address of original skeleton and store it in a pointer
    skeleton = &skeleton_;
    
    // setup max OSC
    toMax.setup("localhost", maxPort);
//    toMax.setup("128.237.203.67", 1818);
    
    activeSkeleton = &activeSkeleton_;
}

// ----------------------------------------------------------------------

// main function to look for gestures and send the messages
void gestureProcessor::processSkeleton(map<string, joint> skeleton_, bool activeSkeleton_) {
    
    // should eventually look through all gestures added to this gesture processor...

    // update the gestures to check for changes / activations / deactivations
    myGesture.updateGesture(skeleton_, activeSkeleton_);
    
    // check if any flag on messages have been activated... if so, send to max
    if (myGesture.getFlagON() && !recordingState && activeSkeleton_) {
        
        // find the position of the right hand
//        ofVec3f rHand = skeleton_["righthand"].position;
        ofVec3f rHand = skeleton_["head"].position;
        ofVec3f rHandRelToCorner = rHand - spaceLowerCorner;
        
        float xDot = rHandRelToCorner.dot(ofVec3f(1., 0., 0.));
        float yDot = rHandRelToCorner.dot(ofVec3f(0., 1., 0.));
        float zDot = rHandRelToCorner.dot(ofVec3f(0., 0., 1.));
        
        // if the dot products with the axis are less than the radius, continue
        if (xDot > 0 && xDot < spaceSideLength &&
            yDot > 0 && yDot < spaceSideLength &&
            zDot > 0 && zDot < spaceSideLength) {
            
            int xIndex = (int)floor(xDot / (spaceSideLength / (float)nSideDivisions));
            int yIndex = (int)floor(yDot / (spaceSideLength / (float)nSideDivisions));
            int zIndex = (int)floor(zDot / (spaceSideLength / (float)nSideDivisions));
            
            currentBufferNumber = xIndex + zIndex * nSideDivisions + yIndex * nSideDivisions * nSideDivisions;
            
            float unitSideLength = spaceSideLength / (float)nSideDivisions;
            float xCenter = xIndex * unitSideLength + unitSideLength / 2.;
            float yCenter = yIndex * unitSideLength + unitSideLength / 2.;
            float zCenter = zIndex * unitSideLength + unitSideLength / 2.;
            
            currentPoint = ofVec3f(xCenter, yCenter, zCenter) + spaceLowerCorner;
            
            recordingState = true;
            startTime = ofGetElapsedTimeMillis();
            
            // send message
            ofxOscMessage msg;
            msg.setAddress("/record");
            msg.addIntArg(1);
            msg.addIntArg(currentBufferNumber);
            msg.addIntArg(1000);
            toMax.sendMessage(msg);
            
            cout << "start recording with buffer # " << currentBufferNumber << endl;
        }
        
    } else if (myGesture.getFlagOFF() && recordingState) {
        
        int bufferDuration = (int)(ofGetElapsedTimeMillis() - startTime);
        
        ofxOscMessage msg;
        msg.setAddress("/record");
        msg.addIntArg(0);
        msg.addIntArg(currentBufferNumber);
        msg.addIntArg(bufferDuration);
        toMax.sendMessage(msg);
        
        soundParticles[currentBufferNumber] = currentPoint; // add particle
        
        recordingState = false;
        
        cout << "end recording with buffer # " << currentBufferNumber << endl;
    }

    // TODO: if recording lasts more than a certain number of seconds, stop recording
    
}

// ----------------------------------------------------------------------

// send data to max with the volumes of each buffer
void gestureProcessor::playAudio(map<string, joint> skeleton_, bool activeSkeleton_) {
    
    map<int, ofVec3f>::iterator it;
    
    ofVec3f headPosition = skeleton_["head"].avgPosition;
    
    float diagonalLength = sqrt(pow(spaceSideLength, 2.f) * 3.);
    
    for (it = soundParticles.begin(); it != soundParticles.end(); it++) {
        
        ofxOscMessage msg;
        msg.setAddress("/play");
        msg.addIntArg(it->first);
        
        float distToPoint = headPosition.distance(it->second);
        float volumeLevel = (diagonalLength - distToPoint) / diagonalLength;
        volumeLevel = pow(volumeLevel, 3.f);
        
        msg.addFloatArg(volumeLevel);
        toMax.sendMessage(msg);
    }
}

