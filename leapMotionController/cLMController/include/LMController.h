//
//  PitchTracker.h
//  PitchTracking
//
//  Created by Bruno Di Giorgi on 19/01/16.
//  Copyright © 2016 Bruno Di Giorgi. All rights reserved.
//


#ifndef LMController_h
#define LMController_h

#include <stdio.h>
#include <vector>

#include "Leap.h"
#include "LeapMath.h"

#define NBONES 4
#define NFINGERS 5
#define NHANDS 2

class LMVector {
public:
    float x{0};
    float y{0};
    float z{0};
};

class LMBone {
public:
    int type;
    LMVector prevJoint;
    LMVector nextJoint;
};

class LMFinger {
public:
    LMFinger() : bones(NBONES){};
    int type;
    std::vector<LMBone> bones;
};

class LMHand {
public:
    LMHand() : fingers(NFINGERS){};
    bool isValid;
    int type;  // 0:left, 1:right
    bool detected;
    LMVector palmPosition;
    LMVector palmVelocity;
    LMVector palmNormal;
    LMVector palmPositionNormalized;
    std::vector<LMFinger> fingers;
};

class LMController {
public:
    
    LMController();
    
    // from LM Documentation:
    // "Polling the Controller object for frames is the simplest and often
    // best strategy when your application has a natural frame rate"
    
    void frame();
    bool hasFocus();
    bool isConnected();
    std::vector<LMHand> hands;
    
private:
    Leap::Controller controller;
    
};



#endif /* LMController_h */
