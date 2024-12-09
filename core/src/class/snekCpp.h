
#ifndef SNEKCPP_H
#define SNEKCPP_H

#include <vector>
#include <SDL.h>
#include <SDL_ttf.h>
#include "game.h"

class snekCpp final : public CGameEngine {
public:
    // Global font
    TTF_Font* gFont;

    // Viewport
    SDL_Rect viewPort;

    void Init(const char *title, const int width, const int height, const bool fullscreen) override {
        int flags = 0;

        // Save the screen dimensions
        mWidth = width;
        mHeight = height;

        // Initialize SDL
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        }

        // Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            printf("Warning: Linear texture filtering not enabled!");
        }

        // Get flags
        if (fullscreen) {
            flags = SDL_WINDOW_FULLSCREEN;
        }

        // Create the screen window
        screen = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags | SDL_WINDOW_RESIZABLE);

        // Create the renderer
        renderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        mFullscreen = fullscreen;
        mRunning = true;

        gFont = TTF_OpenFont("../assets/fonts/lazy.ttf", 28);

        printf("CGameEngine Init\n");
    }
    void ChangeState(CGameState* state) override
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

    void Cleanup() override {
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

        //Deallocate stuff
        TTF_CloseFont(gFont);
        gFont = nullptr;
        SDL_DestroyRenderer(renderer);
        renderer = nullptr;
        SDL_DestroyWindow(screen);
        screen = nullptr;

        // Close game
        SDL_Quit();
    }
};

#endif //SNEKCPP_H