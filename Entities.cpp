#include "project_02.10.2025.h"

void Hero::Draw(HANDLE h) const {
    COORD c = { (SHORT)this->pos.x, (SHORT)this->pos.y };
    SetConsoleCursorPosition(h, c);
    SetConsoleTextAttribute(h, (int)Color::YELLOW);
    cout << "C";
}

void Enemy::Draw(HANDLE h) const {
    COORD c = { (SHORT)this->pos.x, (SHORT)this->pos.y };
    SetConsoleCursorPosition(h, c);
    SetConsoleTextAttribute(h, (int)Color::RED);
    cout << "O";
}