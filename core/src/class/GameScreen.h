
#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include <vector>
#include "LTexture.h"
#include "snekCpp.h"
#include "state.h"
#include "LDeltaTime.h"
#include "bodyPart.h"

class GameScreen final : public CGameState {
public:

    // Snek directions
    enum Direction {
        UP,
        DOWN,
        LEFT,
        RIGHT
    };

    // Delta time
    LDeltaTime* deltaTime;

    // Snek directions
    std::vector<Direction> directions;
    Direction currentDirection;

    const float MOVE_TIME_INIT = .2f;
    float MOVE_TIME;
    float MOVE_TIME_DECREMENT;
    float MOVE_TIME_MIN;
    static constexpr int MAX_FRAMES = 2;
    const int CLIP_WIDTH = 100;
    const int CLIP_HEIGHT = 100;
    int grid;

    // Snek game
    snekCpp* snek;

    // Textures
    LTexture snekHead;
    LTexture snekDeathSpriteSheet;
    LTexture snekBody;
    LTexture apple;

    // Snek positions
    int snekX, snekY;
    int snekXBeforeUpdate, snekYBeforeUpdate;

    // Sprite clips
    SDL_Rect* snekDeathAnim;

    // Animation variables
    float frameDuration;
    int currentFrame;

    // Apple variables
    bool appleAvailable;
    int appleX, appleY;
    int applesEaten;

    // Time since death
    float timeElapsed;
    float stateTime;

    // Snek body
    std::vector<BodyPart> bodyParts;

    void checkAndPlaceApple();
    void checkAppleCollision();
    void moveSnek();
    bool checkForDeath();
    void snekDead();
    void checkForOutOfBounds();


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


private:

    // Time between moves
    float timer = MOVE_TIME_INIT;

    // Dead state
    bool isDead = false;
};

#endif //GAMESCREEN_H
