#pragma once
#include "HackProcess.h"
#include "Offsets.h"
#include <vector>

class Player
{

public:
	Player();
	Player(int playerID, CHackProcess fp);
	virtual ~Player();
	int playerListIndex; //index in PlayerList array.index = playerID -1
	DWORD playerStructPointer; // pointer to the Player struct
	int teamNum;
	int health;
	float location[3]; //x y z
	std::vector<float> aimAngles; //the angles needed to aim at the guy (vertical, horizontal, 0)
	Offsets offsets;
	CHackProcess fProcess;
	virtual void readInformation();
	//int getNumberOfPlayers(); //Implemented in main.cpp. 
	//we will also add the subclass variables and methods. https://stackoverflow.com/questions/2559854/accessing-subclass-members-from-a-superclass-pointer-c andreas bonini's answer
	float angleRotations[2]; //where he's aiming (vertical, horizontal)
	//Vertical(might need to be corrected to the right/left a bit), Horizontal.
	double fieldOfVision[2] = { 33.3, 54}; //our player's FOV in degrees in either direction.
};