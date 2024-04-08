#pragma once
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "Enemy.h"
#include "utility.h"
Enemy::Enemy()
{
}

void Enemy::EnemyLaserUpdate()
{
	std::vector <int> enemylaser = Play::CollectGameObjectIDsByType(type_enemyLaser);
	for (int i : enemylaser)
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

void Enemy::SetSprite(int object_id, const char* spriteName)
{
	GameObject& object = Play::GetGameObject(object_id);
	Play::SetSprite(object, spriteName, 0.25f);
	Play::UpdateGameObject(object);
	Play::DrawObjectRotated(object);
}

Enemy0::Enemy0()
{
}

__declspec(selectany) SpawnSeed spawnSeed;
__declspec(selectany) PlayerProperties playerProperties;
__declspec(selectany) EnemyProperties enemyProperties;

void Enemy0::SpawnEnemy()
{
	int randX = Play::RandomRollRange(800, 1000);
	int randY = Play::RandomRollRange(50, 950);
	int id = Play::CreateGameObject(type_enemy0, { randX,randY }, collisionRad, "rsz_gabby_enemy1", hP);
	GameObject& enemy_id = Play::GetGameObject(id);
	Play::DrawObjectRotated(enemy_id);
	Play::UpdateGameObject(enemy_id);
}

int Enemy0::EnemyMovement(GameObject& player, GameObject& enemyObject)
{
	// Could add thruster animations here depending on Y velocity
	int deltaY = player.pos.y - enemyObject.pos.y;
	int velocityY;
	if (deltaY > 0)
	{
		velocityY = 2;
	}
	else if (deltaY < 0)
	{
		velocityY = -2;
	}
	else
	{
		velocityY = 0;
	}
	return velocityY;
}

void Enemy0::UpdateEnemy(GameObject& player)
{
	std::vector <int> enemy = Play::CollectGameObjectIDsByType(type_enemy0);
	for (int i : enemy)
	{
		GameObject& enemyObject = Play::GetGameObject(i);
		//	Enemy Y velocity is calculated by working out difference between player and enemy on Y axis to adjust Y velocity	
		enemyObject.velocity = { -3, EnemyMovement(player, enemyObject) };
		Play::UpdateGameObject(enemyObject);
		Play::DrawObjectRotated(enemyObject);

		if (!Play::IsVisible(enemyObject))
		{
			enemyObject.type = type_junk;
		}
	}
}

Enemy1::Enemy1()
{
}

void Enemy1::SpawnEnemy()
{
	int randX = Play::RandomRollRange(800, 1000);
	int randY = Play::RandomRollRange(50, 950);
	int id = Play::CreateGameObject(type_enemy1, { randX,randY }, collisionRad, "shark_laser", hP);
	GameObject& enemy_id = Play::GetGameObject(id);
	enemy_id.velocity.y = 2;
	enemy_id.velocity.x = -2;
	Play::DrawObjectRotated(enemy_id);
	Play::UpdateGameObject(enemy_id);
}

void Enemy1::EnemyMovement(GameObject& enemyObject)
{
	if (enemyObject.pos.y >= 950)
	{
		enemyObject.velocity.y = -enemyObject.velocity.y;
	}
	else if (enemyObject.pos.y <= 50)
	{
		enemyObject.velocity.y = -enemyObject.velocity.y;
	}

	if (enemyObject.pos.x <= 550)
	{
		enemyObject.velocity.x = -enemyObject.velocity.x;
	}
	else if (enemyObject.pos.x >= 1000)
	{
		enemyObject.velocity.x = -enemyObject.velocity.x;
	}
}

void Enemy1::UpdateEnemy()
{
	std::vector <int> enemy1 = Play::CollectGameObjectIDsByType(type_enemy1);
	for (int i : enemy1)
	{
		GameObject& enemyObject = Play::GetGameObject(i);
		EnemyMovement(enemyObject);
		Play::UpdateGameObject(enemyObject);
		Play::DrawObjectRotated(enemyObject);

		if (!Play::IsVisible(enemyObject))
		{
			enemyObject.type = type_junk;
		}

		if (Play::RandomRoll(spawnSeed.getEnemy1Laser()) == spawnSeed.getEnemy1Laser())
		{
			Vector2D firePos = enemyObject.pos + Vector2D{ 0, 0 };
			int laser_id = Play::CreateGameObject(type_enemyLaser, firePos, 30, "rszsharklaser", damage);
			
			SetSprite(laser_id, "rszsharklaser");

			Play::GetGameObject(laser_id).velocity = { -enemyProperties.getEnemy1ProjVelocity(), 0};
		}
	}
}

Enemy2::Enemy2()
{
}

void Enemy2::SpawnEnemy()
{
	int randX = Play::RandomRollRange(800, 1000);
	int randY = Play::RandomRollRange(50, 950);
	int id = Play::CreateGameObject(type_enemy2, { randX,randY }, collisionRad, "Enemytwo", hP);
	GameObject& enemy_id = Play::GetGameObject(id);
	enemy_id.animSpeed = 0.05;
	enemy_id.velocity.y = 1;
	enemy_id.velocity.x = -1;
	Play::DrawObjectRotated(enemy_id);
	Play::UpdateGameObject(enemy_id);
}

void Enemy2::EnemyMovement(GameObject& enemyObject)
{
	if (enemyObject.pos.y >= 950)
	{
		enemyObject.velocity.y = -enemyObject.velocity.y;
	}
	else if (enemyObject.pos.y <= 50)
	{
		enemyObject.velocity.y = -enemyObject.velocity.y;
	}

	if (enemyObject.pos.x <= 550)
	{
		enemyObject.velocity.x = -enemyObject.velocity.x;
	}
	else if (enemyObject.pos.x >= 1000)
	{
		enemyObject.velocity.x = -enemyObject.velocity.x;
	}
}

void Enemy2::UpdateEnemy()
{
	std::vector <int> enemy2 = Play::CollectGameObjectIDsByType(type_enemy2);
	for (int b : enemy2)
	{
		GameObject& enemyObject = Play::GetGameObject(b);
		EnemyMovement(enemyObject);
		Play::UpdateGameObject(enemyObject);
		Play::DrawObjectRotated(enemyObject);

		if (!Play::IsVisible(enemyObject))
		{
			enemyObject.type = type_junk;
		}

		if (Play::RandomRoll(spawnSeed.getEnemy1Laser()) == spawnSeed.getEnemy1Laser())
		{
			Vector2D firePos = enemyObject.pos + Vector2D{ 0, 0 };

			int laser_id = Play::CreateGameObject(type_enemyLaser, firePos, 30, "purplelaser", damage);
			Play::GetGameObject(laser_id).velocity = { -enemyProperties.getEnemy1ProjVelocity(), 0 };

			int laser_id2 = Play::CreateGameObject(type_enemyLaser, firePos, 30, "purplelaser", damage);
			GameObject& laser2 = Play::GetGameObject(laser_id2);
			Play::SetGameObjectDirection(laser2, enemyProperties.getEnemy1ProjVelocity(), enemyProperties.getEnemy2Angle1() * PLAY_PI);

			int laser_id3 = Play::CreateGameObject(type_enemyLaser, firePos, 30, "purplelaser", damage);;
			GameObject& laser3 = Play::GetGameObject(laser_id3);
			Play::SetGameObjectDirection(laser3, enemyProperties.getEnemy1ProjVelocity(), enemyProperties.getEnemy2Angle2() * PLAY_PI);
			
			SetSprite(laser_id, "purplelaser");
			SetSprite(laser_id2, "purplelaser");
			SetSprite(laser_id3, "purplelaser");
		
		}
	}
}
