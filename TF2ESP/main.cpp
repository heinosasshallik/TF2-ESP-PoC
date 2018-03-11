

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
