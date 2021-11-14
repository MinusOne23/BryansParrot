#include "DungeonBuilder.h"
#include "EnemyEncounter.h"

vector<string> DungeonBuilder::roomNames;

map<string, Room> DungeonBuilder::buildDungeon()
{
	//-----------------------------------------------------------------------
	// Create Room
	// 
	// *** All room names MUST BE UNIQUE ***
	//-----------------------------------------------------------------------
	map<string, Room> allRooms = {
		{"Jail Cell",				Room()},
		{"Guard Room",				Room()},
		{"Control Room",			Room()},
		{"Bryan's Parrot",			Room()},
		{"East Corridor",			Room()},
		{"East Safe Room",			Room()},
		{"Wearable Treasure",		Room()},
		{"Condor Lair",				Room()},
		{"Cavernous Chasm",			Room()},
		{"CassoCare Room",			Room()},
		{"Guessing Room",			Room()},
		{"Pickled Crane Room",		Room()},
		{"Vulture Surprise Room",	Room()},
		{"Safe Room West",			Room()},
		{"West Corridor Room",		Room()},
		{"Usale Treasure Room",		Room()},
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
	Room& jailCell = allRooms.at("Jail Cell");
	Room& guardRoom = allRooms.at("Guard Room"); //
	Room& controlRoom = allRooms.at("Control Room");
	Room& eastCorridor = allRooms.at("East Corridor");
	Room& cavernousChasm = allRooms.at("Cavernous Chasm");
	Room& bryansParrot = allRooms.at("Bryan's Parrot");
	Room& eastSafeRoom = allRooms.at("East Safe Room");
	Room& wearableTreasure = allRooms.at("Wearable Treasure");
	Room& condorLair= allRooms.at("Condor Lair");
	Room& emergence = allRooms.at("Emergence");
	Room& cassoCareRoom = allRooms.at("CassoCare Room");
	Room& guessingRoom = allRooms.at("Guessing Room");
	Room& pickledCraneRoom = allRooms.at("Pickcled Crane Room");
	Room& vultureSurpriseRoom = allRooms.at("Vulture Surprise Room");
	Room& safeRoomWest = allRooms.at("Safe Room West");
	Room& westCorridorRoom = allRooms.at("West Corridor Room");
	Room& usableTreasureRoom = allRooms.at("Usable Treasure Room");

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
	
	//JailCell: Initialization
	jailCell.setRoom(Room::Direction::NORTH, &guardRoom, 1);

	//GuardRoom: Initialization
	guardRoom.setRoom(Room::Direction::NORTH, &controlRoom,1);

	//ControlRoom: Initialization
	controlRoom.setRoom(Room::Direction::NORTH, &bryansParrot, 3);
	controlRoom.setRoom(Room::Direction::EAST, &eastSafeRoom);
	controlRoom.setRoom(Room::Direction::WEST, &westCorridorRoom);

	//BryansParrot: Initialization
	bryansParrot.setRoom(Room::Direction::NORTH, &emergence);
	
	//EastCorridor: Initialization
	eastCorridor.setRoom(Room::Direction::EAST, &condorLair);
	eastCorridor.setRoom(Room::Direction::SOUTH, &wearableTreasure);

	//CondorLair: Initialization
	condorLair.setRoom(Room::Direction:: SOUTH, &cavernousChasm,1);

	//CavernousChasm: Initialization
	cavernousChasm.setRoom(Room::Direction::EAST, &jailCell,0, false);

	//CassoCare Room: Initialization
	cassoCareRoom.setRoom(Room::Direction::WEST, &guessingRoom);
	cassoCareRoom.setRoom(Room::Direction::EAST, &jailCell,0,false);

	//Guessing Room: Initialization
	guessingRoom.setRoom(Room::Direction::WEST, &pickledCraneRoom);
	guessingRoom.setRoom(Room::Direction::EAST, &cassoCareRoom,1);

	//Pickled Crane Room: Initialization
	pickledCraneRoom.setRoom(Room::Direction::SOUTH, &vultureSurpriseRoom,1);

	//Vulture Room: Initialization
	vultureSurpriseRoom.setRoom(Room::Direction::SOUTH, &safeRoomWest);

	//Safe Room: Initialization
	safeRoomWest.setRoom(Room::Direction::EAST, &westCorridorRoom);
	safeRoomWest.setRoom(Room::Direction::SOUTH, &usableTreasureRoom);

	//West Corridor: Initialization
	westCorridorRoom.setRoom(Room::Direction::EAST, &controlRoom);

	//Usable Treasure: Initialization
	usableTreasureRoom.setRoom(Room::Direction::NORTH, &safeRoomWest);


	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Items


	//-----------------------------------------------------------------------
	// Create Weapons
	// 
	// Weapon [WeaponName]("[Name]", [CritChance], [CritMultiplier]
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
	// Create Enemies
	// 
	// Enemy [EnemyName]("[Name]", [MaxHealth], [Speed], [Stamina], [DodgeChance], [DefaultWeapon])
	//-----------------------------------------------------------------------
	Enemy goblin("Goblin", 100, 5, 2, 0.5f, goblinFists);
	Enemy troll("Troll", 100, 5, 2, 0.5f, trollFists);
	Enemy miniWest("Cassowary", 100, 20, 2, 0.75f, goblinFists);
	Enemy miniEast("Ostrich", 100, 5, 4, 0.25f, goblinFists);
	Enemy miniNorth("ShoeBill", 100, 10, 2, 0.5f, goblinFists);
	Enemy boss("Bryan's Parrot", 100, 15, 3, 0.65f, goblinFists);

	//-----------------------------------------------------------------------
	// Create Keys
	// 
	// Key [KeyName]([Room].getDoor(Room::Direction::[Direction]))
	//	OR
	// Key [KeyName]("[Name]", [Room].getDoor(Room::Direction::[Direction]))
	//	OR
	// Key [KeyName]()
	//-----------------------------------------------------------------------
	
	Key jailKey("Jail Cell Key", jailCell.getDoor(Room::Direction::NORTH));
	Key guardRoomKey("Guard Room Key", guardRoom.getDoor(Room::Direction::NORTH));
	Key mainBossKey("Parrot Skull Key", controlRoom.getDoor(Room::Direction::NORTH));
	Key mainBossKey1("Blue Feather Key", controlRoom.getDoor(Room::Direction::NORTH));
	Key mainBossKey2("Green Feather Key", controlRoom.getDoor(Room::Direction::NORTH));
	Key winRoomKey("Golden Key", bryansParrot.getDoor(Room::Direction::NORTH));
	Key condorRoomKey("Ostrich Room Key", condorLair.getDoor(Room::Direction::SOUTH));
	Key cassoCareRoomKey("Cassowary Room Key", guessingRoom.getDoor(Room::Direction::EAST));

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
	
	//Guard Room Encounter: Initialization
	EnemyEncounter secondRoomEncounter1;
	secondRoomEncounter1.addEnemy(goblin);
	secondRoomEncounter1.addEnemy(troll);
	secondRoomEncounter1.addDrop(make_shared<Key>(guardRoomKey));

	//MiniWest Room Encounter: INitialization
	EnemyEncounter miniBossWestEncounter1;
	miniBossWestEncounter1.addEnemy(miniWest);
	miniBossWestEncounter1.addDrop(make_shared<Key>(mainBossKey));

	//MiniEast Room Encounter: INitialization
	EnemyEncounter miniBossEastEncounter1;
	miniBossEastEncounter1.addEnemy(miniEast);
	miniBossEastEncounter1.addDrop(make_shared<Key>(mainBossKey1));

	//MiniNorth Room Encounter: INitialization
	EnemyEncounter miniBossNorthEncounter1;
	miniBossNorthEncounter1.addEnemy(miniNorth);
	miniBossNorthEncounter1.addDrop(make_shared<Key>(mainBossKey2));

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
	jailCell.addItem(make_shared<Weapon>(sword));
	jailCell.addItem(make_shared<Key>(jailKey));

	// Second Room Init
	guardRoom.addEnemyEncounter(secondRoomEncounter1);

	// Third Room Init
	controlRoom.addItem(make_shared<Potion>(sPotion));

	// Fourth Room Init
	bryansParrot.addItem(make_shared<Potion>(lPotion));

	// Mini Boss West Room Init
	cassoCareRoom.addEnemyEncounter(miniBossWestEncounter1);

	// Mini Boss East Room Init
	cavernousChasm.addEnemyEncounter(miniBossEastEncounter1);

	// Mini Boss North Room Init
	controlRoom.addEnemyEncounter(miniBossNorthEncounter1);

	// Main Boss Room Init
	bryansParrot.addEnemyEncounter(mainBossEcounter1);

	return allRooms;
}

vector<string> DungeonBuilder::getRoomNames()
{
	return roomNames;
}
