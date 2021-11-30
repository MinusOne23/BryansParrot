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
			const float TROLL_DODGE = 0;

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

		TEST_METHOD(VerifyEquipmentManagement)
		{
			const std::string BASE_WEAPON_NAME = "Fists";

			Weapon baseWeapon(BASE_WEAPON_NAME, 0.1f, 1.5f);
			Equipment equipment(baseWeapon);

			// Verify active weapon defaults as base weapon
			Assert::AreEqual(BASE_WEAPON_NAME, equipment.getActiveWeapon().getName());

			shared_ptr<Shield> shield(new Shield("Shield"));
			equipment.equip(shield);

			// Verify can retrieve equipped shield
			Assert::IsTrue(shield == equipment.getShield());

			shared_ptr<Weapon> sword(new Weapon("Sword", 0.2f, 1.75f));
			equipment.equip(sword);

			// Verify can retrieve equipped weapon
			Assert::AreEqual(sword->getName(), equipment.getActiveWeapon().getName());

			equipment.unequip("Sword");
			
			// Verify when weapon is equipped the active weapon is again base weapon
			Assert::AreEqual(BASE_WEAPON_NAME, equipment.getActiveWeapon().getName());

			shared_ptr<Armor> head	(new Armor("Helmet", Armor::ArmorType::HEAD, 1));
			shared_ptr<Armor> chest	(new Armor("Breastplate", Armor::ArmorType::CHEST, 1));
			shared_ptr<Armor> legs	(new Armor("Greaves", Armor::ArmorType::LEGS, 1));
			shared_ptr<Armor> hands	(new Armor("Gauntlets", Armor::ArmorType::HANDS, 1));
			shared_ptr<Armor> feet	(new Armor("Boots", Armor::ArmorType::FEET, 1));

			// Verify all pieces of armor default to nullptr
			Assert::IsTrue(equipment.getArmor(Armor::ArmorType::HEAD) == nullptr, L"Head piece should be null");
			Assert::IsTrue(equipment.getArmor(Armor::ArmorType::CHEST) == nullptr, L"Chest piece should be null");
			Assert::IsTrue(equipment.getArmor(Armor::ArmorType::HANDS) == nullptr, L"Hands piece should be null");
			Assert::IsTrue(equipment.getArmor(Armor::ArmorType::LEGS) == nullptr, L"Legs piece should be null");
			Assert::IsTrue(equipment.getArmor(Armor::ArmorType::FEET) == nullptr, L"Feet piece should be null");

			equipment.equip(head);
			equipment.equip(chest);
			equipment.equip(hands);
			equipment.equip(legs);
			equipment.equip(feet);

			// Verify can retrieve all pieces of equipped armor
			Assert::IsTrue(head == equipment.getArmor(Armor::ArmorType::HEAD), L"Head piece is incorrect");
			Assert::IsTrue(chest == equipment.getArmor(Armor::ArmorType::CHEST), L"Chest piece is incorrect");
			Assert::IsTrue(hands == equipment.getArmor(Armor::ArmorType::HANDS), L"Hands piece is incorrect");
			Assert::IsTrue(legs == equipment.getArmor(Armor::ArmorType::LEGS), L"Legs piece is incorrect");
			Assert::IsTrue(feet == equipment.getArmor(Armor::ArmorType::FEET), L"Feet piece is incorrect");

			Logger::WriteMessage(equipment.display("").c_str());
		}

		TEST_METHOD(VerifyInventoryManagement)
		{
			Inventory inventory;

			Key key;

			shared_ptr<Key> item1 = make_shared<Key>(key);
			shared_ptr<Key> item2 = make_shared<Key>(key);
			shared_ptr<Key> item3 = make_shared<Key>(key);

			// Verify inventory defaults to empty
			Assert::AreEqual(0, inventory.numItems());

			inventory.addItem(item1);
			inventory.addItem(item2);
			inventory.addItem(item3);

			// Verify inventory has correct count
			Assert::AreEqual(3, inventory.numItems());

			// Verify first item is correct
			Assert::IsTrue(item1 == inventory[0], L"First item is not correct");

			inventory.remove(0);

			// Verify correct removal by index
			Assert::AreEqual(2, inventory.numItems());
			Assert::IsTrue(item2 == inventory[0], L"After index removal, first item is not correct");

			inventory.remove(item2);

			// Verify correct removal by pointer
			Assert::AreEqual(1, inventory.numItems());
			Assert::IsTrue(item3 == inventory[0], L"After ptr removal, first item is not correct");

			inventory.remove(0);

			// Verify inventory can be emptied
			Assert::AreEqual(0, inventory.numItems());

			shared_ptr<Weapon> sword(new Weapon("Sword", 0.25f, 1.5f));
			shared_ptr<Shield> shield(new Shield("Shield"));

			inventory.addItem(sword);
			inventory.addItem(shield);

			// Verify find function works and is case insensitive
			Assert::AreNotEqual(-1, inventory.find("Sword"));
			Assert::AreNotEqual(-1, inventory.find("sword"));
			Assert::AreNotEqual(-1, inventory.find("Shield"));
			Assert::AreNotEqual(-1, inventory.find("shield"));

			int swordIndex = inventory.find("Sword");

			Assert::IsTrue(inventory[swordIndex] == sword, L"Index returned for sword was incorrect");
		}
	};
}
