#pragma once
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Player.h"
#include "Play.h"
#include "Utility.h"

__declspec(selectany) SpawnSeed spawnSeed;
__declspec(selectany) PlayerProperties playerProperties;
__declspec(selectany) EnemyProperties enemyProperties;


std::vector <std::string> music =
{
	"cowboy_classic",
	"cowboy_song0",
	"cowboy_song1",
	"cowboy_song2",
};


PlayerClass::PlayerClass()
{
}


//Pass in variables into constructor
void PlayerClass::CreatePlayer()
{
	Play::CreateGameObject(type_player, { 100,200 }, radius, "spacecowboy", hP);
	GameObject& player = Play::GetGameObjectByType(type_player);
	player.animSpeed = 0.05;
}

void PlayerClass::PlayAudio()
{
	Play::StopAudioLoop(music[song].c_str());
	song = song + 1;
	if (song > 3)
	{
		song = 0;
	}
	Play::StartAudioLoop(music[song].c_str());
}

void PlayerClass::setMoveSpeed(float speed)
{
	moveSpeed = speed;
}

//bool PlayerClass::SetDead(bool set)
//{
//	dead = set;
//}

void PlayerClass::PlayerControls()
{
	GameObject& playerCon = Play::GetGameObjectByType(type_player);

	fireReady += rateOfFire;
	if (fireReady > 1 + rateOfFire)
	{
		fireReady -= rateOfFire;
	}

	if (Play::KeyDown(VK_UP))
	{
		playerCon.velocity = { 0,-moveSpeed };
	}
	else if (Play::KeyDown(VK_DOWN))
	{
		playerCon.velocity = { 0,moveSpeed };
	}
	else if (Play::KeyDown(VK_RIGHT))
	{
		playerCon.velocity = { moveSpeed,0 };
	}
	else if (Play::KeyDown(VK_LEFT))
	{
		playerCon.velocity = { -moveSpeed,0 };
	}
	else
	{
		playerCon.velocity = { 0,0 };
	}
	if (Play::KeyDown(VK_SPACE) == true) {
		Vector2D firePos = playerCon.pos + Vector2D{ 40, 5 };
		Vector2D firePos2 = playerCon.pos + Vector2D{ 40, -5 };
		if (fireReady >= 1.0f)
		{
			fireReady -= 1.0f;
			int laser_id = Play::CreateGameObject(type_laser, firePos, 10, "shot4_asset", damage);
			int laser_id2 = Play::CreateGameObject(type_laser, firePos2, 10, "shot4_asset", damage);
			Play::GetGameObject(laser_id).velocity = { playerProperties.getPlayerProjVelocity(), 0 };
			Play::GetGameObject(laser_id2).velocity = { playerProperties.getPlayerProjVelocity(), 0 };
		}
		else {};
		//Play::PlayAudio("shoot");
	}
	//Player is confined to an unknown area.
	if (Play::IsLeavingDisplayArea(playerCon))
	{
		playerCon.pos = playerCon.oldPos;
	}
	Play::UpdateGameObject(playerCon);
	Play::DrawObjectRotated(playerCon);

	if (Play::KeyPressed(VK_NUMPAD1))
	{
		PlayAudio();
	}
	else if (Play::KeyPressed(VK_NUMPAD2))
	{
		Play::StopAudioLoop(music[song].c_str());
	}
}

void PlayerClass::PlayerWeaponUpdate()
{
	std::vector <int> playerlaser = Play::CollectGameObjectIDsByType(type_laser);
	for (int i : playerlaser)
	{
		GameObject& laserObject = Play::GetGameObject(i);
		//	Enemy Y velocity is calculated by working out difference between player and enemy on Y axis to adjust Y velocity	

		Play::UpdateGameObject(laserObject);
		Play::DrawObjectRotated(laserObject);

		if (!Play::IsVisible(laserObject))
		{
			laserObject.type = type_junk;
		}
	}
}

int PlayerClass::ReturnMaxHP()
{
	return maxHP;
}
