//
// Created by đỗ quyên on 10/12/24.
//

#ifndef BODYPART_H
#define BODYPART_H
#include "snekCpp.h"
#include "LTexture.h"

class BodyPart {
public:
    int x, y;
    snekCpp* snek;
    BodyPart(snekCpp* game, LTexture &snekBody) {
        texture = &snekBody;
        snek = game;
    }
    BodyPart();

    void updateBodyPosition(int x, int y);

    void render(SDL_Renderer *mRenderer, int snekX, int snekY, int grid);

    static void updateBodyPartsPosition(std::vector<BodyPart> &bodyParts, int snekXBeforeUpdate, int snekYBeforeUpdate);
private:
    LTexture* texture;
};

#endif //BODYPART_H
