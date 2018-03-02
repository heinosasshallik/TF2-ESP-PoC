#pragma once
#include <Windows.h>

class Offsets
{
public:
	Offsets();
	~Offsets();
	DWORD teamNumPointer; //offset to teamnumber from Player struct.BLU is 3, RED is 2
	DWORD healthPointer;
	DWORD playerLocationPointer; //offset from Player struct.

	DWORD numberOfPlayersPointer; //SERVER.DLL. find out how many players in-game.

												   //is multi-level pointer: the real pointer is at *( *(client.dll+[0]) + [1]) + [2]
												   //if these change, then there are other options you can try as well in the guide.
	//const DWORD crosshairIDPointerOffsets[3] = { 0x00C8CCC4,0x50,0x1CC };


	//list of Players. ourPlayer is list[0], list[1] is offset from list[0] by 0x10.
	DWORD playerListPointer;
	DWORD playerListLoopDistance; //list[1] is list[0] + ....
	DWORD ourPlayerPointer;//ourPlayer is playerList[0].

	DWORD angleRotationsPointer; //ENGINE.DLL. 2 floats. 1 vertical 1 horizontal

	DWORD fieldOfVisionPointer;
};

