#pragma once
#include <windows.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

// ======== ENUMS ========
// ���� ������ �� �����
enum class Tile : short { HALL, WALL, COIN, ENEMY };

// ����� ������ � �������
enum class Color : short {
    BLACK, DARKBLUE, DARKGREEN, TURQUOISE, DARKRED,
    PURPLE, DARKYELLOW, GREY, DARKGREY, BLUE, GREEN,
    CYAN, RED, PINK, YELLOW, WHITE
};

// ���� ������ (��� ���������� ������)
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

// ======== ���� ========
class Game {
private:
    int width, height;      // ������� �����
    Tile** map;             // ������������ ������ �����
    Hero hero;              // ������ �����
    vector<Enemy> enemies; // ������ ������
    int coinsCollected;     // ������� ����� �������
    int totalCoins;         // ����� ����� �� �����
    HANDLE h;               // ���������� ������� (��� ���������� �������)

public:
    Game(int hgt, int wdt, Position heroPos); // �����������
    ~Game(); // ����������

    void LoadLayout(const vector<string>& layout); // �������� ����� �� ������� �����
    void DrawMap();    // ���������� ��� �����
    void DrawHero();   // ���������� �����
    void ShowCoins();  // ������� ���������� ��������� �����
    void MoveEnemies(); // ����������� ������
    bool MoveHero(Key dir); // ����������� �����
    void Map(const string& msg); // �������� ��������� � ���-����

    // �������
    int getCollected() const { return this->coinsCollected; }
    int getTotalCoins() const { return this->totalCoins; }
    Position getHeroPos() const { return this->hero.getPos(); }
};

// ======== ������ ========
DWORD WINAPI MusicThread(void* param);

