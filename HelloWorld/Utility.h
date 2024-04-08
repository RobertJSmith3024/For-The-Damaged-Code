#pragma once

enum GameObjectType 
{
	type_player,
	type_enemy0,
	type_enemy1,
	type_enemy2,
	type_junk,
	type_laser,
	type_enemyLaser
};

class Utility 
{
public:
	Utility();
	void CurrentTime(float elapsedTime);
	float GetTime();
	void ResetTime();
	float GetTimeOnce(float waitTime);
	void destroy();
	int scaleRate(float scaleRate, int scaleMax);
	void resetScale();

private:
	float Time = 0;
	bool waitTimeTriggered = false;
	int DISPLAY_WIDTH = 1024;
	int DISPLAY_HEIGHT = 1024;
	int DISPLAY_SCALE = 1;
	int Scale = 0;
};

class SpawnSeed : public Utility
{
public:
	int getEnemy0();
	int getEnemy1();
	int getEnemy2();
	int getEnemy1Laser();
	int getItem();

private:
	int enemy0 = 40;
	int enemy1 = 120;
	int enemy2 = 240;
	int enemy1Laser = 150;
	int item = 20;
};

class PlayerProperties : public Utility
{
public:
	int getPlayerProjVelocity();
private:
	int playerProjVelocity = 15;
};

class EnemyProperties : public Utility
{
public:
	int getEnemy1ProjVelocity();
	float getEnemy2Angle1();
	float getEnemy2Angle2();

private:
	int enemy1ProjVelocity = 10;
	// Angles need to be negative
	float enemy2Angle1 = -0.45f;
	float enemy2Angle2 = -0.55f;
};

