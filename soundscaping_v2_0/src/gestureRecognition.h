//
//  gestureRecognition.h
//  soundscaping_v2_0
//
//  Created by Ben Snell on 12/6/15.
//
//

#ifndef __soundscaping_v2_0__gestureRecognition__
#define __soundscaping_v2_0__gestureRecognition__

#include "ofMain.h"
#include "kinectJoint.h"
#include "kinectGestures.h"
#include "ofxOsc.h"
//#include "soundParticle.h"

class gestureProcessor {
    
public:
    
    // ---------------------
    // ---- CONSTRUCTION ---
    // ---------------------
    
    void linkSkeleton(map<string, joint> skeleton_, bool activeSkeleton_);
    // pass original object to function (i.e. <skeleton>)
    
    map<string, joint>* skeleton;
    // pointer to store address of original skeleton
    
    bool* activeSkeleton;
    
    // ---------------------
    // ------ GESTURES -----
    // ---------------------
    
    // process skeleton -- check for all gestures
    void processSkeleton(map<string, joint> skeleton_, bool activeSkeleton_);
    
    // gestures of interest (could eventually be a vector of them)
    gesture myGesture;
    
    // ---------------------
    // -- PIXELIZED SPACE --
    // ---------------------

    ofVec3f spaceLowerCorner = ofVec3f(-1000., -1000., 2000.);
    float spaceSideLength = 2000.;
    int nSideDivisions = 4;
    
    map<int, ofVec3f> soundParticles;
    int currentBufferNumber = -1; // if not -1, we're currently writing to a buffer
    ofVec3f currentPoint;
    bool recordingState = false;
    unsigned long startTime;
    
    
    // ---------------------
    // ------- TO MAX ------
    // ---------------------
    
    // communication to max
    ofxOscSender toMax;
    int maxPort = 1818;
    
    void playAudio(map<string, joint> skeleton_, bool activeSkeleton_);
    
};

#endif /* defined(__soundscaping_v2_0__gestureRecognition__) */
