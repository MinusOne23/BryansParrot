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
		{"Emergence",				Room()},
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
		{"Usable Treasure Room",	Room()},
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
	Room& guardRoom = allRooms.at("Guard Room"); 
	Room& controlRoom = allRooms.at("Control Room");
	Room& eastCorridor = allRooms.at("East Corridor");
	Room& cavernousChasm = allRooms.at("Cavernous Chasm");
	Room& bryansParrot = allRooms.at("Bryan's Parrot");
	Room& eastSafeRoom = allRooms.at("East Safe Room");
	Room& wearableTreasure = allRooms.at("Wearable Treasure");
	Room& condorLair = allRooms.at("Condor Lair");
	Room& emergence = allRooms.at("Emergence");
	Room& cassoCareRoom = allRooms.at("CassoCare Room");
	Room& guessingRoom = allRooms.at("Guessing Room");
	Room& pickledCraneRoom = allRooms.at("Pickled Crane Room");
	Room& vultureSurpriseRoom = allRooms.at("Vulture Surprise Room");
	Room& safeRoomWest = allRooms.at("Safe Room West");
	Room& westCorridorRoom = allRooms.at("West Corridor Room");
	Room& usableTreasureRoom = allRooms.at("Usable Treasure Room");

	/*
	*	Pickled Crane Room   <->   Guessing Room   <->   Casso Care Room
	*		^
	*		v
	*	Vulture Surprise							  Bryans Parrot
	*		^												^
	*		v												v
	*	safe Room West   <->   West Corridor   <->   Controll Room   <->   East Corridor   <->   Safe Room East   <->   Condor Lair
	*		^												^											^					 ^
	*		v												v										    v					 v
	*	usable Treasure									Guard Room								 Wearable Teasure	Cernous Chasm
	*														^
	*														v
	*													Jail Cell
	*/

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
	controlRoom.setRoom(Room::Direction::EAST, &eastCorridor);
	controlRoom.setRoom(Room::Direction::WEST, &westCorridorRoom);

	//BryansParrot: Initialization
	bryansParrot.setRoom(Room::Direction::NORTH, &emergence,1);
	
	//EastCorridor: Initialization
	eastCorridor.setRoom(Room::Direction::EAST, &eastSafeRoom);
	
	//EastSafeRoom: Initialization
	eastSafeRoom.setRoom(Room::Direction::WEST, &eastCorridor);
	eastSafeRoom.setRoom(Room::Direction::SOUTH, &wearableTreasure);
	eastSafeRoom.setRoom(Room::Direction::EAST, &condorLair);

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
	pickledCraneRoom.setRoom(Room::Direction::SOUTH, &vultureSurpriseRoom);

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
	
	//Enemy Weapons
	Weapon chickenHead("Chicken Head", 0.2f, 1.5f);
	chickenHead.addAttackMove(AttackMove("Headbutt", 5, 10, 1, 0.8f));

	Weapon birdLegs("Bird Legs", 0.3f, 2.0f);
	birdLegs.addAttackMove(AttackMove("Bicycle Kick", 4, 12, 1, 0.9f));

	Weapon birdBeak("Turkey Beak", 0.1f, 1.5f);
	birdBeak.addAttackMove(AttackMove("Peck", 10, 15, 2, 0.85f));

	Weapon birdWings("Vulture Wings", 0.3f, 1.75f);
	birdWings.addAttackMove(AttackMove("Fly", 10, 20, 2, 0.9f));

	Weapon birdCharge("Hatred", 0.8f, 2.0f);
	birdCharge.addAttackMove(AttackMove("Charge", 25, 40, 4, 0.8f));

	Weapon birdScreach("Microphone", 0.2f, 1.5f);
	birdScreach.addAttackMove(AttackMove("Song", 15, 30, 2, 1.0f));

	Weapon birdModel("Beauty", 0.2f, 1.5f);
	birdModel.addAttackMove(AttackMove("Attract", 5, 10, 2, 0.9f));

	Weapon birdDive("Crane Wings", 0.3f, 1.75f);
	birdDive.addAttackMove(AttackMove("Dive", 15, 25, 2, 0.9f));

	Weapon birdScratch("Talons", 0.5f, 1.5f);
	birdScratch.addAttackMove(AttackMove("Rampage", 8, 12, 1, 0.9f));
	//-----------------------------------------------------------------------
