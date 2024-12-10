//
// Created by đỗ quyên on 10/12/24.
//

#include "EndingScreen.h"
#include "GameScreen.h"
#include "MainMenuScreen.h"

EndingScreen::EndingScreen(snekCpp *game) {
    this->snek = game;
}

EndingScreen::~EndingScreen() = default;

void EndingScreen::Init() {
    // Update viewPort
    if (snek->mWidth <= snek->mHeight)
        snek->viewPort = {0, (snek->mHeight - snek->mWidth) / 2, snek->mWidth, snek->mWidth};
    else
        snek->viewPort = {(snek->mWidth - snek->mHeight) / 2, 0, snek->mHeight, snek->mHeight};

    gDeathTexture.loadFromRenderedText(snek->renderer, snek->gFont, "ur ded (XP)", textColor);
    gScoreTexture.loadFromRenderedText(snek->renderer, snek->gFont, "final score: " + std::to_string(GameScreen::applesEaten), textColor);
    gRestartPromptTexture.loadFromRenderedText(snek->renderer, snek->gFont, "(click or enter to restart)", textColor);
    gReturnPromptTexture.loadFromRenderedText(snek->renderer, snek->gFont, "press esc to return to main menu", textColor);
}

void EndingScreen::Cleanup() {
    gDeathTexture.free();
    gScoreTexture.free();
    gRestartPromptTexture.free();
    gReturnPromptTexture.free();
    snek = nullptr;
    delete this;
}

void EndingScreen::Pause() {
}

void EndingScreen::Resume() {
}

void EndingScreen::HandleEvents() {
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
                    case SDLK_ESCAPE:
                        snek->ChangeState(new MainMenuScreen(snek));
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

void EndingScreen::Update() {
}

void EndingScreen::Draw() {
    SDL_SetRenderDrawColor(snek->renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(snek->renderer);
    gDeathTexture.render(snek->renderer, (snek->mWidth - gDeathTexture.getWidth()) / 2, snek->viewPort.h / 6);
    gScoreTexture.render(snek->renderer, (snek->mWidth - gScoreTexture.getWidth()) / 2, snek->viewPort.h / 3);
    gRestartPromptTexture.render(snek->renderer, (snek->mWidth - gRestartPromptTexture.getWidth()) / 2, snek->viewPort.h / 2);
    gReturnPromptTexture.render(snek->renderer, (snek->mWidth - gReturnPromptTexture.getWidth()) / 2, snek->viewPort.h / 1.5);
    SDL_RenderPresent(snek->renderer);
}
