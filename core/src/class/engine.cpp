//
// Created by đỗ quyên on 9/12/24.
//

#include "engine.h"
#include <vector>
#include "SDL.h"
#include "state.h"

void CGameEngine::Init(const char* title, int width, int height, bool fullscreen) {
    int flags = 0;

    // Save the screen dimensions
    mWidth = width;
    mHeight = height;

    // Initialize SDL
    SDL_Init(SDL_INIT_VIDEO);

    //Set texture filtering to linear
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        printf("Warning: Linear texture filtering not enabled!");
    }

    // Get flags
    if ( fullscreen ) {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    // Create the screen window
    screen = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

    // Create the renderer
    renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);

    mFullscreen = fullscreen;
    mRunning = true;

    printf("CGameEngine Init\n");
}

void CGameEngine::Cleanup()
{
    // Cleanup the all states
    while ( !states.empty() ) {
        states.back()->Cleanup();
        states.pop_back();
    }

    // Switch back to windowed mode so other
    // Programs won't get accidentally resized
    if ( mFullscreen ) {
        SDL_SetWindowFullscreen(screen, 0);
        SDL_SetWindowSize(screen, mWidth, mHeight);
    }

    printf("CGameEngine Cleanup\n");

    // shutdown SDL
    SDL_Quit();
}

void CGameEngine::ChangeState(CGameState* state)
{
    // cleanup the current state
    if ( !states.empty() ) {
        states.back()->Cleanup();
        states.pop_back();
    }

    // store and init the new state
    states.push_back(state);
    states.back()->Init();
}

void CGameEngine::PushState(CGameState* state)
{
    // Pause current state
    if ( !states.empty() ) {
        states.back()->Pause();
    }

    // Store and init the new state
    states.push_back(state);
    states.back()->Init();
}

void CGameEngine::PopState()
{
    // Cleanup the current state
    if ( !states.empty() ) {
        states.back()->Cleanup();
        states.pop_back();
    }

    // Resume previous state
    if ( !states.empty() ) {
        states.back()->Resume();
    }
}


void CGameEngine::HandleEvents()
{
    // Let the state handle events
    states.back()->HandleEvents();
}

void CGameEngine::Update()
{
    // Let the state update the game
    states.back()->Update();
}

void CGameEngine::Draw()
{
    // Let the state draw the screen
    states.back()->Draw();
}