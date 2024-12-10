//
// Created by đỗ quyên on 10/12/24.
//


#include "bodyPart.h"
#include "LDeltaTime.h"
#include "GameScreen.h"

// Move snek
void GameScreen::moveSnek() {
    snekXBeforeUpdate = snekX;
    snekYBeforeUpdate = snekY;
    switch (currentDirection) {
        case UP:
            snekY -= grid;
            break;
        case DOWN:
            snekY += grid;
            break;
        case LEFT:
            snekX -= grid;
            break;
        case RIGHT:
            snekX += grid;
            break;
        default:
            break;
    }
}

// Check if snek is dead
bool GameScreen::checkForDeath() {
    for (BodyPart bodyPart : bodyParts) {
        if (snekX == bodyPart.x && snekY == bodyPart.y) {
            return true;
        }
    }
    return false;
}

// Execute snek dead animation
void GameScreen::snekDead() {
    stateTime += deltaTime->getDeltaTime();
    timeElapsed += deltaTime->getDeltaTime();
    if (stateTime >= frameDuration) {
        stateTime = 0.f;
        currentFrame++;
        if (currentFrame >= MAX_FRAMES) {
            currentFrame = 0;
        }
    }
    snekDeathSpriteSheet.render(snek->renderer, snekX + snek->viewPort.x, snekY + snek->viewPort.y, grid, grid, &snekDeathAnim[currentFrame]);
}

// Check if snek is out of bounds
void GameScreen::checkForOutOfBounds() {
    if (snekX >= snek->viewPort.x + snek->viewPort.w) {
        snekX = snek->viewPort.x;
    }
    else if (snekX < snek->viewPort.x) {
        snekX = snek->viewPort.x + snek->viewPort.w - grid;
    }
    if (snekY >= snek->viewPort.y + snek->viewPort.h) {
        snekY = snek->viewPort.y;
    }
    else if (snekY < snek->viewPort.y) {
        snekY = snek->viewPort.y + snek->viewPort.h - grid;
    }
}
