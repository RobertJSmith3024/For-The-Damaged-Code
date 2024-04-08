#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "Utility.h"
#include "Enemy.h"
#include "Player.h"
#include "Item.h"
#include<windows.h>

//Global Variables
int DISPLAY_WIDTH = 1024;
int DISPLAY_HEIGHT = 1024;
int DISPLAY_SCALE = 1;
int playerScore;
bool dead = false;
bool start = true;

//Create classes to be used by functions
__declspec(selectany) SpawnSeed spawnSeed;
__declspec(selectany) PlayerProperties playerProperties;
__declspec(selectany) EnemyProperties enemyProperties;
Enemy enemyClass;
Enemy0 enemy0Class;
Enemy1 enemy1Class;
Enemy2 enemy2Class;
PlayerClass playerClass;
Utility utility;

//Display Text at start of game
void StartText()
{
	if (utility.GetTime() < 5)
	{
		Play::DrawFontText("64px", "Press 'NUMPAD 1' to change music OR", { DISPLAY_WIDTH / 2 , DISPLAY_HEIGHT - 950 }, Play::CENTRE);
		Play::DrawFontText("64px", "Press 'NUMPAD 2' to stop music.", { DISPLAY_WIDTH / 2 , DISPLAY_HEIGHT - 900 }, Play::CENTRE);
	}
}

//Prepare DeathScreen for RestartGame function
void RestartGame(GameObject& player);
//Display Text at start of game
void StartScreen(GameObject& player)
{
	do
	{
		Play::DrawFontText("64px", "Welcome. To start the game press 'space'", { DISPLAY_WIDTH / 2 , DISPLAY_HEIGHT / 2 }, Play::CENTRE);
		//Play::DrawDebugText({ DISPLAY_WIDTH / 2, DISPLAY_HEIGHT - 30 }, "You Have Died!! Press NUMPAD 9 to Carry on or ESCAPE to take a trip down wash out lane.", Play::cWhite);
		Play::PresentDrawingBuffer();
		if (Play::KeyDown(VK_SPACE)) { RestartGame(player); start = false; }
		//Escape also activates the EXIT function (last line) in main game update 
		if (Play::KeyDown(VK_ESCAPE)) { start = false; };
	} while (start == true);
}
//Prints out text on player death + reset game state by setting death boolean to false
void DeathScreen(GameObject& player)
{
	do
	{
		Play::DrawFontText("64px", "You Have Died! Press 'NUMPAD 9' to Carry on or 'ESC' to exit.", { DISPLAY_WIDTH / 2 , DISPLAY_HEIGHT - 980 }, Play::CENTRE);
		//Play::DrawDebugText({ DISPLAY_WIDTH / 2, DISPLAY_HEIGHT - 30 }, "You Have Died!! Press NUMPAD 9 to Carry on or ESCAPE to take a trip down wash out lane.", Play::cWhite);
		Play::PresentDrawingBuffer();
		if (Play::KeyDown(VK_NUMPAD9)){RestartGame(player);}
		//Escape also activates the EXIT function (last line) in main game update 
		if (Play::KeyDown(VK_ESCAPE)){ dead = false; };
	}	while (dead == true);
}
//Restarts game by deleting all enemy objects and resetting score
void RestartGame(GameObject& player)
{
	for (int i = 1; i <= 6; i++)
	{
		std::vector <int> endGameClear = Play::CollectGameObjectIDsByType(i);
		for (int s : endGameClear) { Play::GetGameObject(s).type = type_junk; }
	}
	dead = false;
	playerScore = 0;
	player.hP = playerClass.ReturnMaxHP();
	utility.ResetTime();
	utility.resetScale();
}
//Gives player score for each enemy killed
void ScoreUpdate(GameObject& destroyedEnemy)
{
	int addScore = 0;
 
	switch (destroyedEnemy.type)
	{
	case type_enemy0:
		addScore = 10;
		break;

	case type_enemy1:
		addScore = 20;
		break;

	case type_enemy2:
		addScore = 30;
		break;
	}
	playerScore = playerScore + addScore;
}
//Checks for collisions (player with enemy laser, enemy with player etc.) sets objects to junk(delete) if hp < 0
void Collision(GameObject& Player)
{
	std::vector <int> collidePlaser = Play::CollectGameObjectIDsByType(type_laser);
	std::vector <int> collideEnemy0 = Play::CollectGameObjectIDsByType(type_enemy0);
	std::vector <int> collideEnemy1 = Play::CollectGameObjectIDsByType(type_enemy1);
	std::vector <int> collideEnemy2 = Play::CollectGameObjectIDsByType(type_enemy2);
	std::vector <int> collideEnemyLaser = Play::CollectGameObjectIDsByType(type_enemyLaser);

	for (int PLaser : collidePlaser) 
	{
		GameObject& Playerlaser = Play::GetGameObject(PLaser);
		//Check through Enemy0. If collide with laser. Destroy laser and enemy0
		for (int Enemy0 : collideEnemy0)
		{
			GameObject& enemy0 = Play::GetGameObject(Enemy0);
			if (Play::IsColliding(Playerlaser,enemy0))
			{
				Playerlaser.type = type_junk;
				enemy0.hP = enemy0.hP - Playerlaser.hP;
				if (enemy0.hP <= 0) {ScoreUpdate(enemy0); enemy0.type = type_junk;}
				else {}
			}
		}
		//Check through Enemy1. If collide with laser. Destroy laser and enemy1
		for (int Enemy1 : collideEnemy1) 
		{
			GameObject& enemy1 = Play::GetGameObject(Enemy1);
			if (Play::IsColliding(Playerlaser, enemy1))
			{
				Playerlaser.type = type_junk;
				enemy1.hP = enemy1.hP - Playerlaser.hP;
				if (enemy1.hP <= 0) {ScoreUpdate(enemy1); enemy1.type = type_junk;}
				else {}
			}
		}
		//Check through Enemy2. If collide with laser. Destroy laser and enemy2
		for (int Enemy2 : collideEnemy2)
		{
			GameObject& enemy2 = Play::GetGameObject(Enemy2);
			if (Play::IsColliding(Playerlaser, enemy2))
			{
				Playerlaser.type = type_junk;
				enemy2.hP = enemy2.hP - Playerlaser.hP;
				if (enemy2.hP <= 0) {ScoreUpdate(enemy2); enemy2.type = type_junk;}
				else {}
			}
		}
	}
	//Check if Enemy laser collides with player - if yes print text/damage player
	for (int ELaser : collideEnemyLaser)
	{
		GameObject& EnemyLaser = Play::GetGameObject(ELaser);
		if (Play::IsColliding(EnemyLaser,Player))
		{
			EnemyLaser.type = type_junk;

			Player.hP = Player.hP - EnemyLaser.hP;

			// Is below line neccessary?
			//else{ Play::DrawDebugText({ DISPLAY_WIDTH / 2,DISPLAY_HEIGHT - 30 }, std::to_string(Player.hP).c_str(), Play::cWhite);}
		}
	}

	for (int Enemy0 : collideEnemy0)
	{
		GameObject& enemy0 = Play::GetGameObject(Enemy0);
		//If Enemy0 collides with player, destroy enemy0 and deal damage to player (currently no damage just death)
		if (Play::IsColliding(enemy0,Player))
		{
			enemy0.type = type_junk;
			Player.hP = Player.hP - enemy0.hP;
		}
	}
	//Moved IF statement outside of for loop of Elaser:collideEnemyLaser as was not setting player dead if they died to enemy0
	if (Player.hP <= 0)
	{
		//Play::SetSprite(Player, "Explosion", 0.25f);
		//if (utility.GetTimeOnce(2) < utility.GetTime())
		//{
			dead = true;
		//}
	}
}
//Draw HP and score to screen
void UIElements(GameObject& player)
{
	Play::DrawFontText("64px", ("HP:" + std::to_string(player.hP)).c_str(), {DISPLAY_WIDTH - 980, DISPLAY_HEIGHT - 30}, Play::CENTRE);
	Play::DrawFontText("64px", ("Score:" + std::to_string(playerScore)).c_str(), { DISPLAY_WIDTH - 850, DISPLAY_HEIGHT - 30 }, Play::CENTRE);
}

