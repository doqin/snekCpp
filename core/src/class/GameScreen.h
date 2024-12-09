
#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <SDL_events.h>

class GameScreen final : public CGameState {
public:
    static SDL_Event e;

    static snekCpp* snek;

    static LTexture gMenuBackground;

    GameScreen(snekCpp* game);
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

    static GameScreen* Instance() {
        return &mGameScreen;
    }
private:
    static GameScreen mGameScreen;
};

inline GameScreen::GameScreen(snekCpp* game) {
    this->snek = game;
}

#endif //GAMESCREEN_H
