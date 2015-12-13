//
//  kinectGestures.cpp
//  soundscaping_v2_0
//
//  Created by Ben Snell on 12/6/15.
//
//

#include "kinectGestures.h"

//gesture::gesture(map<string, joint> skeleton_) {
//    
//    // get address of original skeleton and store it in a pointer
//    skeleton = &skeleton_;
//}

// -----------------------------------------------------------------------

void gesture::updateGesture(map<string, joint> skeleton_, bool activeSkeleton_) {
    
    activeSkeleton__ = activeSkeleton_;
    
    handsTogether(skeleton_);
    
}

// -----------------------------------------------------------------------

void gesture::handsTogether(map<string, joint> skeleton_) {
    
    if (skeleton_["righthand"].position.distance(skeleton_["lefthand"].position) < 100. && !gestureState) {
        
        setGestureState(true);
        
        lastGestureOnTime = ofGetElapsedTimeMillis();
        
    }
    if ((ofGetElapsedTimeMillis() > (lastGestureOnTime + 3000))){
        
        setGestureState(false);
    }
}

// -----------------------------------------------------------------------

void gesture::setGestureState(bool bState) {
    
    prevGestureState = gestureState;
    
    gestureState = bState;
    
    // change appropriate flags
    if (gestureState && !prevGestureState && activeSkeleton__) {
        
        flagON = true;
        
    } else if (!gestureState && prevGestureState) {
        
        flagOFF = true;
        
    }
}

// -----------------------------------------------------------------------

bool gesture::getFlagON() {
    
    bool tempFlag = flagON;
    flagON = false;
    return tempFlag;
}

// -----------------------------------------------------------------------

bool gesture::getFlagOFF() {
    
    bool tempFlag = flagOFF;
    flagOFF = false;
    return tempFlag;
}


