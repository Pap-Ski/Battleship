#include "Game.h"

void playerVScpu(){
	srand(time(0));
	int cpuDifficulty;
	do{
		clearScreen();
		cout << "\n\tCPU DIFFICULTY" << endl;
		cout << "1. Easy\n";
		cout << "2. Medium\n";
		cout << "Select cpu difficulty: ";
		cin >> cpuDifficulty;
	} while (cpuDifficulty != 1 && cpuDifficulty != 2);
	
	clearScreen();
	cout << "\t\t*****PLAYER 1*****\n";
	Player p1;
	p1.setupPlayer();
	cout << "\t\t*****PLAYER 1 READY*****\n";
	//clearScreen();
	Cpu cpu;
	cout << "\nPlayers ready, and all ships postioned!" << endl;
	cout << p1.getName() << " will begin." << endl;
	
	while(!gameOver){
		shoot(p1, cpu);
		if(gameOver)
			break;
		if(cpuDifficulty == 1){
			cpuEasyShoot(cpu, p1);
		} else {
			cpuMediumShoot(cpu,p1);
		}
	}
	
}

void playerVSplayer(){
	clearScreen();
	cout << "\t\t*****PLAYER 1*****\n";
	Player p1;
	p1.setupPlayer();
	cout << "\t\t*****PLAYER 1 READY*****\n";
	clearScreen();
	cout << "\t\t*****PLAYER 2*****\n";
	Player p2;
	p2.setupPlayer();
	cout << "\t\t*****PLAYER 2 READY*****\n";

	cout << "\nPlayers ready, and all ships postioned!" << endl;
	cout << p1.getName() << " will begin." << endl;

	while(!gameOver){
		shoot(p1, p2);
		if(gameOver)
			break;
		shoot(p2, p1);
	}
}

void shoot(Player & player, Cpu & cpu){
	char rowLabel;
	int col, row;
	string pos;

	do{
		player.showPlayerGrid();
		player.showOppGrid();
		cout << player.getName() << " ,enter position to target: ";
		cin  >> pos;
		stringstream ss(pos);
		ss >> rowLabel >> col;
		rowLabel=toupper(rowLabel);
		row = rowLabel-65;

		if(!player.posIsValid(pos)){
			cout << "Invalid Postion" << endl;
		}else{
			if(cpu.getPlayerGrid().getCellData(row,col) == 'X'){
				cout << "Position is already hit" << endl;
				shoot(player,cpu);
				break;
			}else if(player.getOpponentGrid().getCellData(row,col) == 'O'){
				cout << "Position already shot and missed" << endl;
				shoot(player,cpu);
				break;
			}else if(cpu.getPlayerGrid().getCellData(row,col) == ' '){
				player.modifyOppGrid(row,col,'O');
				cpu.modifyPlayerGrid(row,col,'O');
				clearScreen();
				cout << "MISS!! :(" << endl;
				checkWinner(player,cpu);
			} else {
				cpu.modifyPlayerGrid(row,col,'X');
				player.modifyOppGrid(row,col,'X');
				clearScreen();
				cout << "\aHIT!! :)" << endl;
				checkShipSink(cpu.getDestroyer(),cpu,player);
				checkShipSink(cpu.getPatrolBoat(),cpu,player);			
				checkShipSink(cpu.getSubmarine(),cpu,player);
				checkShipSink(cpu.getCarrier(),cpu,player);
				checkShipSink(cpu.getBattelship(),cpu,player);
				player.setHit(true);
				checkWinner(player,cpu);
			}
		}
			
	} while (pos == "1" || !player.posIsValid(pos));
}

void cpuEasyShoot(Cpu & cpu, Player & player){
	hrow = rand() % 10;
	hcol = rand() % 10;
	row = hrow;
	col = hcol;
	
	if(player.getPlayerGrid().getCellData(row,col) == '-'){
		cpuEasyShoot(cpu,player);
	}else if(cpu.getOpponentGrid().getCellData(row,col) == 'O'){
		cpuEasyShoot(cpu,player);
	}else if(cpu.getOpponentGrid().getCellData(row,col) == 'X'){
		cpuEasyShoot(cpu,player);
	}else if(player.getPlayerGrid().getCellData(row,col) == ' '){
		cpu.modifyOppGrid(row,col,'O');
		player.modifyPlayerGrid(row,col,'O');
		cpu.setHit(false);
	} else {
		player.modifyPlayerGrid(row,col,'X');
		cpu.modifyOppGrid(row,col,'X');
		cout << "\a";
		checkShipSink(player.getDestroyer(),player,cpu);
		checkShipSink(player.getPatrolBoat(),player,cpu);
		checkShipSink(player.getSubmarine(),player,cpu);
		checkShipSink(player.getCarrier(),player,cpu);
		checkShipSink(player.getBattelship(),player,cpu);
		cpu.setHit(true);
	}
}

