#pragma once
class Enemy
{
public:
	Enemy();
	void EnemyLaserUpdate();
	void SetSprite(int laser_id, const char* spriteName);
private:
};

class Enemy0 : public Enemy
{
public:
	Enemy0();
	void SpawnEnemy();
	int EnemyMovement(GameObject& player, GameObject& enemyObject);
	void UpdateEnemy(GameObject& player);

private:
	//hP is damage for enemy0 as they are the object that collides with the player. Can keep this low or high
	int hP = 10;
	int collisionRad = 30;
};

class Enemy1 : public Enemy
{
public:
	Enemy1();
	void SpawnEnemy();
	void EnemyMovement(GameObject& enemyObject);
	void UpdateEnemy();
private:

	int hP = 60;
	int collisionRad = 30;
	int damage = 20;
};

class Enemy2 : public Enemy
{
public:
	Enemy2();
	void SpawnEnemy();
	void EnemyMovement(GameObject& enemyObject);
	void UpdateEnemy();
private:

	int hP = 90;
	int collisionRad = 30;
	int damage = 30;
};