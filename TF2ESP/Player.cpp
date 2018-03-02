#include "Player.h"


//default constructor
Player::Player() {}
Player::~Player() {}


Player::Player(int playerIndex, CHackProcess fp) {
	playerListIndex = playerIndex;
	fProcess = fp;
}

void Player::readInformation() {
	ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(fProcess.__dwordClient + offsets.playerListPointer + (offsets.playerListLoopDistance*playerListIndex)), &playerStructPointer, sizeof(DWORD), 0);
	//Get team ID from ourPlayer + teamIDoffset
	ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(playerStructPointer + offsets.teamNumPointer), &teamNum, sizeof(int), 0);
	//Get the location
	ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(playerStructPointer + offsets.playerLocationPointer), &location, sizeof(float[3]), 0);
	//Get the health
	ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(playerStructPointer + offsets.healthPointer), &health, sizeof(int), 0);
}

/*int Player::getNumberOfPlayers() {
	int numberOfPlayers;
	ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(fProcess.__dwordServer + offsets.numberOfPlayersPointer), &numberOfPlayers, sizeof(int), 0);
	return numberOfPlayers;
}*/