void cpuMediumShoot(Cpu & cpu, Player & player){
	if(cpu.isHit() == false){
		hrow = rand() % 10;
		hcol = rand() % 10;
		row = hrow;
		col = hcol;
	
		if(player.getPlayerGrid().getCellData(row,col) == '-'){
			cpuMediumShoot(cpu,player);
		}else if(cpu.getOpponentGrid().getCellData(row,col) == 'O'){
			cpuMediumShoot(cpu,player);
		}else if(cpu.getOpponentGrid().getCellData(row,col) == 'X'){
			cpuMediumShoot(cpu,player);
		}else if(player.getPlayerGrid().getCellData(row,col) == ' '){
			cpu.modifyOppGrid(row,col,'O');
			player.modifyPlayerGrid(row,col,'O');
			cpu.setHit(false);
		} else {
			player.modifyPlayerGrid(row,col,'X');
			cpu.modifyOppGrid(row,col,'X');
			cout << "\a";
			checkShipSink(player.getDestroyer(),player,cpu);
			checkShipSink(player.getPatrolBoat(),player,cpu);
			checkShipSink(player.getSubmarine(),player,cpu);
			checkShipSink(player.getCarrier(),player,cpu);
			checkShipSink(player.getBattelship(),player,cpu);
			cpu.setHit(true);
		}
	} else {
		if((player.getPlayerGrid().getCellData(row,col+1) != 'O')
		&& (player.getPlayerGrid().getCellData(row,col+1) != '-')
		&& (player.getPlayerGrid().getCellData(row,col+1) != 'X')){
			col++;
			cpuIntelliShoot(cpu,player,row,col);
		} else if((player.getPlayerGrid().getCellData(row+1,col) != 'O')
			&& (player.getPlayerGrid().getCellData(row+1,col) != '-')
			&& (player.getPlayerGrid().getCellData(row+1,col) != 'X')){
			row++;
			cpuIntelliShoot(cpu,player,row,col); 
		} else if((player.getPlayerGrid().getCellData(row,col+1) == 'O')
			|| (player.getPlayerGrid().getCellData(row,col+1) == '-')
			|| (player.getPlayerGrid().getCellData(row,col+1) != 'X')){
			cpu.setHit(false);
		} else if((player.getPlayerGrid().getCellData(row+1,col) == 'O')
			|| (player.getPlayerGrid().getCellData(row+1,col) == '-')
			|| (player.getPlayerGrid().getCellData(row+1,col) != 'X')){
			cpu.setHit(false);
		}
		/*else {
			col = hcol;
			if((player.getPlayerGrid().getCellData(row,col-1) != 'O')
			&& (player.getPlayerGrid().getCellData(row,col-1) != '-')
			&& (player.getPlayerGrid().getCellData(row,col-1) != 'X')
			&& (player.getPlayerGrid().getCellData(row,col-1) != ' ')){
				col--;
				cpuIntelliShoot(cpu,player,row,col);
			}
		}*/
	}
}

void shoot(Player &player, Player &opponent){
	char rowLabel;
	int col, row;
	string pos;
	char symbol;

	do{
		player.showOppGrid();
		cout << player.getName() << " ,enter position to target, "
			<< "or press '1' to view your battleships: ";
		cin  >> pos;
		if(pos == "1"){
			do{
				cout << "Enter secret symbol, "
					<< "or enter '0' to go back: ";
				cin >> symbol;
				if(symbol == player.getSecretChar()){
					player.showPlayerGrid();
				} else if(symbol == '0'){
					shoot(player,opponent);
					break;
				}else{
					cout << "Wrong symbol!" << endl;
				}
			} while(symbol != player.getSecretChar());
		} else {
			stringstream ss(pos);
			ss >> rowLabel >> col;
			rowLabel=toupper(rowLabel);
			row = rowLabel-65;

			if(!player.posIsValid(pos)){
				cout << "Invalid Postion" << endl;
			}else{
				if(opponent.getPlayerGrid().getCellData(row,col) == 'X'){
					cout << "Position is already hit" << endl;
					shoot(player,opponent);
					break;
				}else if(player.getOpponentGrid().getCellData(row,col) == 'O'){
					cout << "Position already shot and missed" << endl;
					shoot(player,opponent);
					break;
				}else if(opponent.getPlayerGrid().getCellData(row,col) == ' '){
					player.modifyOppGrid(row,col,'O');
					opponent.modifyPlayerGrid(row,col,'O');
					player.setHit(false);
					clearScreen();
					cout << "MISS!! :(" << endl;
					cout << opponent.getName() << " plays next." << endl;
					checkWinner(player,opponent);
				} else {
					opponent.modifyPlayerGrid(row,col,'X');
					player.modifyOppGrid(row,col,'X');
					clearScreen();
					cout << "\aHIT!! :)" << endl;
					checkShipSink(opponent.getDestroyer(),opponent,player);
					checkShipSink(opponent.getPatrolBoat(),opponent,player);
					checkShipSink(opponent.getSubmarine(),opponent,player);
					checkShipSink(opponent.getCarrier(),opponent,player);
					checkShipSink(opponent.getBattelship(),opponent,player);
					cout << player.getName() << ", you play again." << endl;
					player.setHit(true);
					checkWinner(player,opponent);
					if(player.isHit() && !gameOver){
						shoot(player,opponent);
						player.setHit(false);
						break;
					} else {
						continue;
					}
				}
			}
		}
	} while (pos == "1" || !player.posIsValid(pos));
}