void MainGameEntry( PLAY_IGNORE_COMMAND_LINE )
{
	Play::CreateManager(DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE);
	playerClass.CreatePlayer();
	Play::LoadBackground("Data\\Backgrounds\\Space16.png");
	Play::CentreAllSpriteOrigins();
	Play::PlayAudio("cowboy_classic");
}

bool MainGameUpdate(float elapsedTime)
{
	//Draw background
	Play::ClearDrawingBuffer(Play::cOrange);
	Play::DrawBackground();
	//Draw player sprite
	GameObject& player = Play::GetGameObjectByType(type_player);
	//Start Screen
	if (start == true) { StartScreen(player); }
	//Store Time
	StartText();

	//Player Controls
	playerClass.PlayerControls();
	playerClass.PlayerWeaponUpdate();
	if (Play::RandomRoll(spawnSeed.getEnemy0() - utility.scaleRate(0.85,30)) == spawnSeed.getEnemy0() - utility.scaleRate(0.85,30)) { enemy0Class.SpawnEnemy(); }
	if (Play::RandomRoll(spawnSeed.getEnemy1() - utility.scaleRate(0.85,90)) == spawnSeed.getEnemy1() - utility.scaleRate(0.85,90)) { enemy1Class.SpawnEnemy(); }
	if (Play::RandomRoll(spawnSeed.getEnemy2() - utility.scaleRate(0.85,180)) == spawnSeed.getEnemy2() - utility.scaleRate(0.85,180)) { enemy2Class.SpawnEnemy(); }
	//if (Play::RandomRoll(spawnSeed.getItem()) == spawnSeed.getItem())
	//{
	//	item.spawn();
	//}
	enemy0Class.UpdateEnemy(player);
	enemy1Class.UpdateEnemy();
	enemy2Class.UpdateEnemy();
	enemyClass.EnemyLaserUpdate();
	Collision(player);
	UIElements(player);
	utility.destroy();
	if (dead == true) { DeathScreen(player); }

	utility.CurrentTime(elapsedTime);
	
	Play::PresentDrawingBuffer();
	return Play::KeyDown(VK_ESCAPE);

}

int MainGameExit( void )
{
	Play::DestroyManager();
	return PLAY_OK;
}
