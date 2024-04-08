#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Utility.h"
#include "Play.h"

Utility::Utility()
{
}

void Utility::ResetTime()
{
	Time = 0;
}

void Utility::CurrentTime(float elapsedTime)
{
	Time = Time + elapsedTime;
	Play::DrawFontText("64px", ("TIME:" + std::to_string(Time)).c_str(), { DISPLAY_WIDTH - 100, DISPLAY_HEIGHT - 100 }, Play::CENTRE);
}

float Utility::GetTime()
{
	return Time;
}


float Utility::GetTimeOnce(float waitTime)
{
	if (waitTimeTriggered = false)
	{
		waitTime = Time + waitTime;
		return waitTime;
		waitTimeTriggered = true;
	}
}

void Utility::destroy()
{
	std::vector <int> junk = Play::CollectGameObjectIDsByType(type_junk);
	for (int i : junk)
	{
		Play::DestroyGameObject(i);
	}
}

int Utility::scaleRate(float scaleRate, int scaleMax)
{
	if (Scale < scaleMax)
	{
		Scale =+ scaleRate * Time;
	}
	if (Scale > scaleMax)
	{
		Scale = scaleMax;
	}
	return Scale;
}

void Utility::resetScale()
{
	Scale = 0;
}

int SpawnSeed::getEnemy0()
{
	return enemy0;
}

int SpawnSeed::getEnemy1()
{
	return enemy1;
}

int SpawnSeed::getEnemy2()
{
	return enemy2;
}

int SpawnSeed::getEnemy1Laser()
{
	return enemy1Laser;
}

int SpawnSeed::getItem()
{
	return item;
}

int PlayerProperties::getPlayerProjVelocity()
{
	return playerProjVelocity;
}

int EnemyProperties::getEnemy1ProjVelocity()
{
	return enemy1ProjVelocity;
}

float EnemyProperties::getEnemy2Angle1()
{
	return enemy2Angle1;
}

float EnemyProperties::getEnemy2Angle2()
{
	return enemy2Angle2;
}
