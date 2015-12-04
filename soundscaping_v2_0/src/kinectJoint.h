//
//  kinectJoint.h
//  soundscaping_v2_0
//
//  Created by Ben Snell on 12/3/15.
//
//

#ifndef __soundscaping_v2_0__kinectJoint__
#define __soundscaping_v2_0__kinectJoint__

#include "ofMain.h"

class joint {
    
public:
    
    // constructor
    joint();
    
    // physics
    ofVec3f position;
    ofVec3f avgPosition;
    
    ofVec3f velocity;
    ofVec3f avgVelocity;
    
    ofVec3f acceleration;
    ofVec3f avgAcceleration;
    
    // for weighting the averages
    float avgWeight = 0.5; // 0.5 = equally weight new value with running average
    
    // hits
    map<string, bool> hits;

    bool getHit(string jointName);
    
    // boolean to know if joint is actively being tracked / updated
    bool bActive = false;
    
    void resetPhysics();
};

#endif /* defined(__soundscaping_v2_0__kinectJoint__) */
