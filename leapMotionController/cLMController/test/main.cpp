//
//  main.cpp
//  multipath_test
//
//  Created by Bruno Di Giorgi on 18/01/16.
//  Copyright © 2016 Bruno Di Giorgi. All rights reserved.
//

#include <iostream>

#include <algorithm>
#include <vector>
#include "gtest/gtest.h"

int main(int argc, char * argv[]) {
    
    testing::FLAGS_gtest_filter = "LMController.*";
    testing::InitGoogleTest(&argc, argv);
    assert(RUN_ALL_TESTS() == 0);
    
    return 0;
}
