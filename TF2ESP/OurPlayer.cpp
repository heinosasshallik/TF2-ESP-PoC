#include "OurPlayer.h"

OurPlayer::OurPlayer() {}

OurPlayer::OurPlayer(int playerID, CHackProcess fp) {
	playerListIndex = playerID;
	fProcess = fp;
}
OurPlayer::~OurPlayer() {}

void OurPlayer::readInformation() {
	ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(fProcess.__dwordClient + offsets.playerListPointer + (offsets.playerListLoopDistance*playerListIndex)), &playerStructPointer, sizeof(DWORD), 0);
	//Get team ID from ourPlayer + teamIDoffset
	ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(playerStructPointer + offsets.teamNumPointer), &teamNum, sizeof(int), 0);
	//Get the location
	ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(playerStructPointer + offsets.playerLocationPointer), &location, sizeof(float[3]), 0);
	//Get the health
	ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(playerStructPointer + offsets.healthPointer), &health, sizeof(int), 0);
	//Get the angle rotations.
	ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(fProcess.__dwordEngine + offsets.angleRotationsPointer), &angleRotations, sizeof(float[2]), 0);
	//Get the field of vision
	//ReadProcessMemory(fProcess.__HandleProcess, (PBYTE*)(fProcess.__dwordClient + offsets.fieldOfVisionPointer), &fieldOfVision, sizeof(float), 0);
	//fieldOfVision = ; // forcing FOV to 90.
}