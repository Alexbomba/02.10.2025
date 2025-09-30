#pragma once
#include <windows.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

// ======== ENUMS ========
// Типы клеток на карте
enum class Tile : short { HALL, WALL, COIN, ENEMY };

// Цвета текста в консоли
enum class Color : short {
    BLACK, DARKBLUE, DARKGREEN, TURQUOISE, DARKRED,
    PURPLE, DARKYELLOW, GREY, DARKGREY, BLUE, GREEN,
    CYAN, RED, PINK, YELLOW, WHITE
};

// Коды клавиш (для управления героем)
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
    int width, height;      // размеры карты
    Tile** map;             // динамический массив карты
    Hero hero;              // объект героя
    vector<Enemy> enemies; // список врагов
    int coinsCollected;     // сколько монет собрано
    int totalCoins;         // всего монет на карте
    HANDLE h;               // дескриптор консоли (для управления выводом)

public:
    Game(int hgt, int wdt, Position heroPos); // конструктор
    ~Game(); // деструктор

    void LoadLayout(const vector<string>& layout); // загрузка карты из массива строк
    void DrawMap();    // нарисовать всю карту
    void DrawHero();   // нарисовать героя
    void ShowCoins();  // вывести количество собранных монет
    void MoveEnemies(); // передвинуть врагов
    bool MoveHero(Key dir); // передвинуть героя
    void Map(const string& msg); // записать сообщение в лог-файл

    // Геттеры
    int getCollected() const { return this->coinsCollected; }
    int getTotalCoins() const { return this->totalCoins; }
    Position getHeroPos() const { return this->hero.getPos(); }
};

// ======== МУЗЫКА ========
DWORD WINAPI MusicThread(void* param);

