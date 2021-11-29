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
#include "AttackMove.cpp"
#include "Equippable.cpp"
#include "Equipment.cpp"
#include "Shield.cpp"
#include "Armor.cpp"

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
			const int TROLL_SPEED = 5;
			const int TROLL_STAMINA = 2;

			Weapon trollFists(TROLL_WEAPON, 0.1f, 1.5f);
			trollFists.addAttackMove(AttackMove("Troll Punch", 5, 10, 1, 0.9f));

			Enemy troll(TROLL_NAME, TROLL_HEALTH, TROLL_SPEED, TROLL_STAMINA, TROLL_DODGE, trollFists);

			// Verify can retrieve stored character name
			Assert::AreEqual(TROLL_NAME, troll.getName());
			// Now verify health
			Assert::AreEqual(TROLL_HEALTH, troll.getCurrentHealth());
			// Now verify speed
			Assert::AreEqual(TROLL_SPEED, troll.getSpeed());
			// Now verify stamina
			Assert::AreEqual(TROLL_STAMINA, troll.getMaxStamina());
			// Now verify dodge chance
			Assert::AreEqual(TROLL_DODGE, troll.getDodgeChance());
		}

		TEST_METHOD(VerifyHealthManagement) {
			std::string logMsg;

			const std::string ENEMY_NAME = "Troll";
			const std::string ENEMY_WEAPON = "Troll Fists";
			const int ENEMY_HEALTH = 100;
			const int ENEMY_SPEED = 5;
			const int ENEMY_STAMINA = 2;
			const int ENEMY_DODGE = 0;
			const int DAMAGE1 = 50;
			const int HEALTH1 = 50;
			const int OVERFLOW_HEAL = ENEMY_HEALTH * 2;
 
			Weapon enemyWeapon(ENEMY_NAME, 0.1f, 1.5f);
			enemyWeapon.addAttackMove(AttackMove("Punch", 5, 10, 1, 0.9f));
			Enemy enemy(ENEMY_NAME, ENEMY_HEALTH, ENEMY_SPEED, ENEMY_STAMINA, ENEMY_DODGE, enemyWeapon);

			// Now verify health
			logMsg = "*Starting Health: " + to_string(enemy.getCurrentHealth()) + "\n";
			Logger::WriteMessage(logMsg.c_str());
			Assert::AreEqual(ENEMY_HEALTH, enemy.getCurrentHealth());

			// do some damage
			enemy.damage(DAMAGE1);
			logMsg = "*After some damage: " + to_string(enemy.getCurrentHealth()) + "\n";
			Logger::WriteMessage(logMsg.c_str());
			Assert::AreEqual(ENEMY_HEALTH - DAMAGE1, enemy.getCurrentHealth());

			// add some health
			enemy.heal(HEALTH1);
			logMsg = "*After some healing: " + to_string(enemy.getCurrentHealth()) + "\n";
			Logger::WriteMessage(logMsg.c_str());
			Assert::AreEqual(ENEMY_HEALTH - DAMAGE1 + HEALTH1, enemy.getCurrentHealth());

			enemy.heal(OVERFLOW_HEAL);
			Assert::AreEqual(enemy.getMaxHealth(), enemy.getCurrentHealth());

			// Net using -1 starting, -50 damage, -50 healing
			// Can end up with negative health - healing only checks if > max health - initial health setting not bounds checked
		}
	};
}
