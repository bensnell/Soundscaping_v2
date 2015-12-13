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
    myGesture.updateGesture(skeleton_);
    
    // send to max whether or not to begin recording
    updateLineSpace(myGesture, skeleton_, activeSkeleton_);
    
}

// ----------------------------------------------------------------------

void gestureProcessor::updateLineSpace(gesture gesture_, map<string, joint> skeleton_, bool activeSkeleton_) {
    
    // if we're not currently recording...
    if (!recordingState) {

        // ... and a gesture is on and the skeleton is actively being tracked ...
        if (gesture_.getFlagON() && activeSkeleton_) {
            
            // ... and the last time a note was turned on was more than 1 second ago...
            if ((lastLineOnTime + bounceOnTime) < ofGetElapsedTimeMillis()) {
                
                // ... and the last time a note was turned off is more than 1/2 sec ago, then start recording
                if ((lastLineOffTime + bounceOffTime) < ofGetElapsedTimeMillis()) {
                    
                    recordingState = true;
                    
                    // reset the last note on time
                    lastLineOnTime = ofGetElapsedTimeMillis();
                    
                    // send message to Max
                    ofxOscMessage msg;
                    msg.setAddress("/record");
                    msg.addIntArg(1);
                    msg.addIntArg(bufferCounter);
                    //            msg.addIntArg(1000);
                    toMax.sendMessage(msg);
                    
                    cout << "start recording with buffer # " << currentBufferNumber << endl;
                }
            }
        }
    }
    // if we're currently recording...
    else if (recordingState) {
        
        // ... and the gesture turns off or the length of the recording reaches its limit, then stop recording
        if (gesture_.getFlagOFF() || ((ofGetElapsedTimeMillis() - lastLineOnTime) > maxRecordingTime)) {
            
            recordingState = false;
            
            lastLineOffTime = ofGetElapsedTimeMillis();
            
            // set the duration of the recording
            int lastTime = thisLine.times.back(); // DOES THIS WORK??
            int bufferDuration = lastTime - timeZero;
            thisLine.duration = bufferDuration;
            
            // set the startTime of the recording
            thisLine.startTime = timeZero;
            
            // resample the line
            thisLine.resampleLine(true);
            
            // send message to Max
            ofxOscMessage msg;
            msg.setAddress("/record");
            msg.addIntArg(0);
            msg.addIntArg(bufferCounter);
//            msg.addIntArg(bufferDuration);
            toMax.sendMessage(msg);

            cout << "end recording with buffer # " << currentBufferNumber << endl;
            
            // add new line to the vector of lines
            allLines.push_back(thisLine);
            // reset thisLine
            thisLine.reset();
            // reset time zero
            timeZero = 0;
            
            // increment buffer counter for Max
            bufferCounter++;
        }
    }
    
    // if we're recording, log the points
    if (recordingState) {
        
        // find the current time in ms
        int timeNow;
        if (thisLine.rawLine.size() == 0) {
            timeZero = ofGetElapsedTimeMillis();
            timeNow = 0;
        } else {
            timeNow = (int)(ofGetElapsedTimeMillis() - timeZero);
        }
        
        // add the time and point at the joint of interest to thisLine
        thisLine.rawLine.addVertex(skeleton_[recordingJoint].position);
        thisLine.times.push_back(timeNow);
    }
}

// ----------------------------------------------------------------------

// play back audio depending on the time (i.e. location in sound lines) and the location of the playbackJoint
void gestureProcessor::playLineSpace(map<string, joint> skeleton_, bool activeSkeleton_) {
    
    // try with iterators next time!
    // iterate through all sound lines
    for (int i = 0; i < allLines.size(); i++) {
        
        // find distance from playback joint to current playback point
        float dist = allLines[i].getDistToPlaybackPoint(skeleton_[playbackJoint].position);
        
        
        
        
        
        
        
        
        
    }
    
    
    
    
    
    
    
    
}

// ----------------------------------------------------------------------

// for a pixelized space
void gestureProcessor::updatePixelSpace(gesture gestureOfInterest, map<string, joint> skeleton_, bool activeSkeleton_) {
    
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
            lastLineOnTime = ofGetElapsedTimeMillis();
            
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
        
        int bufferDuration = (int)(ofGetElapsedTimeMillis() - lastLineOnTime);
        
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
}

// ----------------------------------------------------------------------

// send data to max with the volumes of each buffer
void gestureProcessor::playAudioPixelSpace(map<string, joint> skeleton_, bool activeSkeleton_) {
    
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

