#include "Game.h"

void playerVScpu(){
	srand(time(0));
	cout << "\t\t*****PLAYER 1*****\n";
	Player p1(5);
	//p1.setupPlayer();
	cout << "\t\t*****PLAYER 1 READY*****\n";
	//clearScreen();
	Cpu cpu;
	cout << "\nPlayers ready, and all ships postioned!" << endl;
	cout << p1.getName() << " will begin." << endl;
	
	while(!gameOver){
		//p1.showPlayerGrid();
		shoot(p1, cpu);
		if(gameOver)
			break;
		shoot(cpu, p1);
	}
	
}

void playerVSplayer(){
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
		player.showPlayerGrid(); // for test
		player.showOppGrid();
		cout << player.getName() << " ,enter postion to target: ";
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
				//cout << player.getName() << ", you play again." << endl;
				//hit = true;
				checkWinner(player,cpu);
				/*if(hit && !gameOver){
					shoot(player,opponent);
					hit = false;
					break;
				} else {
					continue;
				}*/
			}
		}
			
	} while (pos == "1" || !player.posIsValid(pos));
}

void shoot(Cpu & cpu, Player & player){

	int row, col;
	row = rand() % 10;
	col = rand() % 10;
	//row = 1; col = 0;
	
	if(player.getPlayerGrid().getCellData(row,col) == '-'){
		shoot(cpu,player);
	}else if(cpu.getOpponentGrid().getCellData(row,col) == 'O'){
		shoot(cpu,player);
	}else if(player.getPlayerGrid().getCellData(row,col) == ' '){
		cpu.modifyOppGrid(row,col,'O');
		player.modifyPlayerGrid(row,col,'O');
	} else {
		player.modifyPlayerGrid(row,col,'X');
		cpu.modifyOppGrid(row,col,'X');
		cout << "\a";
		checkShipSink(player.getDestroyer(),player,cpu);
		checkShipSink(player.getPatrolBoat(),player,cpu);
		checkShipSink(player.getSubmarine(),player,cpu);
		checkShipSink(player.getCarrier(),player,cpu);
		checkShipSink(player.getBattelship(),player,cpu);
		hit = true;
		/*cout << player.getName() << ", you play again." << endl;
		checkWinner(player,opponent);
		if(hit && !gameOver){
			shoot(player,opponent);
			hit = false;
			break;
		} else {
			continue;
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
		cout << player.getName() << " ,enter postion to target, "
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
					hit = true;
					checkWinner(player,opponent);
					if(hit && !gameOver){
						shoot(player,opponent);
						hit = false;
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
