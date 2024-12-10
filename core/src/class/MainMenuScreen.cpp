
#include "MainMenuScreen.h"
#include <SDL_events.h>

#include "GameScreen.h"

MainMenuScreen::MainMenuScreen(snekCpp* game) {
    this->snek = game;
}

void MainMenuScreen::Init() {
    snek->viewPort = {0, 0, snek->mWidth, snek->mHeight};
    gMenuBackground.loadFromFile(this->snek->renderer, "../assets/homescreen.png");
}

void MainMenuScreen::Cleanup() {
    gMenuBackground.free();
    snek = nullptr;
    delete this;
}

void MainMenuScreen::Pause() {

}

void MainMenuScreen::Resume() {

}

void MainMenuScreen::HandleEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                snek->Quit();
            break;
            case SDL_MOUSEBUTTONDOWN:
                switch (e.button.button) {
                    case SDL_BUTTON_LEFT:
                        if (snek->mMouseFocus == true)
                            snek->ChangeState(new GameScreen(snek));
                    break;
                    default:
                        break;
                }
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym) {
                    case SDLK_RETURN:
                        snek->ChangeState(new GameScreen(snek));
                    break;
                    default:
                        break;
                }
            case SDL_WINDOWEVENT:
                switch (e.window.event) {
                    //Window resized
                    case SDL_WINDOWEVENT_RESIZED:
                        if (e.window.data1 <= e.window.data2)
                            snek->viewPort = {0, (e.window.data2 - e.window.data1) / 2, e.window.data1, e.window.data1};
                        else
                            snek->viewPort = {(e.window.data1 - e.window.data2) / 2, 0, e.window.data2, e.window.data2};
                    snek->mWidth = e.window.data1;
                    snek->mHeight = e.window.data2;
                    break;
                    default:
                        break;
                    case SDL_WINDOWEVENT_ENTER:
                        snek->mMouseFocus = true;
                    break;
                    case SDL_WINDOWEVENT_LEAVE:
                        snek->mMouseFocus = false;
                    break;
                }
            default:
                break;
        }
    }
}

void MainMenuScreen::Update() {

}

void MainMenuScreen::Draw() {
    // Clear previous render
    SDL_SetRenderDrawColor(snek->renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(snek->renderer);

    // Render background texture
    gMenuBackground.render(snek->renderer, snek->viewPort.x, snek->viewPort.y, &snek->viewPort);

    // Update screen
    SDL_RenderPresent(snek->renderer);
}

