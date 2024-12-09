//
// Created by đỗ quyên on 10/12/24.
//

#include "LTimer.h"
// Initializes variables
LTimer::LTimer() {
    mStartTicks = 0;
    mPausedTicks = 0;

    mPaused = false;
    mStarted = false;
}

// The various clock actions
void LTimer::start() {
    // Start the timer
    mStarted = true;

    // Unpause the timer
    mPaused = false;

    // Get the current clock time
    mStartTicks = SDL_GetTicks();
    mPausedTicks = 0;
}

void LTimer::stop() {
    // Stop the timer
    mStarted = false;

    // Unpause the timer
    mPaused = false;

    // Clear tick variables
    mStartTicks = 0;
    mPausedTicks = 0;
}

void LTimer::pause() {
    // If the timer is running and isn't already paused
    if (mStarted && !mPaused) {
        // Pause the timer
        mPaused = true;

        // Calculate the paused ticks
        mPausedTicks = SDL_GetTicks() - mStartTicks;
        mStartTicks = 0;
    }
}

void LTimer::unpause() {
    // If the timer is running and paused
    if (mStarted && mPaused) {
        // Unpause the timer
        mPaused = false;

        // Reset the starting ticks
        mStartTicks = SDL_GetTicks() - mPausedTicks;

        // Reset the paused ticks
        mPausedTicks = 0;

    }
}

// Gets the timer's time
Uint32 LTimer::getTicks() const {
    // The actual timer time
    Uint32 time = 0;

    // If the timer is running
    if (mStarted) {
        // If the timer is paused
        if (mPaused) {
            // Return the number of ticks when the timer was paused
            time = mPausedTicks;
        }
        else {
            // Return the current time minus the start time
            time = SDL_GetTicks() - mStartTicks;
        }
    }
    return time;
}

// Checks the status of the timer
bool LTimer::isStarted() const {
    // Timer is running and paused or unpaused
    return mStarted;
}

bool LTimer::isPaused() const {
    // Timer is running and paused
    return mPaused && mStarted;
}
