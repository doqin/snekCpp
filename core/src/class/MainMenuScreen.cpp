
#include "MainMenuScreen.h"
#include "GameScreen.h"
#include "state.h"
#include <SDL_events.h>

MainMenuScreen::MainMenuScreen(snekCpp* game) {
    this->snek = game;
}

void MainMenuScreen::Init() {
    viewPort = {0, 0, 600, 600};
    gMenuBackground.loadFromFile(this->snek->renderer, "../assets/homescreen.png");
}

void MainMenuScreen::Cleanup() {
    gMenuBackground.free();
    snek = nullptr;
}

void MainMenuScreen::Pause() {

}

void MainMenuScreen::Resume() {

}

void MainMenuScreen::HandleEvents() {
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            snek->Quit();
        }
    }
}

void MainMenuScreen::Update() {

}

void MainMenuScreen::Draw() {
    gMenuBackground.render(snek->renderer, 0, 0, &viewPort);
    SDL_RenderPresent(this->snek->renderer);
}

