#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "Item.h"

Item::Item()
{
	Spawn();
}

void Item::Spawn()
{
	int randX = Play::RandomRollRange(800, 1000);
	int randY = Play::RandomRollRange(50, 950);
	int id = Play::CreateGameObject(999, { randX,randY }, 20, "melon", 200);
	GameObject& gameObject = Play::GetGameObject(id);
	Play::DrawObjectRotated(gameObject);
	Play::UpdateGameObject(gameObject);
}

