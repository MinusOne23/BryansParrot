#include "pch.h"
#include "CppUnitTest.h"
#include "..\BryansParrot\Game.cpp"
#include "..\BryansParrot\Player.cpp"
#include "..\BryansParrot\Character.cpp"
#include "..\BryansParrot\Door.cpp"
#include "..\BryansParrot\Enemy.cpp"
#include "..\BryansParrot\Health.cpp"
#include "..\BryansParrot\Inventory.cpp"
#include "..\BryansParrot\Key.cpp"
#include "..\BryansParrot\Main.cpp"
#include "..\BryansParrot\Potion.cpp"
#include "..\BryansParrot\Room.cpp"
#include "..\BryansParrot\Utils.cpp"
#include "..\BryansParrot\Weapon.cpp"
#include "..\BryansParrot\Interaction.cpp"
#include "..\BryansParrot\EnemyEncounter.cpp"



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

			Weapon trollFists(TROLL_WEAPON, {5, 10}, 0.1f, {10, 20});
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

 
			Weapon enemyWeapon(ENEMY_NAME, { 5, 10 }, 0.1f, { 10, 20 });
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
