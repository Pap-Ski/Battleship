#ifndef GAME_H
#define GAME_H
//#include "Player.h"
//#include "Player.cpp"
#include "cpu.h"
#include "cpu.cpp"
#include <iostream>
#include <sstream>
#include <cstdlib>

bool gameOver = false;
bool hit = false;

		// Functions for Multiplayer
void playerVSplayer();
void shoot(Player & player, Player & opponent);
void checkShipSink(Ship& playerShip, Player& opponent, Player& player);
void checkWinner(Player & player, Player & opponent);
		
		// Functions for Single player
void playerVScpu();
void shoot(Cpu & cpu, Player & player);
void shoot(Player & player, Cpu & cpu);
#endif
