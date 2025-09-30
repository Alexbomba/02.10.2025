#include "project_02.10.2025.h"
#include <conio.h>

using namespace std;

int main() {
    const int height = 19; 
    const int width = 36;

    // Карта
    vector<string> layout = {
        "###################################",
        "#................#................#",
        "#.#####.########.#.########.#####.#",
        "#.................................#",
        "#.#####.#.###############.#.#####.#",
        "#.......#........#........#.......#",
        "#######.########.#.########.#######",
        "      #.#........ ........#.#      ",
        "#######.#.###### E ######.#.#######",
        "       ...#             #...       ",
        "#######.#.###############.#.#######",
        "      #.#.................#.#      ",
        "#######.########.#.########.#######",
        "#.......#........#........#.......#",
        "#.#####.#.###############.#.#####.#",
        "#.................................#",
        "#.#####.########.#.########.#####.#",
        "#................#................#",
        "###################################"
    };

    Game game(height, width, Position(17, 11));

    // музыка
    CreateThread(0, 0, MusicThread, 0, 0, 0);

    system("title PAC-MAN Console");

    game.LoadLayout(layout);
    game.DrawMap();
    game.DrawHero();
    game.ShowCoins();

    int dir = -1; 
    while (true) {
        Sleep(200); 

        // обработка клавиш
        if (_kbhit()) { 
            int key = _getch();
            if (key == 224 && _kbhit()) { 
                dir = _getch();
            }
            else if (key == (int)Key::ESCAPE) break; // выход по ESC
        }

        // движение героя
        switch (dir) {
        case (int)Key::LEFT:  game.MoveHero(Key::LEFT); break;
        case (int)Key::RIGHT: game.MoveHero(Key::RIGHT); break;
        case (int)Key::UP:    game.MoveHero(Key::UP); break;
        case (int)Key::DOWN:  game.MoveHero(Key::DOWN); break;
        }

        // движение врагов
        game.MoveEnemies();
    }

    return 0;
}