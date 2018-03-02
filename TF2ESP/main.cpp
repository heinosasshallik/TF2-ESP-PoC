/*

PROBLEMS:
1) for some reason the esp always spawns to the right of the medic, even though the aimangle and screen position calculations are correct.
It also goes out of frame before the medic if you rotate the screen so that the medic moves to the left.
I checked with a pen and paper - the medic really is at the very centre of the screen. So what is going wrong?


TO DO:
*) fix calculation bugs
*) test memory leaks

PROBLEMS:

SOLVED PROBLEMS:
1) shared_ptr deletes the pointer if the code goes out of scope. Switch to a normal pointer and manage the memory yourself.
2) cant convert from shared_ptr<player> to shared_ptr<ourplayer>. This is fixed by implementing all the functions and variables that are needed in Player and overloading them in subclasses.
3) fix memory leak. -- fixed by deallocating and deleting the vector's elements on each new pass of the loop.
4) Successfully implement a vector of polymorphic objects -- make a  vector of pointers to the base class and put the subclass into that vector as a pointer to base class. Make sure to define all the variables and functions the subclass needs in baseclass. Make sure to make the functions virtual, so they can be overwritten, and make sure to provide an implementation of all the virtual functions in the base class as well (including the destructor)
*/

#include <iostream>
#include <vector>
#include <memory>
#include "OurPlayer.h"
#include "ESP.h"
#include "Rendering.h"
#include "RenderingInputData.h"
#include "ServerData.h"
#include <tchar.h>

#define F6_KEY 0x75

CHackProcess fProcess;
std::vector<Player*> players;

//0 - low. 1 - normal
void setProcessPriority(int priority) {
	DWORD dwError, dwPriClass;

	if (priority == 0) {
		if (!SetPriorityClass(GetCurrentProcess(), PROCESS_MODE_BACKGROUND_BEGIN))
		{
			dwError = GetLastError();
			if (ERROR_PROCESS_MODE_ALREADY_BACKGROUND == dwError)
				_tprintf(TEXT("Already in background mode\n"));
			else _tprintf(TEXT("Failed to enter background mode (%d)\n"), dwError);
		}
		else std::cout << "Running process in background mode";
	}
	return;
	
}

//0 - low. 1 - normal
int processPriority = 0;

void main() {
	//finds the game's dll modules and makes them easily accessible to us via fprocess.
	fProcess.RunProcess();

	std::cout << "Game found, running." << std::endl;

	setProcessPriority(0);
	

	ESP esp;
	Rendering rendering;
	ServerData serverData;
	while (!GetAsyncKeyState(F6_KEY)) {
		players = serverData.readPlayerData(); // server.readnumofplayers not working. Retest this
		//Calculates the data needed for rendering
		std::vector<RenderingInputData> renderingInputData = esp.calculateRenderingData(players); //returns screen positions and depth
		
		rendering.render(renderingInputData);
	}
}