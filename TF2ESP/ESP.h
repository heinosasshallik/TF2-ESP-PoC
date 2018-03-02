#pragma once
#include "RenderingInputData.h"
#include <vector>
#include "OurPlayer.h"

class ESP
{
public:
	ESP();
	~ESP();
	std::vector<RenderingInputData> calculateRenderingData(std::vector<Player*> players);
	std::vector<float> calculateScreenPositions(Player* enemy, Player* ourPlayer);
	std::vector<float> calcAngle(float* src, float* dst);
	float calculate3dDistance(float* src, float* dst);
	std::vector<float> calculateAngleDifferences(std::vector<float> enemyAimAngles, float* ourAngleRotations);
	bool withinClipSpace(std::vector<float> angleDifferences);
};