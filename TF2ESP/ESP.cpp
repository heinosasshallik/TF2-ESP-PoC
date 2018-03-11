#include "ESP.h"
#include <iostream>


ESP::ESP()
{
}


ESP::~ESP()
{
}

// simple 3d distance calculation with Pythagorean theorem

float ESP::calculate3dDistance(float* src, float* dst) {
	//d = sqrt(dx_squared + dy_squared + dz_squared)

	float delta[3] = { (src[0] - dst[0]), (src[1] - dst[1]), (src[2] - dst[2]) };
	//untested
	return sqrt(pow(delta[0], 2) + pow(delta[1], 2) + pow(delta[2], 2));
}

//Calculate what our angleRotations should be to aim at the enemy.
//world to screen function.
//Returns vertical and horizontal angles
std::vector<float> ESP::calcAngle(float* src, float* dst)
{

	std::vector<float> angles;
	//1)vectors from one coordinate to the other x1=3 x2=1  x1-x2 = 2. You have to move by 2 on the x axis to get to your destination.
	//double delta[3] = { (src[0] - dst[0]), (src[1] - dst[1]), (src[2] - dst[2]) };
	double delta[3] = { (dst[0] - src[0]), (dst[1] - src[1]), (dst[2] - src[2]) };

	//2)sqrt(v1^2 + v2^2). Distance from you to the enemy on 2D horizontal plane.
	double hypothenuse = sqrt(delta[0] * delta[0] + delta[1] * delta[1]); 
																		  
	angles.push_back((float)(atanf(delta[2] / hypothenuse) * 57.295779513082f)); //that constant changes radians to degrees. It's 180/pi.
																		   
	angles.push_back((float)(atanf(delta[1] / delta[0]) * 57.295779513082f));
	
	angles.push_back(0.0f);
	//this is here because arc functions don't give answers in the [0,360) range.
	if (delta[0] <= 0.0)
	{
		if (delta[1] <= 0.0) {
			angles[1] -= 180.0f;
		}
		else {
			angles[1] += 180.0f;
		}
		
	}

	return angles;
}

std::vector<float> ESP::calculateAngleDifferences(std::vector<float> enemyAimAngles, float* ourAngleRotations) {
	std::vector<float> angleDifferences;
	angleDifferences.push_back(99999999999999999.9);
	angleDifferences.push_back(99999999999999999.9);

	//convert the horizontal angles from the old angles system to the new one. Makes it easier to work with.
	//original: 0, -90, -180(and 180), 90, 0
	//new: 0, 90, 180, 270, 360(and 0)
	float enemyModifiedAimAngles[2];
	if (enemyAimAngles[1] < 0) {
		enemyModifiedAimAngles[1] = -enemyAimAngles[1];
		enemyModifiedAimAngles[0] = enemyAimAngles[0];
	}
	else {
		enemyModifiedAimAngles[1] = 360 - enemyAimAngles[1];
		enemyModifiedAimAngles[0] = enemyAimAngles[0];
	}
	float ourModifiedAngleRotations[2];
	if (ourAngleRotations[1] < 0) {
		ourModifiedAngleRotations[1] = -ourAngleRotations[1];
		ourModifiedAngleRotations[0] = ourAngleRotations[0];
	}
	else {
		ourModifiedAngleRotations[1] = 360 - ourAngleRotations[1];
		ourModifiedAngleRotations[0] = ourAngleRotations[0];
	}
	angleDifferences[0] = enemyModifiedAimAngles[0] - ourModifiedAngleRotations[0];
	angleDifferences[1] = enemyModifiedAimAngles[1] - ourModifiedAngleRotations[1];

	return angleDifferences;
}

bool ESP::withinClipSpace(std::vector<float> angleDifferences) {
	if (angleDifferences[0] >= -1 && angleDifferences[0] <= 1) {
		if (angleDifferences[1] >= -1 && angleDifferences[1] <= 1) {
			return true;
		}
	}
	return false;
}

/*
Screen position calculation.

This is done by getting the direction we're aiming at, 
calculating the direction we should be aiming at to aim at the enemy
subtracting them
and using the known field of view to find out where they are on screen.

Returns a float. Visible objects are between [-1,1]
*/
std::vector<float> ESP::calculateScreenPositions(Player* enemy, Player* ourPlayer) {
	std::vector<float> screenPositions;
	//Reinitializing because it gets fucked up somewhere and I cant find it by searching, i'm sorry,
	ourPlayer->fieldOfVision[0] = 33.3;
	ourPlayer->fieldOfVision[1] = 54.0;

	

	enemy->aimAngles = calcAngle(ourPlayer->location, enemy->location);

	std::vector<float> angleDifferences = calculateAngleDifferences(enemy->aimAngles, ourPlayer->angleRotations);
	//angleDifferences[0] = enemy->aimAngles[0] - ourPlayer->angleRotations[0];
	//angleDifferences[1] = ourPlayer->angleRotations[1] - enemy->aimAngles[1]; // order is inverted so that right is positive and left is negative.
	screenPositions.push_back(angleDifferences[0] / ourPlayer->fieldOfVision[0]); 
	screenPositions.push_back(angleDifferences[1] / ourPlayer->fieldOfVision[1]);
	return screenPositions;
}

std::vector<RenderingInputData> ESP::calculateRenderingData(std::vector<Player*> players) {
	std::vector<RenderingInputData> renderingInputData;
	for (unsigned int i = 0; i < players.size(); i++) {
		//Do not render our teammates.
		if (players[i]->teamNum != players[0]->teamNum) {
			//Do not render dead players. 1HP == dead.
			if (players[i]->health > 1) {
				//untested
				RenderingInputData tempRenderingData;
				tempRenderingData.playerIndex = i;
				tempRenderingData.teamNum = players[i]->teamNum;

				
				tempRenderingData.screenPositions = calculateScreenPositions(players[i], players[0]);
				if (!withinClipSpace(tempRenderingData.screenPositions)) {
					continue;
				}
				tempRenderingData.distance = calculate3dDistance(players[0]->location, players[i]->location);


				renderingInputData.push_back(tempRenderingData);
			}
		}
	}
	
	return renderingInputData;
}
