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
    
    map<string, joint>* skeleton;
    // pointer to store address of original skeleton
    
    gesture(map<string, joint> skeleton_);
    // pass original object to function (i.e. <skeleton>)
    

    
    void righthandAboveHead();
    
    
    
    
};

bool righthandAboveHead(map<string, joint> joints_);






#endif /* defined(__soundscaping_v2_0__kinectGestures__) */
