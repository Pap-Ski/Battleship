#include "Game.h"

void playerVSplayer(){
	cout << "\t\t*****PLAYER 1*****\n";
	Player p1("player");
	cout << "\t\t*****PLAYER 1 READY*****\n";
	clearScreen();
	cout << "\t\t*****PLAYER 2*****\n";
	Player p2("player");
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
				if(opponent.getPlayerGrid().getCellData(row,col) == '-'){
					cout << "Position is already hit" << endl;
					shoot(player,opponent);
					break;
				}else if(player.getOpponentGrid().getCellData(row,col) == 'O'){
					cout << "Position already shot and missed" << endl;
					shoot(player,opponent);
					break;
				}else if(opponent.getPlayerGrid().getCellData(row,col) == ' '){
					player.modifyOppGrid(row,col,'O');
					clearScreen();
					cout << "MISS!! :(" << endl;
					cout << opponent.getName() << " plays next." << endl;
					checkWinner(player,opponent);
				} else {
					opponent.modifyPlayerGrid(row,col,'-');
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

void checkShipSink(Ship& playerShip,Player& player, Player& opponent){
	if(playerShip.hasSunk == false){
		if(playerShip.getAxis() == 'r'){
			int count = 0;
			for(int i = playerShip.beginningCol; i <= playerShip.endingCol; ++i){
				if(player.getPlayerGrid().getCellData(playerShip.beginningRow,i) == '-'){
					count++;
				}
			}
			if(count == playerShip.getLength()){
				player.incnOfSunkShips();
				playerShip.hasSunk = true;
				for(int i = playerShip.beginningCol; i <= playerShip.endingCol; ++i)
					opponent.modifyOppGrid(playerShip.beginningRow,i,'#');
				cout << "You sunk " << player.getName() << "'s " << playerShip.getName() << endl;
			}

		} else if(playerShip.getAxis() == 'l'){
			int count = 0;
			for(int i = playerShip.beginningCol; i >= playerShip.endingCol; --i){
				if(player.getPlayerGrid().getCellData(playerShip.beginningRow,i) == '-'){
					count++;
				}
			}
			if(count == playerShip.getLength()){
				player.incnOfSunkShips();
				playerShip.hasSunk = true;
				for(int i = playerShip.beginningCol; i >= playerShip.endingCol; --i)
					opponent.modifyOppGrid(playerShip.beginningRow,i,'#');
				cout << "You sunk " << player.getName() << "'s " << playerShip.getName() << endl;
			}

		} else if(playerShip.getAxis() == 'd'){
			int count = 0;
			for(int i = playerShip.beginningRow; i <= playerShip.endingRow; ++i){
				if(player.getPlayerGrid().getCellData(i, playerShip.beginningCol) == '-')
					count++;
			}
			if(count == playerShip.getLength()){
				player.incnOfSunkShips();
				playerShip.hasSunk = true;
				for(int i = playerShip.beginningRow; i <= playerShip.endingRow; ++i)
					opponent.modifyOppGrid(i, playerShip.beginningCol,'#');
				cout << "You sunk " << player.getName() << "'s " << playerShip.getName() << endl;
			}
			
		} else if(playerShip.getAxis() == 'u'){
			int count = 0;
			for(int i = playerShip.beginningRow; i >= playerShip.endingRow; --i){
				if(player.getPlayerGrid().getCellData(i, playerShip.beginningCol) == '-')
					count++;
			}
			if(count == playerShip.getLength()){
				player.incnOfSunkShips();
				playerShip.hasSunk = true;
				for(int i = playerShip.beginningRow; i >= playerShip.endingRow; --i)
					opponent.modifyOppGrid(i, playerShip.beginningCol,'#');
				cout << "You sunk " << player.getName() << "'s " << playerShip.getName() << endl;
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
