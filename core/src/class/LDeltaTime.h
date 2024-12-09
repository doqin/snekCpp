//
// Created by đỗ quyên on 10/12/24.
//

#ifndef LDELTATIME_H
#define LDELTATIME_H

#include "LTimer.h"

class LDeltaTime {
public:
    //Initializes variables
    LDeltaTime();

    //Initializes variables with existing offset
    LDeltaTime(float milliseconds);

    //Update delta time
    void update();

    //Get delta time
    float getDeltaTime();

private:
    LTimer mTimer;
    float mDeltaTime;
    float mLastTime;
    float mCurrentTime;
};



#endif //LDELTATIME_H
