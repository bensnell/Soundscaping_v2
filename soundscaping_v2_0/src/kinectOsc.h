//
//  kinectOsc.h
//  soundscaping_v2_0
//
//  Created by Ben Snell on 12/2/15.
//
//

#ifndef __soundscaping_v2_0__kinectOsc__
#define __soundscaping_v2_0__kinectOsc__

#include "ofMain.h"
#include "ofxOsc.h"

class kinectRecorder {
    
public:
    
    ofxOscReceiver receiver;
    int synapseIn = 12345; // could also use 12347
    
    ofxOscSender sender;

    int synapseOut = 12346;
    
    void setupKinect();
    void updateKinect();
    
    
    void requestData(vector<string> jointNames);
    unsigned long lastTime = -2000;
    
    vector<string> jointNames_;
    
};






























#endif /* defined(__soundscaping_v2_0__kinectOsc__) */