// Create Weapons
// 
// Weapon [WeaponName]("[Name]", [CritChance], [CritMultiplier]
// [WeaponName].addAttackMove(AttackMove("[Name]", [MinDmg], [MaxDmg], [Stamina], [Accuracy])
// ...
// 
//-----------------------------------------------------------------------

	//Player Weapons
	Weapon knife("knife", 0.25f, 1.65f);
	knife.addAttackMove(AttackMove("Puncture", 20, 30, 1, 0.20f));
	knife.addAttackMove(AttackMove("Slash", 35, 50, 3, .90f));
	knife.setSpeedBoost(2);
	knife.setStaminaBoost(2);

	Weapon pipe("Pipe", 0.25f, 1.65f);
	pipe.addAttackMove(AttackMove("Swing", 20, 30, 1, 0.95f));
	pipe.addAttackMove(AttackMove("Bash", 35, 50, 3, 0.75f));
	pipe.setSpeedBoost(2);
	pipe.setStaminaBoost(2);

	Weapon sword("Sword", 0.25f, 1.65f);
	sword.addAttackMove(AttackMove("Stab", 20, 30, 1, 0.95f));
	sword.addAttackMove(AttackMove("Slash", 35, 50, 3, 0.75f));
	sword.setSpeedBoost(2);
	sword.setStaminaBoost(2);

	Weapon bat("Bat", 0.25f, 1.65f);
	bat.addAttackMove(AttackMove("Stab", 20, 30, 1, 0.95f));
	bat.addAttackMove(AttackMove("Slash", 35, 50, 3, 0.75f));
	bat.setSpeedBoost(2);
	bat.setStaminaBoost(2);

	Weapon shovel("shovel", 0.25f, 1.65f);
	shovel.addAttackMove(AttackMove("Stab", 20, 30, 1, 0.95f));
	shovel.addAttackMove(AttackMove("Slash", 35, 50, 3, 0.75f));
	shovel.setSpeedBoost(2);
	shovel.setStaminaBoost(2);

	Weapon wrench("Wrench", 0.25f, 1.65f);
	wrench.addAttackMove(AttackMove("Stab", 20, 30, 1, 0.95f));
	wrench.addAttackMove(AttackMove("Slash", 35, 50, 3, 0.75f));
	wrench.setSpeedBoost(2);
	wrench.setStaminaBoost(2);

	Weapon slingShot("Slingshot", 0.25f, 1.65f);
	slingShot.addAttackMove(AttackMove("Stab", 20, 30, 1, 0.95f));
	slingShot.addAttackMove(AttackMove("Slash", 35, 50, 3, 0.75f));
	slingShot.setSpeedBoost(2);
	slingShot.setStaminaBoost(2);

	Weapon bbGun("BB Gunn", 0.25f, 1.65f);
	bbGun.addAttackMove(AttackMove("Stab", 20, 30, 1, 0.95f));
	bbGun.addAttackMove(AttackMove("Slash", 35, 50, 3, 0.75f));
	bbGun.setSpeedBoost(2);
	bbGun.setStaminaBoost(2);

	Weapon elephantGun("Elephent Gun", 0.25f, 1.65f);
	elephantGun.addAttackMove(AttackMove("Stab", 20, 30, 1, 0.95f));
	elephantGun.addAttackMove(AttackMove("Slash", 35, 50, 3, 0.75f));
	elephantGun.setSpeedBoost(2);
	elephantGun.setStaminaBoost(2);


	//-----------------------------------------------------------------------
	// Create Enemies
	// 
	// Enemy [EnemyName]("[Name]", [MaxHealth], [Speed], [Stamina], [DodgeChance], [DefaultWeapon])
	//-----------------------------------------------------------------------
	Enemy chicken("Chicken", 100, 5, 2, 0.5f, chickenHead);
	Enemy turkey("Turkey", 100, 8, 2, 0.5f, birdBeak);
	Enemy flamingo("Flamingo", 100, 10, 2, 0.5f, birdModel);
	Enemy crane("Crane", 100, 8, 4, 0.5f, birdDive);
	Enemy condor("Andian Condor", 100, 15, 2, 0.5f, birdWings);
	Enemy vulture("Vulture", 100, 10, 2, 0.5f, birdWings);
	Enemy kingVulture("King Vulture", 100, 12, 2, 0.5f, birdWings);
	Enemy miniWest("Cassowary", 100, 20, 2, 0.75f, birdLegs);
	Enemy miniEast("Ostrich", 100, 4, 4, 0.25f, birdCharge);
	Enemy miniNorth("ShoeBill", 100, 10, 4, 0.5f, birdScreach);
	Enemy boss("Parrot", 100, 15, 3, 0.65f, birdScratch);

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
	Key secretRoomKey("Cassowary Room Key", guessingRoom.getDoor(Room::Direction::EAST));

	//-----------------------------------------------------------------------
	// Create Potions
	// 
	// Potion [PotionName]("[Name]", [Amount])
	//-----------------------------------------------------------------------
	Potion sPotion("Small Potion", 25);
	Potion mPotion("Medium Potion", 50);
	Potion lPotion("Large Potion", 100);

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
	EnemyEncounter guardRoomEncounter;
	guardRoomEncounter.addEnemy(chicken);
	guardRoomEncounter.addDrop(make_shared<Key>(guardRoomKey));

	//East Corridor Encounter: Initialization
	EnemyEncounter eastCorridorEncounter;
	eastCorridorEncounter.addEnemy(turkey);
	eastCorridorEncounter.addEnemy(chicken);

	//Wearable Treasure Encounter: Initialization
	EnemyEncounter wearableTreasureEncounter1;
	wearableTreasureEncounter1.addEnemy(turkey);
	wearableTreasureEncounter1.addEnemy(chicken);
	wearableTreasureEncounter1.addEnemy(flamingo);
	EnemyEncounter wearableTreasureEncounter2;
	wearableTreasureEncounter2.addEnemy(flamingo);
	wearableTreasureEncounter2.addEnemy(condor);
	wearableTreasureEncounter2.addEnemy(vulture);
	EnemyEncounter wearableTreasureEncounter3;
	wearableTreasureEncounter3.addEnemy(condor);
	wearableTreasureEncounter3.addEnemy(crane);

	//Condor Lair: Initialization
	EnemyEncounter condorLairEncounter;
	condorLairEncounter.addEnemy(condor);
	condorLairEncounter.addEnemy(turkey);
	condorLairEncounter.addDrop(make_shared<Key>(condorRoomKey));

	//West Corridor Encounter: Initialization
	EnemyEncounter westCorridorRoomEncounter;
	westCorridorRoomEncounter.addEnemy(flamingo);
	westCorridorRoomEncounter.addEnemy(turkey);
	westCorridorRoomEncounter.addEnemy(chicken);

	//Usable Treasure Encounter: Initialization
	EnemyEncounter usableTreasureRoomEncounter1;
	usableTreasureRoomEncounter1.addEnemy(turkey);
	usableTreasureRoomEncounter1.addEnemy(chicken);
	usableTreasureRoomEncounter1.addEnemy(flamingo);
	EnemyEncounter usableTreasureRoomEncounter2;
	usableTreasureRoomEncounter2.addEnemy(flamingo);
	usableTreasureRoomEncounter2.addEnemy(vulture);
	usableTreasureRoomEncounter2.addEnemy(condor);
	EnemyEncounter usableTreasureRoomEncounter3;
	usableTreasureRoomEncounter3.addEnemy(condor);
	usableTreasureRoomEncounter3.addEnemy(crane);

	//Vulture Surprise Encounter: Initialization
	EnemyEncounter vultureSurpriseRoomEncounter;
	vultureSurpriseRoomEncounter.addEnemy(vulture);
	vultureSurpriseRoomEncounter.addEnemy(condor);
	vultureSurpriseRoomEncounter.addEnemy(kingVulture);

	//Pickled Crane Room Encounter: Initialization
	EnemyEncounter pickledCraneRoomEncounter;
	pickledCraneRoomEncounter.addEnemy(crane);
	pickledCraneRoomEncounter.addEnemy(flamingo);
	pickledCraneRoomEncounter.addEnemy(chicken);

	//Guessing Room Encounter: Initialization
	EnemyEncounter guessingRoomEncounter;
	guessingRoomEncounter.addEnemy(turkey);
	guessingRoomEncounter.addEnemy(kingVulture);
	
	//MiniWest Room Encounter: INitialization
	EnemyEncounter miniBossWestEncounter1;
	miniBossWestEncounter1.addEnemy(miniWest);
	miniBossWestEncounter1.addDrop(make_shared<Key>(mainBossKey));
	miniBossWestEncounter1.addDrop(make_shared<Potion>(lPotion));

	//MiniEast Room Encounter: INitialization
	EnemyEncounter miniBossEastEncounter1;
	miniBossEastEncounter1.addEnemy(miniEast);
	miniBossEastEncounter1.addDrop(make_shared<Key>(mainBossKey1));
	miniBossEastEncounter1.addDrop(make_shared<Potion>(lPotion));
	//MiniNorth Room Encounter: INitialization
	EnemyEncounter miniBossNorthEncounter1;
	miniBossNorthEncounter1.addEnemy(miniNorth);
	miniBossNorthEncounter1.addDrop(make_shared<Key>(mainBossKey2));
	miniBossNorthEncounter1.addDrop(make_shared<Potion>(lPotion));

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

	// JailCell Init
	jailCell.addItem(make_shared<Weapon>(pipe));
	jailCell.addItem(make_shared<Key>(jailKey));

	// GuardRoom Init
	guardRoom.addEnemyEncounter(guardRoomEncounter);

	// ControlRoom Init	
	// Mini Boss North Room Init
	controlRoom.addEnemyEncounter(miniBossNorthEncounter1);

	// East Corridor Init
	eastCorridor.addEnemyEncounter(eastCorridorEncounter);

	// Safe Room East Init
	eastSafeRoom.addItem(make_shared<Potion>(lPotion));

	// Wearable Treasure Init
	wearableTreasure.addEnemyEncounter(wearableTreasureEncounter1);
	wearableTreasure.addEnemyEncounter(wearableTreasureEncounter2);
	wearableTreasure.addEnemyEncounter(wearableTreasureEncounter3);
	
	// CondorLair Init
	condorLair.addEnemyEncounter(condorLairEncounter);

	// Cavernous Chasm Init
	// Mini Boss East Room Init
	cavernousChasm.addEnemyEncounter(miniBossEastEncounter1);

	// West Corridor Init
	westCorridorRoom.addEnemyEncounter(westCorridorRoomEncounter);

	// Safe Room West Init
	safeRoomWest.addItem(make_shared<Potion>(lPotion));

	// Usable Treasure Room Init
	usableTreasureRoom.addEnemyEncounter(usableTreasureRoomEncounter1);
	usableTreasureRoom.addEnemyEncounter(usableTreasureRoomEncounter2);
	usableTreasureRoom.addEnemyEncounter(usableTreasureRoomEncounter3);

	// Vulture Surprise Room Init
	vultureSurpriseRoom.addEnemyEncounter(vultureSurpriseRoomEncounter);

	//Pickled Crane Room Init
	pickledCraneRoom.addItem(make_shared<Key>(secretRoomKey));
	pickledCraneRoom.addEnemyEncounter(pickledCraneRoomEncounter);

	// Guessing Room Init
	guessingRoom.addEnemyEncounter(guessingRoomEncounter);

	// CassoCare Room Init
	// Mini Boss West Room Init
	cassoCareRoom.addEnemyEncounter(miniBossWestEncounter1);

	// Bryans Parrot Init
	// Main Boss Room Init
	bryansParrot.addEnemyEncounter(mainBossEcounter1);

	return allRooms;
}

vector<string> DungeonBuilder::getRoomNames()
{
	return roomNames;
}
