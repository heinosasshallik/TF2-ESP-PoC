#include "ServerData.h"




ServerData::ServerData()
{
}


ServerData::~ServerData()
{
}

int ServerData::getNumberOfPlayers() {
	int numberOfPlayers;
	Offsets offsets;
	ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(fProcess.__dwordServer + offsets.numberOfPlayersPointer), &numberOfPlayers, sizeof(int), 0);
	return numberOfPlayers;
}

//function for reading out the data of all players.
std::vector<Player*> ServerData::readPlayerData() {
	std::vector<Player*> players;

	//Memory leak clean up.
	for (unsigned int i = 0; i < players.size(); i++) {
		delete players[i];
	}
	players.clear();

	//Using vector of base class pointers to get a vector of polymorphic objects
	for (int i = 0; i < getNumberOfPlayers(); i++) {
		if (i == getOurPlayerID() - 1) {
			Player* ourPlayer = new OurPlayer(i + 1, fProcess);
			ourPlayer->readInformation();
			players.push_back(ourPlayer);

		}
		else {
			Player* player = new Player(i + 1, fProcess);
			player->readInformation();
			players.push_back(player);
		}
	}
	return players;
}
