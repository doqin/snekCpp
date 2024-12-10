//
// Created by đỗ quyên on 10/12/24.
//

#ifndef ENDINGSCREEN_H
#define ENDINGSCREEN_H
#include "LTexture.h"
#include "snekCpp.h"

class CGameState;

class EndingScreen final : public CGameState{
public:
    snekCpp* snek;

    LTexture gDeathTexture;
    LTexture gScoreTexture;
    LTexture gRestartPromptTexture;
    LTexture gReturnPromptTexture;

    SDL_Color textColor = {0xFF, 0xFF, 0xFF, 0xFF};

    EndingScreen(snekCpp* game);

    ~EndingScreen() override;

    void Init() override;

    void Cleanup() override;

    void Pause() override;

    void Resume() override;

    void HandleEvents() override;

    void Update() override;

    void Draw() override;
};



#endif //ENDINGSCREEN_H
