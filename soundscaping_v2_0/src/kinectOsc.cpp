//
//  kinectOsc.cpp
//  soundscaping_v2_0
//
//  Created by Ben Snell on 12/2/15.
//
//

#include "kinectOsc.h"

void kinectRecorder::setupKinect() {
    
    receiver.setup(synapseIn);
    
    sender.setup("localhost", synapseOut);
    
}

// --------------------------------------------------------------------

void kinectRecorder::updateKinect() {
    
    while (receiver.hasWaitingMessages()) {
        
        ofxOscMessage mess;
        receiver.getNextMessage(&mess);
        string thisAddress = mess.getAddress();
        vector<float> args;
        
        for (int i = 0; i < jointNames_.size(); i++) {
            
            string tempName = "/" + jointNames_[i] + "_pos_world";
            if (thisAddress.compare(tempName) == 0) {
                
                for (int i = 0; i < mess.getNumArgs(); i++) {
                    float thisArg = mess.getArgAsFloat(i);
        
                    args.push_back(thisArg);
                    
//                    cout << thisArg << "  ";
                }
//                cout << endl;
                
                break;
            }
        }
    }
    
}

// --------------------------------------------------------------------

void kinectRecorder::requestData(vector<string> jointNames) {
    
    jointNames_ = jointNames;
    
    if (ofGetElapsedTimeMillis() - lastTime >= 1990) {
        lastTime = ofGetElapsedTimeMillis();
        
    
        for (int i = 0; i < jointNames.size(); i++) {
            ofxOscMessage outMess;
            string tempString = "/" + jointNames[i] + "_trackjointpos";
            outMess.setAddress(tempString);
            outMess.addIntArg(2);
            
            sender.sendMessage(outMess);
        }
    }
}

