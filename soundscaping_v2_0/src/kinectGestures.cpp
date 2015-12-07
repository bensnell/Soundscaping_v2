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

//// check if right hand is above head
//void gesture::righthandAboveHead() {
//    // Within this function, to access original skeleton, use this format:
//        // (*skeleton)["joint_name"]
//    
//    // check for whether right hand is above head
//    bool rightAboveHead = ((*skeleton)["righthand"].position.y > (*skeleton)["head"].position.y);
//    bool prevRightAboveHead = ((*skeleton)["righthand"].prevPosition.y > (*skeleton)["head"].prevPosition.y);
//    
//    // check for whether left hand is below torso
//    bool leftBelowTorso = ((*skeleton)["lefthand"].position.y < (*skeleton)["torso"].position.y);
//    
//    if (rightAboveHead && ! prevRightAboveHead && leftBelowTorso) {
//        gestureON = true;
//
//        
//    }
//    
//    
//}

// -----------------------------------------------------------------------

void gesture::handsTogether(map<string, joint> skeleton_) {
    
    if (skeleton_["righthand"].position.distance(skeleton_["lefthand"].position) < 100.) {
        
        setGestureState(true);
    } else {
        
        setGestureState(false);
    }
}

// -----------------------------------------------------------------------

void gesture::setGestureState(bool bState) {
    
    prevGestureState = gestureState;
    
    gestureState = bState;
    
//    cout << "state within setGestureState " << ofToString(activeSkeleton__) << "    " << prevGestureState << "  " << gestureState << endl;
    
    // change appropriate flags
    if (gestureState && !prevGestureState && activeSkeleton__) {
        
        flagON = true;
        
//        cout << "start recording" << endl;
        
    } else if (!gestureState && prevGestureState) {
        
        flagOFF = true;
        
//        cout << "end recording" << endl;
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

// -----------------------------------------------------------------------





