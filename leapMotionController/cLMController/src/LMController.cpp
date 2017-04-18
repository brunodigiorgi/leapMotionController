//
//  PitchTracker.cpp
//  PitchTracking
//
//  Created by Bruno Di Giorgi on 19/01/16.
//  Copyright © 2016 Bruno Di Giorgi. All rights reserved.
//


#include <cassert>
#include <cmath>
#include "LMController.h"

LMController::LMController() : hands(NHANDS){
    controller.setPolicy(Leap::Controller::PolicyFlag::POLICY_BACKGROUND_FRAMES);
};

bool LMController::hasFocus(){
    return controller.hasFocus();
}

bool LMController::isConnected(){
    return controller.hasFocus();
}

void LMController::frame() {
    if(!controller.isConnected()) {
        return;
    }
    
    Leap::Frame frame = controller.frame();
    Leap::InteractionBox f_box = frame.interactionBox();
    Leap::HandList f_hands = frame.hands();
    Leap::PointableList pointables = frame.pointables();
    Leap::FingerList f_fingers = frame.fingers();
    Leap::ToolList tools = frame.tools();
    
    hands[0].detected = false;
    hands[1].detected = false;
    for(int ih = 0; ih < f_hands.count(); ih++){
        Leap::Hand hand = f_hands[ih];
        
        int ihand = 0;
        if(hand.isRight())
            ihand = 1;
        
        LMHand& h = hands[ihand];
        h.detected = true;
        h.type = ihand;
        h.isValid = hand.isValid();
        
        Leap::Vector v;
        v = hand.palmPosition();
        h.palmPosition.x = v.x;
        h.palmPosition.y = v.y;
        h.palmPosition.z = v.z;
        
        v = hand.palmVelocity();
        h.palmVelocity.x = v.x;
        h.palmVelocity.y = v.y;
        h.palmVelocity.z = v.z;
        
        v = hand.palmNormal();
        h.palmNormal.x = v.x;
        h.palmNormal.y = v.y;
        h.palmNormal.z = v.z;
        
        v = f_box.normalizePoint(hand.palmPosition());
        h.palmPositionNormalized.x = v.x;
        h.palmPositionNormalized.y = v.y;
        h.palmPositionNormalized.z = v.z;
        
        Leap::FingerList fingers = hand.fingers();
        for(int if_ = 0; if_ < fingers.count(); if_++){
            Leap::Finger finger = fingers[if_];
            
            int ifinger = finger.type();
            LMFinger& f = h.fingers[ifinger];
            
            for(int ib = 0; ib < NBONES; ib++){
                Leap::Bone b = finger.bone(Leap::Bone::Type(ib));
                v = b.prevJoint();
                f.bones[ib].prevJoint.x = v.x;
                f.bones[ib].prevJoint.y = v.y;
                f.bones[ib].prevJoint.z = v.z;
                
                v = b.nextJoint();
                f.bones[ib].nextJoint.x = v.x;
                f.bones[ib].nextJoint.y = v.y;
                f.bones[ib].nextJoint.z = v.z;
            }
        }
    }
}








