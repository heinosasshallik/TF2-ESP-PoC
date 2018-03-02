#pragma once

#include <vector>

struct RenderingInputData {
	std::vector<float> screenPositions; //vertical, horizontal
	float distance;
	int teamNum;
	int playerIndex; //index of player in players vector
};