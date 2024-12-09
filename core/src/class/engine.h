
#ifndef ENGINE_H
#define ENGINE_H

#include <vector>
#include <SDL.h>

class CGameState;

class CGameEngine {
public:
    int mHeight;
    int mWidth;

    virtual void Init(const char *title, int width, int height, bool fullscreen);

    virtual void Cleanup();

    virtual void ChangeState(CGameState *state);

    virtual void PushState(CGameState *state);

    virtual void PopState();

    virtual void HandleEvents();

    virtual void Update();

    virtual void Draw();

    virtual bool Running() const { return mRunning; }
    virtual void Quit() { mRunning = false; }

    SDL_Window *screen;
    SDL_Renderer *renderer;

protected:
    ~CGameEngine() = default;

    CGameEngine() = default;

    // The stack of states
    std::vector<CGameState *> states;

    bool mFullscreen;
    bool mRunning;
};

#endif //ENGINE_H
