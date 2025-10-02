#include "project_02.10.2025.h"
using namespace std;

// ======== GAME ========
Game::Game(int hgt, int wdt, Position heroPos)
    : height(hgt), width(wdt), hero(heroPos),
    coinsCollected(0), totalCoins(0) {

    this->h = GetStdHandle(STD_OUTPUT_HANDLE);

    // Hide the blinking cursor
    CONSOLE_CURSOR_INFO cursor{ 100, FALSE };
    SetConsoleCursorInfo(this->h, &cursor);

    // create a two-dimensional array for the map
    map = new Tile * [height];
    for (int i = 0; i < height; i++)
        map[i] = new Tile[width];
}

// Destructor
Game::~Game() {
    for (int i = 0; i < height; i++)
        delete[] map[i];
    delete[] map;

    SetConsoleTextAttribute(h, (int)Color::WHITE);
}

// Working with files
void Game::Map(const string& msg) {
    ofstream f("map.txt", std::ios::app); 
    if (f.is_open()) f << msg << "\n"; 
}

// Loading a map from an array of strings
void Game::LoadLayout(const vector<string>& layout) {
    this->enemies.clear();
    this->totalCoins = 0;

    for (int y = 0; y < this->height; y++) {
        for (int x = 0; x < this->width; x++) {
            char ch = layout[y][x];
            switch (ch) {
            case '#': this->map[y][x] = Tile::WALL; break;
            case '.': this->map[y][x] = Tile::COIN; this->totalCoins++; break;
            case 'E': this->map[y][x] = Tile::ENEMY; this->enemies.emplace_back(Position(x, y)); break;
            default:  this->map[y][x] = Tile::HALL;
            }
        }
    }
    this->Map("Map loaded"); 
}

// Drawing the entire map
void Game::DrawMap() {
    for (int y = 0; y < this->height; y++) {
        for (int x = 0; x < this->width; x++) {
            switch (this->map[y][x]) {
            case Tile::HALL:  SetConsoleTextAttribute(this->h, (int)Color::BLACK); cout << " "; break;
            case Tile::WALL:  SetConsoleTextAttribute(this->h, (int)Color::BLUE); cout << (char)178; break;
            case Tile::COIN:  SetConsoleTextAttribute(this->h, (int)Color::YELLOW); cout << "."; break;
            case Tile::ENEMY: SetConsoleTextAttribute(this->h, (int)Color::RED); cout << "O"; break;
            }
        }
        cout << "\n";
    }
}

// Draw a hero
void Game::DrawHero() { this->hero.Draw(this->h); }

// Show the number of coins
void Game::ShowCoins() {
    COORD c = { (SHORT)(this->width + 2), 0 };
    SetConsoleCursorPosition(this->h, c);
    SetConsoleTextAttribute(this->h, (int)Color::DARKYELLOW);
    cout << "COINS: ";
    SetConsoleTextAttribute(this->h, (int)Color::YELLOW);
    cout << this->coinsCollected;
}

// Enemy movement (towards the hero)
void Game::MoveEnemies() {
    for (auto& e : this->enemies) {
        Position p = e.getPos();

        COORD old = { (SHORT)p.x, (SHORT)p.y };
        SetConsoleCursorPosition(this->h, old);
        SetConsoleTextAttribute(this->h, (int)Color::BLACK);
        cout << " ";
        this->map[p.y][p.x] = Tile::HALL;

        int dx = (this->hero.getPos().x > p.x) ? 1 : (this->hero.getPos().x < p.x ? -1 : 0);
        int dy = (this->hero.getPos().y > p.y) ? 1 : (this->hero.getPos().y < p.y ? -1 : 0);

        if (dx != 0 && this->map[p.y][p.x + dx] != Tile::WALL) p.x += dx;
        else if (dy != 0 && this->map[p.y + dy][p.x] != Tile::WALL) p.y += dy;

        if (p.x == this->hero.getPos().x && p.y == this->hero.getPos().y) {
            PlaySoundA("PacMan-Death-Sound-Effect-HD.wav", NULL, SND_FILENAME | SND_SYNC);
            COORD msg = { 0, (SHORT)(this->height + 1) };
            SetConsoleCursorPosition(this->h, msg);
            SetConsoleTextAttribute(this->h, (int)Color::RED);
            cout << "YOU WERE CAUGHT! GAME OVER!\n";
            exit(0);
        }

        e.setPos(p);
        e.Draw(this->h);
        this->map[p.y][p.x] = Tile::ENEMY;
    }
}

// The hero's movement
bool Game::MoveHero(Key dir) {
    Position old = this->hero.getPos();
    Position np = old;

    if (dir == Key::LEFT)  np.x = (old.x == 0) ? this->width - 1 : old.x - 1;
    if (dir == Key::RIGHT) np.x = (old.x == this->width - 1) ? 0 : old.x + 1;
    if (dir == Key::UP && old.y > 0) np.y--;
    if (dir == Key::DOWN && old.y < this->height - 1) np.y++;

    if (this->map[np.y][np.x] == Tile::WALL) return false;

    COORD oc = { (SHORT)old.x, (SHORT)old.y };
    SetConsoleCursorPosition(this->h, oc);
    SetConsoleTextAttribute(this->h, (int)Color::BLACK);
    cout << " ";

    this->hero.setPos(np);
    this->hero.Draw(this->h);

    if (this->map[np.y][np.x] == Tile::COIN) {
        this->coinsCollected++;
        this->map[np.y][np.x] = Tile::HALL;
        this->ShowCoins();

        if (this->coinsCollected == this->totalCoins) {
            COORD win = { 0, (SHORT)(this->height + 2) };
            SetConsoleCursorPosition(this->h, win);
            SetConsoleTextAttribute(this->h, (int)Color::GREEN);
            cout << "CONGRATULATIONS! YOU WON!\n";
            exit(0);
        }
    }
    return true;
}


