//
//  FFTTest.cpp
//  DSP
//
//  Created by Bruno Di Giorgi on 31/03/15.
//  Copyright (c) 2015 Bruno Di Giorgi. All rights reserved.
//

#include <stdio.h>

#include "gtest/gtest.h"

#include "LMController.h"

TEST(LMController, test){
    
    LMController controller;
    
    for(int i = 0; i < 10; i++) {
        sleep(1);
        controller.frame();
        
        std::cout << controller.hands[1].palmPosition.x << std::endl;
        
    }
}