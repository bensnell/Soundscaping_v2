//
//  kinectGestures.cpp
//  soundscaping_v2_0
//
//  Created by Ben Snell on 12/6/15.
//
//

#include "kinectGestures.h"

gesture::gesture(map<string, joint> skeleton_) {
    
    // get address of original skeleton and store it in a pointer
    skeleton = &skeleton_;
}

// -----------------------------------------------------------------------

// check if right hand is above head
void gesture::righthandAboveHead() {
    // Within this function, to access original skeleton, use this format:
        // (*skeleton)["joint_name"]
    
    bool bNow = ((*skeleton)["righthand"].position.y > (*skeleton)["head"].position.y);
    
    bool bLast = ((*skeleton)["righthand"].prevPosition.y > (*skeleton)["head"].prevPosition.y);
    
    
    
    
    
    
    
}