void checkShipSink(Ship& playerShip,Player& opponent, Player& player){
	if(playerShip.hasSunk == false){
		if(playerShip.getAxis() == 'r'){
			int count = 0;
			for(int i = playerShip.beginningCol; i <= playerShip.endingCol; ++i){
				if(opponent.getPlayerGrid().getCellData(playerShip.beginningRow,i) == 'X'){
					count++;
				}
			}
			if(count == playerShip.getLength()){
				opponent.incnOfSunkShips();
				playerShip.hasSunk = true;
				for(int i = playerShip.beginningCol; i <= playerShip.endingCol; ++i){
					player.modifyOppGrid(playerShip.beginningRow,i,'-');
					opponent.modifyPlayerGrid(playerShip.beginningRow,i,'-');
				}
				cout << "You sunk " << opponent.getName() << "'s " << playerShip.getName() << endl;
			}

		} else if(playerShip.getAxis() == 'l'){
			int count = 0;
			for(int i = playerShip.beginningCol; i >= playerShip.endingCol; --i){
				if(opponent.getPlayerGrid().getCellData(playerShip.beginningRow,i) == 'X'){
					count++;
				}
			}
			if(count == playerShip.getLength()){
				opponent.incnOfSunkShips();
				playerShip.hasSunk = true;
				for(int i = playerShip.beginningCol; i >= playerShip.endingCol; --i){
					player.modifyOppGrid(playerShip.beginningRow,i,'-');
					opponent.modifyPlayerGrid(playerShip.beginningRow,i,'-');
				}
				cout << "You sunk " << opponent.getName() << "'s " << playerShip.getName() << endl;
			}

		} else if(playerShip.getAxis() == 'd'){
			int count = 0;
			for(int i = playerShip.beginningRow; i <= playerShip.endingRow; ++i){
				if(opponent.getPlayerGrid().getCellData(i, playerShip.beginningCol) == 'X')
					count++;
			}
			if(count == playerShip.getLength()){
				opponent.incnOfSunkShips();
				playerShip.hasSunk = true;
				for(int i = playerShip.beginningRow; i <= playerShip.endingRow; ++i){
					player.modifyOppGrid(i, playerShip.beginningCol,'-');
					opponent.modifyPlayerGrid(playerShip.beginningRow,i,'-');
				}
				cout << "You sunk " << opponent.getName() << "'s " << playerShip.getName() << endl;
			}
			
		} else if(playerShip.getAxis() == 'u'){
			int count = 0;
			for(int i = playerShip.beginningRow; i >= playerShip.endingRow; --i){
				if(opponent.getPlayerGrid().getCellData(i, playerShip.beginningCol) == 'X')
					count++;
			}
			if(count == playerShip.getLength()){
				opponent.incnOfSunkShips();
				playerShip.hasSunk = true;
				for(int i = playerShip.beginningRow; i >= playerShip.endingRow; --i){
					player.modifyOppGrid(i, playerShip.beginningCol,'-');
					opponent.modifyPlayerGrid(playerShip.beginningRow,i,'-');
				}
				cout << "You sunk " << opponent.getName() << "'s " << playerShip.getName() << endl;
			}
		}
	}
}

void checkWinner(Player & player, Player & opponent){
	cout << "\n\t********** SUNK SHIPS *********\n\n";
	cout << player.getName() << "'s number of sunk ships: " << player.getnOfSunkShips() << endl;
	cout << opponent.getName() << "'s number of sunk ships: " << opponent.getnOfSunkShips() << endl;
	cout << endl;

	if(player.getnOfSunkShips() == 5 && player.getnOfSunkShips() > opponent.getnOfSunkShips()){
		cout << "\n" << opponent.getName() << " WINS!!!" << endl;
		gameOver = true;
	}else if(opponent.getnOfSunkShips() == 5 && opponent.getnOfSunkShips() > player.getnOfSunkShips()){
		cout << "\n" << player.getName() << " WINS!!!" << endl;
		gameOver = true;
	}
}

void cpuIntelliShoot(Cpu & cpu, Player & player, int row, int col){
	if(player.getPlayerGrid().getCellData(row,col) == ' '){
		cpu.modifyOppGrid(row,col,'O');
		player.modifyPlayerGrid(row,col,'O');
		cpu.setHit(false);
	} else {
		player.modifyPlayerGrid(row,col,'X');
		cpu.modifyOppGrid(row,col,'X');
		cout << "\a";
		checkShipSink(player.getDestroyer(),player,cpu);
		checkShipSink(player.getPatrolBoat(),player,cpu);
		checkShipSink(player.getSubmarine(),player,cpu);
		checkShipSink(player.getCarrier(),player,cpu);
		checkShipSink(player.getBattelship(),player,cpu);
		cpu.setHit(true);
	}
}
