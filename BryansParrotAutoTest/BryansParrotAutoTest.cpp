#include "pch.h"
#include "CppUnitTest.h"
#include "Game.cpp"
#include "Player.cpp"
#include "Character.cpp"
#include "Door.cpp"
#include "Enemy.cpp"
#include "Health.cpp"
#include "Inventory.cpp"
#include "Key.cpp"
#include "Main.cpp"
#include "Potion.cpp"
#include "Room.cpp"
#include "Utils.cpp"
#include "Weapon.cpp"
#include "Interaction.cpp"
#include "EnemyEncounter.cpp"
#include "DungeonBuilder.cpp"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BryansParrotAutoTest
{
	TEST_CLASS(BryansParrotAutoTest)
	{
	public:
		
		TEST_METHOD (VerifyCanCreateOneEnemy)
		{
			Game game;
			game.initializeGameTest();

			const std::string TROLL_NAME = "Troll";
			const std::string TROLL_WEAPON = "Troll Fists";
			const int TROLL_HEALTH = 100;

			Weapon trollFists(TROLL_WEAPON, {5, 10}, {10, 20}, 0.1f, 1.5f);
			Enemy troll(TROLL_NAME, TROLL_HEALTH, trollFists);

			// Verify can retrieve stored character name
			Assert::AreEqual(TROLL_NAME, troll.getName());
			// Now verify health
			Assert::AreEqual(TROLL_HEALTH, troll.getCurrentHealth());
		}

		TEST_METHOD(VerifyHealthManagement) {
			Game game;
			game.initializeGameTest();
			std::string str;
			const char* logMsg;

			const std::string ENEMY_NAME = "Troll";
			const std::string ENEMY_WEAPON = "Troll Fists";
			const int ENEMY_HEALTH = -1;
			const int DAMAGE1 = -50;
			const int HEALTH1 = -50;

 
			Weapon enemyWeapon(ENEMY_NAME, { 5, 10 }, { 10, 20 }, 0.1f, 1.5f);
			Enemy enemy(ENEMY_NAME, ENEMY_HEALTH, enemyWeapon);

			// Now verify health
			str = "*Starting Health: " + to_string(enemy.getCurrentHealth()) + "\n";
			logMsg = str.c_str();
			Logger::WriteMessage(logMsg);
			Assert::AreEqual(ENEMY_HEALTH, enemy.getCurrentHealth());

			// do some damage
			enemy.damage(DAMAGE1);
			str = "*After some damage: " + to_string(enemy.getCurrentHealth()) + "\n";
			logMsg = str.c_str();
			Logger::WriteMessage(logMsg);
			Assert::AreEqual(ENEMY_HEALTH - DAMAGE1, enemy.getCurrentHealth());

			// add some health
			enemy.heal(HEALTH1);
			str = "*After some healing: " + to_string(enemy.getCurrentHealth()) + "\n";
			logMsg = str.c_str();
			Logger::WriteMessage(logMsg);
			Assert::AreEqual(ENEMY_HEALTH - DAMAGE1 + HEALTH1, enemy.getCurrentHealth());

			// Net using -1 starting, -50 damage, -50 healing
			// Can end up with negative health - healing only checks if > max health - initial health setting not bounds checked
		}
	};
}
