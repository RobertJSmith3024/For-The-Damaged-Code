#pragma once
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "utility.h"



class PlayerClass
{
public:
	PlayerClass();

	void CreatePlayer();
	void PlayerControls();
	void PlayerWeaponUpdate();
	int ReturnMaxHP();
	void PlayAudio();
	
	void setMoveSpeed(float speed);

private:
	int maxHP = 100;
	int hP = 100;
	int damage = 10;
	int radius = 30;
	int song = 0;
	bool dead;
	float fireReady = 0.0f;
	float rateOfFire = 0.16f;

	float moveSpeed = 4;
};

class Cowboy : public PlayerClass
{



};

class Gabby : public PlayerClass
{


};


class Maxwell : public PlayerClass
{


};
