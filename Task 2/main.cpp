#include <cstdlib>
#include <ctime>
#include "GameSession.h"

int main() {
    srand(time(0)); // inisialisasi random seed untuk enemy AI

    GameSession game;
    game.StartGame();

    return 0;
}
