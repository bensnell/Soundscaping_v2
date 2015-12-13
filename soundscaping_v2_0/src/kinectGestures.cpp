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

//// closeness of jointA and jointB
//void gesture::createGestureByProximity(map<string, joint> skeleton_, string jointA_, string jointB_) {
//    
//    jointA = jointA_;
//    jointB = jointB_;
////        createGesture = &createGestureByProximity;
//    
//    
//    
//    
//    
//    
//}
//
//// jointA further along projected axis than jointB
//void gesture::createGestureByHeight(map<string, joint> skeleton_, string jointA, string jointB, ofVec3f projectedAxis) {
//    
//    
//
//
//    
//}
//
//// direction is from jointA to jointB (ray AB)
//void gesture::createGestureByDirection(map<string, joint> skeleton_, string jointA, string jointB, ofVec3f direction) {
//    
//    
//    
//    
//}

// -----------------------------------------------------------------------

// just update the state of the gesture (don't do any debugging here)
void gesture::updateGesture(map<string, joint> skeleton_) {
    
    if (skeleton_["righthand"].position.distance(skeleton_["lefthand"].position) < 100. && !gestureState) {
    
            setGestureState(true);
    
    }
    
}


//void gesture::updateGesture(map<string, joint> skeleton_, bool activeSkeleton_) {
//    
//    activeSkeleton__ = activeSkeleton_;
//    
//    handsTogether(skeleton_);
//    
//    lastGestureOnTime = ofGetElapsedTimeMillis();
//    
//}
//
//// -----------------------------------------------------------------------
//
//void gesture::handsTogether(map<string, joint> skeleton_) {
//    
//    if (skeleton_["righthand"].position.distance(skeleton_["lefthand"].position) < 100. && !gestureState) {
//        
//        setGestureState(true);
//        
//    }
//    if ((ofGetElapsedTimeMillis() > (lastGestureOnTime + 3000))){
//        
//        setGestureState(false);
//    }
//}

// -----------------------------------------------------------------------

void gesture::setGestureState(bool bState) {
    
    prevGestureState = gestureState;
    
    gestureState = bState;
    
    // change appropriate flags
    if (gestureState && !prevGestureState) {
        
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


