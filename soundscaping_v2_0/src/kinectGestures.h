//
//  kinectGestures.h
//  soundscaping_v2_0
//
//  Created by Ben Snell on 12/6/15.
//
//

#ifndef __soundscaping_v2_0__kinectGestures__
#define __soundscaping_v2_0__kinectGestures__

#include "ofMain.h"
#include "kinectJoint.h"

class gesture {
    
public:
    
//    map<string, joint>* skeleton;
    // pointer to store address of original skeleton
    
//    gesture(map<string, joint> skeleton_);
    // pass original object to function (i.e. <skeleton>)
    
    // call this function to update the gesture each frame
    void updateGesture(map<string, joint> skeleton_, bool activeSkeleton_);
    
    void setGestureState(bool bState);
    // holds current and previous state of gesture (ON or OFF)
    bool gestureState = false;
    bool prevGestureState = false;
    // flags to hold switch from on to off and vice versa
    bool flagON = false;
    bool flagOFF = false;
    bool getFlagON();
    bool getFlagOFF();
    
    bool activeSkeleton__;
    
    
    // AVAILABLE GESTURES:
    void handsTogether(map<string, joint> skeleton_);

    // NEED DEBOUNCER
    
    unsigned long lastGestureOnTime;
    
};

#endif /* defined(__soundscaping_v2_0__kinectGestures__) */
