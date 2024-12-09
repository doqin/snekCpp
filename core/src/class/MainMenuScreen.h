
#ifndef MAINMENUSCREEN_H
#define MAINMENUSCREEN_H

#include <SDL_events.h>
#include "LTexture.h"
#include "snekCpp.h"

class CGameState;

class MainMenuScreen final : public CGameState {
public:
    SDL_Event e;

    snekCpp* snek;

    LTexture gMenuBackground;

    MainMenuScreen(snekCpp* game);
    void Init() override;
    void Cleanup() override;

    void Pause() override;
    void Resume() override;

    void HandleEvents() override;
    void Update() override;
    void Draw() override;

    static void ChangeState(snekCpp* game, CGameState* state) {
        game->ChangeState(state);
    }
};

#endif //MAINMENUSCREEN_H