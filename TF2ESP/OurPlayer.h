#pragma once

#include "Player.h"

class OurPlayer : public Player {
public:
	OurPlayer();
	OurPlayer(int playerID, CHackProcess fp);
	~OurPlayer();
	void readInformation();
};