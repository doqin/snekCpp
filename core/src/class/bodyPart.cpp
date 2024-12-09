//
// Created by đỗ quyên on 10/12/24.
//

#include "snekCpp.h"
#include "GameScreen.h"
#include "bodyPart.h"

BodyPart::BodyPart() {
}

void BodyPart::updateBodyPosition(const int x, const int y) {
    this->x = x;
    this->y = y;
}

void BodyPart::render(SDL_Renderer *mRenderer, const int snekX, const int snekY, const int grid) {
    if (x != snekX || y != snekY) {
        texture->render(mRenderer, x + snek->viewPort.x, y + snek->viewPort.y, grid, grid);
    }
}

void BodyPart::updateBodyPartsPosition(std::vector<BodyPart> &bodyParts, const int snekXBeforeUpdate, const int snekYBeforeUpdate) {
    // Update the body part position
    if (bodyParts.size() > 0) {
        bodyParts.erase(bodyParts.begin());
        BodyPart bodypart;
        bodypart.updateBodyPosition(snekXBeforeUpdate, snekYBeforeUpdate);
        bodyParts.push_back(bodypart);
    }
}

