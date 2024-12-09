
#include "snekCpp.h"
#include "MainMenuScreen.h"

int main (int argc, char *argv[]) {
    // Create the game engine
    snekCpp game;

    // Initialize game
    game.Init("snekCpp", 600, 600, false);

    game.ChangeState(new MainMenuScreen(&game));

    // main loop
    while ( game.Running() )
    {
        game.HandleEvents();
        game.Update();
        game.Draw();
    }

    // cleanup the engine
    game.Cleanup();
}