//
// Created by đỗ quyên on 10/12/24.
//

#include "bodyPart.h"
#include "GameScreen.h"

void GameScreen::checkAndPlaceApple() {
    if (!appleAvailable) {
        bool appleBodyCollide;
        do {
            appleBodyCollide = false;
            appleX = rand() % (snek->viewPort.w / grid - 1) * grid;
            appleY = rand() % (snek->viewPort.h / grid - 1) * grid;
            for (BodyPart bodyPart : bodyParts) {
                if (appleX == bodyPart.x && appleY == bodyPart.y) {
                    appleBodyCollide = true;
                    break;
                }
            }
            if (appleX == snekX && appleY == snekY) {
                appleBodyCollide = true;
            }
        } while (appleBodyCollide);
        appleAvailable = true;
    }
    apple.render(snek->renderer, appleX + snek->viewPort.x, appleY + snek->viewPort.y, grid, grid);
}

void GameScreen::checkAppleCollision() {
    if (appleAvailable && snekX == appleX && snekY == appleY) {
        appleAvailable = false;
        applesEaten++;
        BodyPart bodyPart;
        bodyPart.updateBodyPosition(snekXBeforeUpdate, snekYBeforeUpdate);
        bodyParts.insert(bodyParts.begin(), bodyPart);
        if (MOVE_TIME > MOVE_TIME_MIN && applesEaten % 2 == 0) {
            MOVE_TIME -= MOVE_TIME_DECREMENT;
        }
    }
}
