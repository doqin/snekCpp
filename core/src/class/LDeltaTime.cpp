//
// Created by đỗ quyên on 10/12/24.
//

#include "LDeltaTime.h"
LDeltaTime::LDeltaTime() {
    mDeltaTime = 0;
    mTimer.start();

    mLastTime = 0;
    mCurrentTime = 0;
}

LDeltaTime::LDeltaTime (const float milliseconds) {
    mDeltaTime = milliseconds;
    mTimer.start();

    mLastTime = milliseconds;
    mCurrentTime = 0;
}

void LDeltaTime::update() {
    mCurrentTime = mTimer.getTicks();
    mDeltaTime = (mCurrentTime - mLastTime) / 1000.f;
    mLastTime = mCurrentTime;
}

float LDeltaTime::getDeltaTime() {
    return mDeltaTime;
}
