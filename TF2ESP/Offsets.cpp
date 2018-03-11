#include "Offsets.h"



Offsets::Offsets()
{
	teamNumPointer = 0xB0; //offset to teamnumber from Player struct.BLU is 3, RED is 2
	healthPointer = 0xA8;
	playerLocationPointer = 0x28C; //offset from Player struct.

	numberOfPlayersPointer = 0x8E9718; //SERVER.DLL. find out how many players in-game.

	//is multi-level pointer: the real pointer is at *( *(client.dll+[0]) + [1]) + [2]
	//if these change, then there are other options you can try as well in the guide.
	//crosshairIDPointerOffsets[3] = { 0x00C8CCC4,0x50,0x1CC };


	//list of Players. ourPlayer is list[0], list[1] is offset from list[0] by 0x10.
	playerListPointer = 0x00C41D0C;
	playerListLoopDistance = 0x10; //list[1] is list[0] + ....
	ourPlayerPointer = playerListPointer;//ourPlayer is playerList[0].

	angleRotationsPointer = 0x495464; //ENGINE.DLL. 2 floats. 1 vertical 1 horizontal
	//fieldOfVisionPointer = 0xC8C7D4; //client.dll -- unused
}


Offsets::~Offsets()
{
}
