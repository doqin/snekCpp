//
// Created by đỗ quyên on 10/12/24.
//

#ifndef LTIMER_H
#define LTIMER_H

#include <SDL.h>

// The application time based timer
class LTimer {
public:
    // Initializes variables
    LTimer();

    // The various clock actions
    void start();

    void stop();

    void pause();

    void unpause();

    // Gets the timer's time
    Uint32 getTicks() const;

    // Checks the status of the timer
    bool isStarted() const;

    bool isPaused() const;

private:
    // The clock time when the timer started
    Uint32 mStartTicks;

    // The ticks stored when the timer was paused
    Uint32 mPausedTicks;

    // The timer status
    bool mPaused;
    bool mStarted;
};

#endif //LTIMER_H
