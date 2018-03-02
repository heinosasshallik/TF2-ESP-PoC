#pragma once

#include <vector>
#include "OurPlayer.h"


class ServerData
{
public:
	ServerData();
	~ServerData();

	std::vector<Player*>  readPlayerData();
	int getOurPlayerID() {return 1;} //true for local servers with bots.
	int getNumberOfPlayers();
};

