#include "project_02.10.2025.h"
#include "layout.h"
#include <conio.h>
using namespace std;

int main() {
    const int height = 19; 
    const int width = 36;

    Game game(height, width, Position(17, 11));

    // Music
    CreateThread(0, 0, MusicThread, 0, 0, 0);

    system("title PAC-MAN Console");

    game.LoadLayout(layout);
    game.DrawMap();
    game.DrawHero();
    game.ShowCoins();

    int dir = -1; 
    while (true) {
        Sleep(200); 

        // key processing
        if (_kbhit()) { 
            int key = _getch();
            if (key == 224 && _kbhit()) { 
                dir = _getch();
            }
            else if (key == (int)Key::ESCAPE) break; // exit with ESC
        }

        // hero's journey
        switch (dir) {
        case (int)Key::LEFT:  game.MoveHero(Key::LEFT); break;
        case (int)Key::RIGHT: game.MoveHero(Key::RIGHT); break;
        case (int)Key::UP:    game.MoveHero(Key::UP); break;
        case (int)Key::DOWN:  game.MoveHero(Key::DOWN); break;
        }

        // enemy movement
        game.MoveEnemies();
    }

    return 0;
}