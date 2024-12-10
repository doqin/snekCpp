#ifndef STATE_H
#define STATE_H
#include "engine.h"

class CGameState {
public:
    CGameState() = default;
    virtual ~CGameState() = default;

    virtual void Init() = 0;
    virtual void Cleanup() = 0;

    virtual void Pause() = 0;
    virtual void Resume() = 0;

    virtual void HandleEvents() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;

    static void ChangeState(CGameEngine* game, CGameState* state) {
        game->ChangeState(state);
    }
};

#endif //STATE_H
