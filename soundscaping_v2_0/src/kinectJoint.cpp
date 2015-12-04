//
//  kinectJoint.cpp
//  soundscaping_v2_0
//
//  Created by Ben Snell on 12/3/15.
//
//

#include "kinectJoint.h"

// constructor
// How do you pass a name into joint while being able to construct a map elsewhere outside of this class using map<string, joint> ?
joint::joint() {
    
    // why won't this work?
//    hits = {{"up", false}, {"down", false}, {"left", false}, {"right", false}, {"forward", false}, {"back", false}};
    
    // initialize map with all values to false
    string hitNames[6] = { "up", "down", "left", "right", "forward", "back" };
    for (int i = 0; i < 6; i++) {
        
//        hits.insert(std::pair<string, bool>(hitNames[i], false));
//        m_deck.insert(std::pair<int, Card>(0, Card(Card::NOVALUE, Card::NOFACE)));
        
        hits[hitNames[i]] = false;
    }
    
    resetPhysics();
}

// -------------------------------------------------------------------

// destructive retrieval of hits
bool joint::getHit(string jointName) {
    
    if (hits[jointName] == true) {
        hits[jointName] = false;
        return true;
    } else {
        return false;
    }
}

// -------------------------------------------------------------------

void joint::resetPhysics() {
    
    position = ofVec3f(0, 0, 0);
    avgPosition = ofVec3f(0, 0, 0);
    
    velocity = ofVec3f(0, 0, 0);
    avgVelocity = ofVec3f(0, 0, 0);
    
    acceleration = ofVec3f(0, 0, 0);
    avgAcceleration = ofVec3f(0, 0, 0);
}

