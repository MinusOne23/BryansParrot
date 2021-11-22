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
	jailCell.setDescription("Jail Cell");
	Room& guardRoom = allRooms.at("Guard Room"); 
	guardRoom.setDescription("Guard Room");
	Room& controlRoom = allRooms.at("Control Room");
	controlRoom.setDescription("Control Room");
	Room& eastCorridor = allRooms.at("East Corridor");
	eastCorridor.setDescription("East Corridor");
	Room& cavernousChasm = allRooms.at("Cavernous Chasm");
	cavernousChasm.setDescription("Cavernous Chasm");
	Room& bryansParrot = allRooms.at("Bryan's Parrot");
	bryansParrot.setDescription("Bryan's Parrot");
	Room& eastSafeRoom = allRooms.at("East Safe Room");
	eastSafeRoom.setDescription("East Safe Room");
	Room& wearableTreasure = allRooms.at("Wearable Treasure");
	wearableTreasure.setDescription("Wearable Treasure");
	Room& condorLair = allRooms.at("Condor Lair");
	condorLair.setDescription("Condor Lair");
	Room& emergence = allRooms.at("Emergence");
	emergence.setDescription("Emergence");
	Room& cassoCareRoom = allRooms.at("CassoCare Room");
	cassoCareRoom.setDescription("CassoCare");
	Room& guessingRoom = allRooms.at("Guessing Room");
	guessingRoom.setDescription("Guessing Game");
	Room& pickledCraneRoom = allRooms.at("Pickled Crane Room");
	pickledCraneRoom.setDescription("Pickled Crane");
	Room& vultureSurpriseRoom = allRooms.at("Vulture Surprise Room");
	vultureSurpriseRoom.setDescription("Vulture Surprise");
	Room& safeRoomWest = allRooms.at("Safe Room West");
	safeRoomWest.setDescription("West Safe Room");
	Room& westCorridorRoom = allRooms.at("West Corridor Room");
	westCorridorRoom.setDescription("West Corridor");
	Room& usableTreasureRoom = allRooms.at("Usable Treasure Room");
	usableTreasureRoom.setDescription("Usable Treasure");

	/*
	*	Vulture Surprise  <->  Guessing Room   <->   Casso Care Room
	*		^
	*		v
	*	Pickled Crane Room							  Bryans Parrot
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
	controlRoom.setRoom(Room::Direction::NORTH, &bryansParrot,3);
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
	guessingRoom.setRoom(Room::Direction::WEST, &vultureSurpriseRoom);
	guessingRoom.setRoom(Room::Direction::EAST, &cassoCareRoom,1);

	//Pickled Crane Room: Initialization
	pickledCraneRoom.setRoom(Room::Direction::SOUTH, &safeRoomWest);

	//Vulture Room: Initialization
	vultureSurpriseRoom.setRoom(Room::Direction::SOUTH, &pickledCraneRoom);

	//Safe Room West: Initialization
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
	Weapon knife("knife", 0.50f, 1.70f);
	knife.addAttackMove(AttackMove("Puncture", 35, 60, 2, 0.30f));
	knife.addAttackMove(AttackMove("Slash", 18, 30, 1, 0.50f));
	knife.setSpeedBoost(5);
	knife.setStaminaBoost(4);

	Weapon pipe("Pipe", 0.30f, 1.40f);
	pipe.addAttackMove(AttackMove("Swing", 10, 20, 1, 0.80f));
	pipe.addAttackMove(AttackMove("Bash", 35, 50, 3, 0.70f));
	pipe.setSpeedBoost(2);
	pipe.setStaminaBoost(2);

	Weapon sword("Sword", 0.70f, 1.65f);
	sword.addAttackMove(AttackMove("Stab", 20, 30, 2, 0.95f));
	sword.addAttackMove(AttackMove("Slash", 35, 50, 2, 0.75f));
	sword.setSpeedBoost(3);
	sword.setStaminaBoost(3);

	Weapon bat("Bat", 0.65f, 1.75f);
	bat.addAttackMove(AttackMove("Swing", 30, 40, 2, 0.85f));
	bat.addAttackMove(AttackMove("Bash", 40, 60, 2, 0.70f));
	bat.setSpeedBoost(2);
	bat.setStaminaBoost(3);

	Weapon shovel("Shovel", 0.95f, 2.0f);
	shovel.addAttackMove(AttackMove("Swing", 30, 40, 3, 0.75f));
	shovel.addAttackMove(AttackMove("Slash", 35, 50, 3, 0.60f));
	shovel.setSpeedBoost(1);
	shovel.setStaminaBoost(2);

	Weapon wrench("Wrench", 0.25f, 1.65f);
	wrench.addAttackMove(AttackMove("Smash", 15, 25, 2, 0.80f));
	wrench.addAttackMove(AttackMove("Swing", 35, 50, 2, 0.60f));
	wrench.setSpeedBoost(3);
	wrench.setStaminaBoost(3);

	Weapon slingShot("Slingshot", 0.50f, 1.40f);
	slingShot.addAttackMove(AttackMove("Shoot", 20, 30, 2, 0.85f));
	slingShot.addAttackMove(AttackMove("Trickshot", 35, 45, 3, 0.50f));
	slingShot.setSpeedBoost(4);
	slingShot.setStaminaBoost(4);

	Weapon bbGun("BB Gun", 0.50f, 1.80f);
	bbGun.addAttackMove(AttackMove("Shoot", 35, 45, 2, 0.95f));
	bbGun.addAttackMove(AttackMove("Pellet", 60, 80, 4, 0.75f));
	bbGun.setSpeedBoost(1);
	bbGun.setStaminaBoost(3);

	Weapon elephantGun("Elephent Gun", 0.70f, 2.0f);
	elephantGun.addAttackMove(AttackMove("Shoot", 60, 75, 2, 0.95f));
	elephantGun.addAttackMove(AttackMove("Shotgun", 80, 110, 4, 0.80f));
	elephantGun.setSpeedBoost(1);
	elephantGun.setStaminaBoost(3);


	//-----------------------------------------------------------------------
	// Create Enemies
	// 
	// Enemy [EnemyName]("[Name]", [MaxHealth], [Speed], [Stamina], [DodgeChance], [DefaultWeapon])
	//-----------------------------------------------------------------------
	Enemy chicken("Chicken", 70, 5, 2, 0.5f, chickenHead);
	Enemy turkey("Turkey", 85, 8, 2, 0.5f, birdBeak);
	Enemy flamingo("Flamingo", 115, 10, 2, 0.5f, birdModel);
	Enemy crane("Crane", 160, 8, 4, 0.5f, birdDive);
	Enemy condor("Andian Condor", 160, 15, 2, 0.5f, birdWings);
	Enemy vulture("Vulture", 100, 10, 2, 0.6f, birdWings);
	Enemy kingVulture("King Vulture", 130, 10, 2, 0.3f, birdWings);
	Enemy miniWest("Cassowary", 200, 20, 4, 0.25f, birdLegs);
	Enemy miniEast("Ostrich", 150, 8, 4, 0.75f, birdCharge);
	Enemy miniNorth("ShoeBill", 100, 10, 4, 0.20f, birdScreach);
	Enemy boss("Parrot", 250, 15, 3, 0.65f, birdScratch);

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
	// Create Notes for rooms
	// 
	// Story [NoteName]("[Name]", "[message]")
	//-----------------------------------------------------------------------
	Story note1("Jail note", "What do i see");

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
	guardRoomEncounter.addDrop(make_shared<Weapon>(wrench));
	guardRoomEncounter.addDrop(make_shared<Potion>(sPotion));

	//East Corridor Encounter: Initialization
	EnemyEncounter eastCorridorEncounter;
	eastCorridorEncounter.addEnemy(turkey);
	eastCorridorEncounter.addEnemy(chicken);
	eastCorridorEncounter.addDrop(make_shared<Weapon>(knife));

	//Wearable Treasure Encounter: Initialization
	EnemyEncounter wearableTreasureEncounter1;
	wearableTreasureEncounter1.addEnemy(turkey);
	wearableTreasureEncounter1.addEnemy(chicken);
	wearableTreasureEncounter1.addEnemy(flamingo);
	EnemyEncounter wearableTreasureEncounter2;
	wearableTreasureEncounter2.addEnemy(flamingo);
	wearableTreasureEncounter2.addEnemy(kingVulture);
	wearableTreasureEncounter2.addEnemy(vulture);
	EnemyEncounter wearableTreasureEncounter3;
	wearableTreasureEncounter3.addEnemy(condor);
	wearableTreasureEncounter3.addEnemy(crane);

	//Condor Lair: Initialization
	EnemyEncounter condorLairEncounter;
	condorLairEncounter.addEnemy(condor);
	condorLairEncounter.addEnemy(turkey);
	condorLairEncounter.addDrop(make_shared<Key>(condorRoomKey));
	condorLairEncounter.addDrop(make_shared<Weapon>(slingShot));
	condorLairEncounter.addDrop(make_shared<Potion>(mPotion));

	//West Corridor Encounter: Initialization
	EnemyEncounter westCorridorRoomEncounter;
	westCorridorRoomEncounter.addEnemy(flamingo);
	westCorridorRoomEncounter.addEnemy(turkey);
	westCorridorRoomEncounter.addEnemy(chicken);
	westCorridorRoomEncounter.addDrop(make_shared<Weapon>(sword));
	westCorridorRoomEncounter.addDrop(make_shared<Potion>(mPotion));
	westCorridorRoomEncounter.addDrop(make_shared<Potion>(mPotion));
	

	//Usable Treasure Encounter: Initialization
	EnemyEncounter usableTreasureRoomEncounter1;
	usableTreasureRoomEncounter1.addEnemy(turkey);
	usableTreasureRoomEncounter1.addEnemy(chicken);
	usableTreasureRoomEncounter1.addEnemy(flamingo);
	EnemyEncounter usableTreasureRoomEncounter2;
	usableTreasureRoomEncounter2.addEnemy(flamingo);
	usableTreasureRoomEncounter2.addEnemy(vulture);
	usableTreasureRoomEncounter2.addEnemy(kingVulture);
	EnemyEncounter usableTreasureRoomEncounter3;
	usableTreasureRoomEncounter3.addEnemy(condor);
	usableTreasureRoomEncounter3.addEnemy(crane);
	usableTreasureRoomEncounter3.addDrop(make_shared<Weapon>(bbGun));
	usableTreasureRoomEncounter3.addDrop(make_shared<Potion>(lPotion));

	//Vulture Surprise Encounter: Initialization
	EnemyEncounter vultureSurpriseRoomEncounter;
	vultureSurpriseRoomEncounter.addEnemy(vulture);
	vultureSurpriseRoomEncounter.addEnemy(condor);
	vultureSurpriseRoomEncounter.addEnemy(kingVulture);
	vultureSurpriseRoomEncounter.addDrop(make_shared<Potion>(lPotion));
	

	//Pickled Crane Room Encounter: Initialization
	EnemyEncounter pickledCraneRoomEncounter;
	pickledCraneRoomEncounter.addEnemy(crane);
	pickledCraneRoomEncounter.addEnemy(flamingo);
	pickledCraneRoomEncounter.addEnemy(chicken);
	pickledCraneRoomEncounter.addDrop(make_shared<Potion>(lPotion));
	pickledCraneRoomEncounter.addDrop(make_shared<Potion>(lPotion));
	pickledCraneRoomEncounter.addDrop(make_shared<Weapon>(bat));

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
	miniBossNorthEncounter1.addDrop(make_shared<Weapon>(shovel));

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
	jailCell.addItem(make_shared<Story>(note1));

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
