#ifndef GAME_H
#define GAME_H
#include "Player.h"
#include "Player.cpp"
#include <iostream>
#include <sstream>

bool gameOver = false;
bool hit = false;
void shoot(Player & player, Player & opponent);
void checkShipSink(Ship& playerShip, Player& player, Player& opponent);
void checkWinner(Player & player, Player & opponent);

#endif
