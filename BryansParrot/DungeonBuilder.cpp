#include "DungeonBuilder.h"
#include "EnemyEncounter.h"
#include "Shield.h"
#include "Armor.h"

vector<string> DungeonBuilder::roomNames;

map<string, Room> DungeonBuilder::buildDungeon()
{
	//-----------------------------------------------------------------------
	// Create Room
	// 
	// *** All room names MUST BE UNIQUE ***
	//-----------------------------------------------------------------------
	map<string, Room> allRooms = {
		{"first_room",			Room()},
		{"second_room",			Room()},
		{"third_room",			Room()},
		{"fourth_room",			Room()},
		{"miniBossWestRoom",	Room()},
		{"miniBossEastRoom",	Room()},
		{"miniBossNorthRoom",	Room()},
		{"mainBossRoom",		Room()},
		{"fifthRoom",			Room()}
	};

	//-----------------------------------------------------------------------
	// Initializes static roomNames vector - DO NOT CHANGE
	//-----------------------------------------------------------------------

	roomNames.clear();
	for (map<string, Room>::iterator it = allRooms.begin(); it != allRooms.end(); it++)
		roomNames.push_back(it->first);

	//-----------------------------------------------------------------------

	//-----------------------------------------------------------------------
	// Create References to all rooms
	// 
	// Room& [RoomName] = allRooms.at("[CapsSensitiveRoomName]")
	//-----------------------------------------------------------------------
	Room& firstRoom = allRooms.at("first_room");
	Room& secondRoom = allRooms.at("second_room");
	Room& thirdRoom = allRooms.at("third_room");
	Room& fourthRoom = allRooms.at("fourth_room");
	Room& miniBossWestRoom = allRooms.at("miniBossWestRoom");
	Room& miniBossEastRoom = allRooms.at("miniBossEastRoom");
	Room& miniBossNorthRoom = allRooms.at("miniBossNorthRoom");
	Room& mainBossRoom = allRooms.at("mainBossRoom");
	Room& fithRoom = allRooms.at("fifthRoom");

	//-----------------------------------------------------------------------
	// Set up Room Connections
	// 
	// [Room].setRoom(Room::Direction::[Direction], &[OtherRoom], locks = 0, bothWays = true)
	// ...
	// 
	// Doors are automatically created in both directions unless specified
	// otherwise using the bothWays parameter:
	//
	// i.e. if roomA.setRoom(Room::Direction::NORTH, &roomB), roomB
	// will automatically set its south room to roomA
	//-----------------------------------------------------------------------
	
	//Room 1: Initialization
	firstRoom.setRoom(Room::Direction::NORTH, &secondRoom);

	//Room 2: Initialization
	secondRoom.setRoom(Room::Direction::NORTH, &thirdRoom, 2);

	//Room3: Initialization
	thirdRoom.setRoom(Room::Direction::NORTH, &fourthRoom);

	//Room4: Initialization
	fourthRoom.setRoom(Room::Direction::NORTH, &miniBossNorthRoom);
	fourthRoom.setRoom(Room::Direction::EAST, &miniBossEastRoom);
	fourthRoom.setRoom(Room::Direction::WEST, &miniBossWestRoom);

	//Mini North: Initialization
	miniBossNorthRoom.setRoom(Room::Direction::NORTH, &mainBossRoom, 3);

	//Boss: Initialization
	mainBossRoom.setRoom(Room::Direction::NORTH, &fithRoom, 1);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Items


	//-----------------------------------------------------------------------
	// Create Weapons
	// 
	// Weapon [WeaponName]("[Name]", [CritChance], [CritMultiplier])
	// [WeaponName].addAttackMove(AttackMove("[Name]", [MinDmg], [MaxDmg], [Stamina], [Accuracy])
	// ...
	// 
	//-----------------------------------------------------------------------
	Weapon goblinFists("Goblin Fists", 0.1f, 1.5f);
	goblinFists.addAttackMove(AttackMove("Punch", 5, 10, 1, 0.9f));

	Weapon trollFists("Troll Firsts", 0.1f, 1.5f);
	trollFists.addAttackMove(AttackMove("Punch", 5, 10, 1, 0.9f));

	Weapon sword("Sword", 0.25f, 1.65f);
	sword.addAttackMove(AttackMove("Stab", 20, 30, 1, 0.95f));
	sword.addAttackMove(AttackMove("Slash", 35, 50, 3, 0.75f));
	sword.setSpeedBoost(2);
	sword.setStaminaBoost(2);

	//-----------------------------------------------------------------------
	// Create Shields
	// 
	// Shield [ShieldName]("[Name]")
	// [ShieldName].setBlockMove(Shield::BlockType::[Type], { minBlock, maxBlock, stamina })
	// ...
	// 
	//-----------------------------------------------------------------------
	Shield shield("Shield");
	shield.setBlockMove(Shield::BlockType::SINGLE, { 25, 35, 1 });
	shield.setBlockMove(Shield::BlockType::GROUP, { 20, 30, 1 });
	shield.setStaminaBoost(2);

	//-----------------------------------------------------------------------
	// Create Armor
	// 
	// Armor [ArmorName]("[Name]", Armor::ArmorType::[Type], [Defense])
	// (Optional) [ArmorName].setHealthBoost([Amt])
	// ...
	// 
	//-----------------------------------------------------------------------
	Armor ironHelmet("Iron Helmet", Armor::ArmorType::HEAD, 3);
	Armor ironBreastplate("Iron Breastplate", Armor::ArmorType::CHEST, 5);
	ironBreastplate.setHealthBoost(50);
	Armor ironGreaves("Iron Greaves", Armor::ArmorType::LEGS, 2);
	ironGreaves.setHealthBoost(25);
	Armor ironBoots("Iron Boots", Armor::ArmorType::FEET, 1);
	Armor ironGauntlets("Iron Gauntlets", Armor::ArmorType::HANDS, 1);

	//-----------------------------------------------------------------------
	// Create Enemies
	// 
	// Enemy [EnemyName]("[Name]", [MaxHealth], [Speed], [Stamina], [DodgeChance], [DefaultWeapon])
	//-----------------------------------------------------------------------
	Enemy goblin("Goblin", 100, 5, 2, 0.5f, goblinFists);
	Enemy troll("Troll", 100, 5, 2, 0.5f, trollFists);
	Enemy mini1("Mini Boss West", 100, 20, 2, 0.75f, goblinFists);
	Enemy mini2("Mini Boss East", 100, 5, 4, 0.25f, goblinFists);
	Enemy mini3("Mini Boss North", 100, 10, 2, 0.5f, goblinFists);
	Enemy boss("Boss", 100, 15, 3, 0.65f, goblinFists);

	//-----------------------------------------------------------------------
	// Create Keys
	// 
	// Key [KeyName]([Room].getDoor(Room::Direction::[Direction]))
	//	OR
	// Key [KeyName]("[Name]", [Room].getDoor(Room::Direction::[Direction]))
	//	OR
	// Key [KeyName]()
	//-----------------------------------------------------------------------
	Key secondNorthKey("Iron Key", secondRoom.getDoor(Room::Direction::NORTH));
	Key mainBossKey("Skull Key", miniBossNorthRoom.getDoor(Room::Direction::NORTH));
	Key winRoomKey("Golden Key", mainBossRoom.getDoor(Room::Direction::NORTH));

	//-----------------------------------------------------------------------
	// Create Potions
	// 
	// Potion [PotionName]("[Name]", [Amount])
	//-----------------------------------------------------------------------
	Potion sPotion("Small Potion", 25);
	Potion mPotion("Medium Potion", 50);
	Potion lPotion("Large Potion", 100);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Encounters

	//-----------------------------------------------------------------------
	// Create Enemy Encounters
	// 
	// EnemyEncounter [EncounterName];
	// [EncounterName].addEnemy([EnemyName]);
	// ...
	// [EncounterName].addDrop(make_shared<[ItemSubclass]>([ItemName]);
	// ...
	//-----------------------------------------------------------------------
	
	//Second Room Encounter: Initialization
	EnemyEncounter secondRoomEncounter1;
	secondRoomEncounter1.addEnemy(goblin);
	secondRoomEncounter1.addEnemy(troll);
	secondRoomEncounter1.addDrop(make_shared<Key>(secondNorthKey));
	secondRoomEncounter1.addDrop(make_shared<Armor>(ironBreastplate));

	//Mini 1 Room Encounter: INitialization
	EnemyEncounter miniBossWestEncounter1;
	miniBossWestEncounter1.addEnemy(mini1);
	miniBossWestEncounter1.addDrop(make_shared<Key>(mainBossKey));
	miniBossWestEncounter1.addDrop(make_shared<Armor>(ironGauntlets));

	//Mini 2 Room Encounter: INitialization
	EnemyEncounter miniBossEastEncounter1;
	miniBossEastEncounter1.addEnemy(mini2);
	miniBossEastEncounter1.addDrop(make_shared<Key>(mainBossKey));
	miniBossEastEncounter1.addDrop(make_shared<Armor>(ironBoots));

	//Mini 3 Room Encounter: INitialization
	EnemyEncounter miniBossNorthEncounter1;
	miniBossNorthEncounter1.addEnemy(mini3);
	miniBossNorthEncounter1.addDrop(make_shared<Key>(mainBossKey));
	miniBossNorthEncounter1.addDrop(make_shared<Armor>(ironHelmet));

	//Main Boss Room Encounter: Initialization
	EnemyEncounter mainBossEcounter1;
	mainBossEcounter1.addEnemy(boss);
	mainBossEcounter1.addDrop(make_shared<Key>(winRoomKey));

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Room Initialization

	//-----------------------------------------------------------------------
	// Initialize Rooms
	// 
	// [RoomName].addItem(make_shared<[ItemSubclass]>([ItemName]);
	// ...
	// [RoomName].addEnemyEncounter([EnemyEncounterName]);
	// ...
	//-----------------------------------------------------------------------

	// First Room Init
	firstRoom.addItem(make_shared<Weapon>(sword));
	firstRoom.addItem(make_shared<Key>(secondNorthKey));
	firstRoom.addItem(make_shared<Shield>(shield));
	firstRoom.addItem(make_shared<Armor>(ironGreaves));

	// Second Room Init
	secondRoom.addEnemyEncounter(secondRoomEncounter1);

	// Third Room Init
	thirdRoom.addItem(make_shared<Potion>(sPotion));

	// Fourth Room Init
	fourthRoom.addItem(make_shared<Potion>(lPotion));

	// Mini Boss West Room Init
	miniBossWestRoom.addEnemyEncounter(miniBossWestEncounter1);

	// Mini Boss East Room Init
	miniBossEastRoom.addEnemyEncounter(miniBossEastEncounter1);

	// Mini Boss North Room Init
	miniBossNorthRoom.addEnemyEncounter(miniBossNorthEncounter1);

	// Main Boss Room Init
	mainBossRoom.addEnemyEncounter(mainBossEcounter1);

	return allRooms;
}

vector<string> DungeonBuilder::getRoomNames()
{
	return roomNames;
}
