//
// Created by đỗ quyên on 10/12/24.
//

#include "GameScreen.h"
#include "bodyPart.h"
#include "EndingScreen.h"

GameScreen::GameScreen(snekCpp *game) {
    this->snek = game;
}

void GameScreen::Init() {
    // Initialize delta time
    deltaTime = new LDeltaTime();

    // Reset positions
    snekXBeforeUpdate = 0, snekYBeforeUpdate = 0;

    // Set seconds per frame for death animation
    frameDuration = 0.25f;

    // Set current frame for death animation
    currentFrame = 0;

    //Update viewPort
    if (snek->mWidth <= snek->mHeight)
        snek->viewPort = {0, (snek->mHeight - snek->mWidth) / 2, snek->mWidth, snek->mWidth};
    else
        snek->viewPort = {(snek->mWidth - snek->mHeight) / 2, 0, snek->mHeight, snek->mHeight};

    // Set grid size
    grid = snek->viewPort.w / 20;

    // Load textures
    snekHead.loadFromFile(snek->renderer, "../assets/snek_head.png");
    snekBody.loadFromFile(snek->renderer, "../assets/snek_body.png");
    snekDeathSpriteSheet.loadFromFile(snek->renderer, "../assets/snek_death_spritesheet.png");
    apple.loadFromFile(snek->renderer, "../assets/apple.png");

    snekDeathAnim = new SDL_Rect[MAX_FRAMES];
    // Set sprite clips
    int offsetX = 0;
    for (int i = 0; i < MAX_FRAMES; ++i) {
        snekDeathAnim[i] = {offsetX, 0, CLIP_WIDTH, CLIP_HEIGHT};
        offsetX += CLIP_WIDTH;
    }

    // Set snekX and snekY positions
    snekX = snek->viewPort.w / 2;
    snekY = snek->viewPort.h / 2;

    MOVE_TIME_DECREMENT = .01f;
    MOVE_TIME_MIN = .08f;
    MOVE_TIME = MOVE_TIME_INIT;
    applesEaten = 0;
    appleAvailable = false;
    stateTime = 0.f;
    timeElapsed = 0.f;
    currentDirection = RIGHT;
    directions.push_back(RIGHT);
}

void GameScreen::Cleanup() {
    snekHead.free();
    snekBody.free();
    apple.free();
    snek = nullptr;
    delete[] snekDeathAnim;
    snekDeathAnim = nullptr;
    delete deltaTime;
    deltaTime = nullptr;
    snekDeathSpriteSheet.free();
    delete this;
}

void GameScreen::Pause() {
}

void GameScreen::Resume() {
}

void GameScreen::HandleEvents() {
    // Event handler
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                snek->Quit();
                break;
            case SDL_KEYDOWN:
                if (e.key.repeat == 0) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        if (directions.size() < 3)
                            if (directions.back() != DOWN) {
                                directions.push_back(UP);
                            }
                        else {
                            if (directions.back() != DOWN) {
                                directions.pop_back();
                                directions.push_back(UP);
                            }
                        }
                    break;
                    case SDLK_DOWN:
                        if (directions.size() < 3)
                            if (directions.back() != UP) {
                                directions.push_back(DOWN);
                            }
                        else {
                            if (directions.back() != UP) {
                                directions.pop_back();
                                directions.push_back(DOWN);
                            }
                        }
                    break;
                    case SDLK_LEFT:
                        if (directions.size() < 3)
                            if (directions.back() != RIGHT) {
                                directions.push_back(LEFT);
                            }
                        else {
                            if (directions.back() != RIGHT) {
                                directions.pop_back();
                                directions.push_back(LEFT);
                            }
                        }
                    break;
                    case SDLK_RIGHT:
                        if (directions.size() < 3)
                            if (directions.back() != LEFT) {
                                directions.push_back(RIGHT);
                            }
                        else {
                            if (directions.back() != LEFT) {
                                directions.pop_back();
                                directions.push_back(RIGHT);
                            }
                        }
                    break;
                    default:
                        break;
                    }
                }
                break;
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
                    grid = snek->viewPort.w / 20;
                    break;
                    default:
                        break;
                }
            default: break;
        }
    }
}


void GameScreen::Update() {
    deltaTime->update();
    if (!isDead) {
        timer -= deltaTime->getDeltaTime();
        if (timer <= 0) {
            timer = MOVE_TIME;
            moveSnek();
            if (directions.size() > 1) {
                directions.erase(directions.begin());
            }
            currentDirection = directions.front();

            isDead = checkForDeath();
            checkForOutOfBounds();
            BodyPart::updateBodyPartsPosition(snek, this, bodyParts, snekXBeforeUpdate, snekYBeforeUpdate);
        }
        checkAppleCollision();
    }
    if (timeElapsed >= 2.f) {
        snek->ChangeState(new EndingScreen(snek));
    }
}

void GameScreen::Draw() {
    // Clear screen
    SDL_SetRenderDrawColor(snek->renderer, 0x2F, 0x2F, 0x2F, 0xFF);
    SDL_RenderClear(snek->renderer);

    // Draw background color
    SDL_SetRenderDrawColor(snek->renderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderFillRect(snek->renderer, &snek->viewPort);

    if (!isDead)
        snekHead.render(snek->renderer, snekX + snek->viewPort.x, snekY + snek->viewPort.y, grid, grid);
    else
        snekDead();
    for (BodyPart bodyPart : bodyParts) {
        bodyPart.render(snek->renderer, snekX, snekY, grid);
    }
    checkAndPlaceApple();

    // Update screen
    SDL_RenderPresent(snek->renderer);
}
