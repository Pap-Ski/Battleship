#ifndef GAME_H
#define GAME_H
//#include "Player.h"
//#include "Player.cpp"
#include "cpu.h"
#include "cpu.cpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <unistd.h>
	
	// Game variables
bool gameOver = false;

	// Cpu shoot variables
int row;
int col;
int hrow;
int hcol; 

void playGame();
void howToPlay();

		// Functions for Multiplayer
void playerVSplayer();
void shoot(Player & player, Player & opponent);
void checkShipSink(Ship& playerShip, Player& opponent, Player& player);
void checkWinner(Player & player, Player & opponent);
		
		// Functions for Single player

void playerVScpu();
void cpuEasyShoot(Cpu & cpu, Player & player);
void cpuMediumShoot(Cpu & cpu, Player & player);
void shoot(Player & player, Cpu & cpu);
void cpuIntelliShoot(Cpu& cpu, Player& player, int row, int col);
#endif
