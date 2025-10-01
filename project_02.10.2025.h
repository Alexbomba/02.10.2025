#pragma once
#include <windows.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

// ======== ENUMS ========
// Cell types on the map
enum class Tile : short { HALL, WALL, COIN, ENEMY };

// Text colors in the console
enum class Color : short {
    BLACK, DARKBLUE, DARKGREEN, TURQUOISE, DARKRED,
    PURPLE, DARKYELLOW, GREY, DARKGREY, BLUE, GREEN,
    CYAN, RED, PINK, YELLOW, WHITE
};

// Key codes (for controlling the character)
enum class Key : short {
    LEFT = 75, RIGHT = 77, UP = 72, DOWN = 80,
    ENTER = 13, SPACE = 32, ESCAPE = 27, BACKSPACE = 8
};

// ======== STRUCTS ========
struct Position {
    int x, y;
    Position(int xx = 0, int yy = 0) : x(xx), y(yy) {}
};

// ======== BASE CLASS ========
class GameObject {
protected:
    Position pos;
public:
    GameObject(Position p) : pos(p) {}
    virtual ~GameObject() {}

    virtual void Draw(HANDLE h) const = 0;

    // Accessors
    Position getPos() const { return this->pos; }
    void setPos(Position p) { this->pos = p; }
};

// ======== HERO ========
class Hero : public GameObject {
public:
    Hero(Position p) : GameObject(p) {}
    void Draw(HANDLE h) const override; 
};

// ======== ENEMY ========
class Enemy : public GameObject {
public:
    Enemy(Position p) : GameObject(p) {}
    void Draw(HANDLE h) const override; 
};

// ======== ИГРА ========
class Game {
private:
    int width, height;      //card dimensions
    Tile** map;             // dynamic map array
    Hero hero;              // hero's object
    vector<Enemy> enemies;  // list of enemies
    int coinsCollected;     // how many coins have been collected
    int totalCoins;         // total coins on the map
    HANDLE h;               // console descriptor (for output control)

public:
    Game(int hgt, int wdt, Position heroPos); // designer
    ~Game(); // деструктор

    void LoadLayout(const vector<string>& layout); // loading a map from an array of strings
    void DrawMap();    // draw the entire map
    void DrawHero();   // draw a hero
    void ShowCoins();  // display the number of coins collected
    void MoveEnemies(); // move enemies
    bool MoveHero(Key dir); // move the hero
    void Map(const string& msg); // write a message to the log file

    // Getters
    int getCollected() const { return this->coinsCollected; }
    int getTotalCoins() const { return this->totalCoins; }
    Position getHeroPos() const { return this->hero.getPos(); }
};

// ======== MUSIC ========
DWORD WINAPI MusicThread(void* param);

