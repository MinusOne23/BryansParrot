#include "DungeonBuilder.h"
#include "EnemyEncounter.h"
#include "Shield.h"
#include "Armor.h"

vector<string> DungeonBuilder::roomNames;

map<string, Room> DungeonBuilder::buildDungeon()
{
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
	guardRoom.setRoom(Room::Direction::NORTH, &controlRoom, 1);

	//ControlRoom: Initialization
	controlRoom.setRoom(Room::Direction::NORTH, &bryansParrot, 3);
	controlRoom.setRoom(Room::Direction::EAST, &eastCorridor);
	controlRoom.setRoom(Room::Direction::WEST, &westCorridorRoom);

	//BryansParrot: Initialization
	bryansParrot.setRoom(Room::Direction::NORTH, &emergence, 1);

	//EastCorridor: Initialization
	eastCorridor.setRoom(Room::Direction::EAST, &eastSafeRoom);

	//EastSafeRoom: Initialization
	eastSafeRoom.setRoom(Room::Direction::WEST, &eastCorridor);
	eastSafeRoom.setRoom(Room::Direction::SOUTH, &wearableTreasure);
	eastSafeRoom.setRoom(Room::Direction::EAST, &condorLair);

	//CondorLair: Initialization
	condorLair.setRoom(Room::Direction::SOUTH, &cavernousChasm, 1);

	//CavernousChasm: Initialization
	cavernousChasm.setRoom(Room::Direction::EAST, &jailCell, 0, false);

	//CassoCare Room: Initialization
	cassoCareRoom.setRoom(Room::Direction::WEST, &guessingRoom);
	cassoCareRoom.setRoom(Room::Direction::EAST, &jailCell, 0, false);

	//Guessing Room: Initialization
	guessingRoom.setRoom(Room::Direction::WEST, &vultureSurpriseRoom);
	guessingRoom.setRoom(Room::Direction::EAST, &cassoCareRoom, 1);

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
	// Weapon [WeaponName]("[Name]", [CritChance], [CritMultiplier])
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
	birdModel.addAttackMove(AttackMove("Attract", 8, 18, 2, 0.9f));

	Weapon birdDive("Crane Wings", 0.3f, 1.75f);
	birdDive.addAttackMove(AttackMove("Dive", 15, 25, 2, 0.9f));

	Weapon birdScratch("Talons", 0.5f, 1.5f);
	birdScratch.addAttackMove(AttackMove("Rampage", 8, 12, 1, 0.9f));

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
	// Create Shields
	// 
	// Shield [ShieldName]("[Name]")
	// [ShieldName].setBlockMove(Shield::BlockType::[Type], { minBlock, maxBlock, stamina })
	// ...
	// 
	//-----------------------------------------------------------------------
	Shield trashShield("Trash Can Lid");
	trashShield.setBlockMove(Shield::BlockType::SINGLE, { 10, 15, 2 });
	trashShield.setBlockMove(Shield::BlockType::GROUP, { 8, 15, 4 });
	trashShield.setStaminaBoost(2);

	Shield wokShield("Wok Pan");
	wokShield.setBlockMove(Shield::BlockType::SINGLE, { 15, 25, 2 });
	wokShield.setBlockMove(Shield::BlockType::GROUP, { 12, 25, 4 });
	wokShield.setStaminaBoost(2);

	Shield riotshield("Riot Shield");
	riotshield.setBlockMove(Shield::BlockType::SINGLE, { 25, 35, 2 });
	riotshield.setBlockMove(Shield::BlockType::GROUP, { 18, 35, 4 });
	riotshield.setStaminaBoost(2);

	//-----------------------------------------------------------------------
	// Create Armor
	// 
	// Armor [ArmorName]("[Name]", Armor::ArmorType::[Type], [Defense])
	// (Optional) [ArmorName].setHealthBoost([Amt])
	// ...
	// 
	//-----------------------------------------------------------------------
	Armor motercycleHelmet("Motercycle Helmet", Armor::ArmorType::HEAD, 3);
	Armor leatherJacket("Leather jacket", Armor::ArmorType::CHEST, 5);
	leatherJacket.setHealthBoost(50);
	Armor leatherPants("Leather Pants", Armor::ArmorType::LEGS, 2);
	leatherPants.setHealthBoost(25);
	Armor constructionBoots("Construction Boots", Armor::ArmorType::FEET, 1);
	Armor leatherGloves("leather Gloves", Armor::ArmorType::HANDS, 1);

	Armor sonicHead("Sonic the Hedgehog Foam Head", Armor::ArmorType::HEAD, 6);
	Armor sonicChest("Sonic the Hedgehog costume Torso", Armor::ArmorType::CHEST, 10);
	sonicChest.setHealthBoost(100);
	Armor sonicLegs("Sonic the Hedgehog blue Legs", Armor::ArmorType::LEGS, 4);
	sonicLegs.setHealthBoost(50);
	Armor sonicShoes("Sonic the Hedgehog red shoes", Armor::ArmorType::FEET, 2);
	Armor sonicGloves("Sonic the Hedgehog white Gloves", Armor::ArmorType::HANDS, 2);


	//-----------------------------------------------------------------------
	// Create Enemies
	// 
	// Enemy [EnemyName]("[Name]", [MaxHealth], [Speed], [Stamina], [DodgeChance], [DefaultWeapon])
	//-----------------------------------------------------------------------
	Enemy chicken("Chicken", 80, 5, 2, 0.5f, chickenHead);
	Enemy turkey("Turkey", 105, 8, 2, 0.5f, birdBeak);
	Enemy flamingo("Flamingo", 125, 10, 2, 0.5f, birdModel);
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
	Key condorRoomKey("White Feather Key", condorLair.getDoor(Room::Direction::SOUTH));
	Key secretRoomKey("Black Feather Key", guessingRoom.getDoor(Room::Direction::EAST));

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
	Story jailCellNote("Jail Note", "\tHello to whoever is reading this, if you're wondering...My name is Kevin, yes, \n"
		"\tI'm the dead body next to you. This place is pretty freaky!! I'm trapped, and the\n"
		"\tonly door that is locked is right in front of you. All I know is that I'm surrounded\n"
		"\tby dark brick walls and bird poo. I wonder what will be out there for me... ");

	Story guardRoomNote("Guard Note", "\tI was stunned to see the room was painted in bright white with torches all around.\n"
		"\tIn the background, I remember you could see two chicken pedestals with the enemy\n"
		"\tbetween them. I don't know how but I found a Garbage Lid and Armor on the side of\n"
		"\tthe room covered in chicken feed. Pretty useful to protect yourself from attacks, \n"
		"\tdon’t you think? ");

	Story controlRoomNote("Control Note", "\tIt was creepy, when I walked in, the whole place was surrounded by multiple\n"
		"\tmonitors and the main monitor displayed a parrot flying. The room itself was pretty\n"
		"\tdark with a few lights on the sealing. I remember the floor being wet, I did not\n"
		"\trealize that when looked up, I saw the terrifying Shoebill! It was the ugliest bird\n"
		"\tI have ever seen, covered in in thick silver grey feathers with a wide gape. ");

	Story safeRoomWestNote("West Note", "\tI've escaped danger... for now. This room was different from the others, It\n"
		"\twas very comfortable. This room looks like an office, with elevator music tranquil\n"
		"\tsongs and birds chirping. I also saw a bunch of snacks which was pretty lucky because I \n"
		"\twas so hungry. I remember you could find some Armour on the other\n"
		"\twall, there is a casket with a Large Health Potion as well. ");

	Story pickledCraneNote("Crane Note", "\tThis room is rather calming, but I'm not. This haunts me I swear, the majestic\n"
		"\tCrane was waiting for me in the back you know, it is one of the tallest birds in\n"
		"\tthe world. And this majestic bird is not alone either!! The bird might be pretty,\n"
		"\tbut its also vey feisty.  ");

	Story cassocareRoomNote("CassoCare Note", "\tThis room is giving me vegetarian vibes, there are fruits, leaves and a\n"
		"\tbunch of other natural resources, perfect habitat for the ferocious Cassowary, \n"
		"\tthis feisty bird will make your life miserable if it's in your way!! Cassowaries\n"
		"\tare very wary especially of humans, but if provoked, they are capable of inflicting\n"
		"\tserious, even fatal, injuries towards you. ");

	Story safeRoomEastNote("East Note", "\tHurray, I have escaped danger, I guess. This room is pretty comfortable if I\n"
		"\tsay so myself. This room looks like a living room, pretty organized I would say,\n"
		"\twith music playing bird songs and snacks on the side of the door. On the walls,\n"
		"\tI noticed a casket with a Large Health Potion, could help to get my helth back up. ");

	Story cavernousChasmNote("Chasm Note", "\tAs far as I know the Ostrich is the largest bird in the animal kingdom.\n"
		"\tNot a bird that you want to take lightly, these birds will eat anything that's in\n"
		"\tits path, and it might swallow you whole. They are pretty fast too with those long legs.  ");

	Story bryansParrotNote("Kevins Note", "\tWhoever is reading this, it was that thing......the parrot, he did this!!\n"
		"\tNo wonder everything was bird related. I do not understand why I had to end up\n"
		"\there in this shallow of a prison. This bird is small, but he is the strongest\n"
		"\tthing I have ever seen. And as you know, I'm dead, which means I didn't make it\n"
		"\tout, but if someone is reading this I know you can get out of this Bird Hell! I\n"
		"\tbelieve in you, I know you can make it out alive and see the sun again. Good Luck,\n"
		"\tand farewell, hopefully you have better luck than me.");

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
	guardRoomEncounter.addDrop(make_shared<Armor>(leatherPants));
	guardRoomEncounter.addDrop(make_shared<Shield>(trashShield));

	//East Corridor Encounter: Initialization
	EnemyEncounter eastCorridorEncounter;
	eastCorridorEncounter.addEnemy(turkey);
	eastCorridorEncounter.addEnemy(chicken);
	eastCorridorEncounter.addDrop(make_shared<Weapon>(knife));
	eastCorridorEncounter.addDrop(make_shared<Armor>(motercycleHelmet));

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
	wearableTreasureEncounter3.addDrop(make_shared<Armor>(sonicHead));
	wearableTreasureEncounter3.addDrop(make_shared<Armor>(sonicChest));
	wearableTreasureEncounter3.addDrop(make_shared<Armor>(sonicLegs));
	wearableTreasureEncounter3.addDrop(make_shared<Armor>(sonicGloves));
	wearableTreasureEncounter3.addDrop(make_shared<Armor>(sonicShoes));

	//Condor Lair: Initialization
	EnemyEncounter condorLairEncounter;
	condorLairEncounter.addEnemy(condor);
	condorLairEncounter.addEnemy(turkey);
	condorLairEncounter.addDrop(make_shared<Key>(condorRoomKey));
	condorLairEncounter.addDrop(make_shared<Weapon>(slingShot));
	condorLairEncounter.addDrop(make_shared<Potion>(mPotion));
	condorLairEncounter.addDrop(make_shared<Armor>(leatherGloves));
	condorLairEncounter.addDrop(make_shared<Shield>(wokShield));

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
	pickledCraneRoomEncounter.addDrop(make_shared<Shield>(riotshield));

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
	miniBossEastEncounter1.addDrop(make_shared<Armor>(constructionBoots));

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
	jailCell.addItem(make_shared<Story>(jailCellNote));

	// GuardRoom Init
	guardRoom.addEnemyEncounter(guardRoomEncounter);
	guardRoom.addItem(make_shared<Story>(guardRoomNote));

	// ControlRoom Init	
	// Mini Boss North Room Init
	controlRoom.addEnemyEncounter(miniBossNorthEncounter1);
	controlRoom.addItem(make_shared<Story>(controlRoomNote));

	// East Corridor Init
	eastCorridor.addEnemyEncounter(eastCorridorEncounter);

	// Safe Room East Init
	eastSafeRoom.addItem(make_shared<Potion>(lPotion));
	eastSafeRoom.addItem(make_shared<Story>(safeRoomEastNote));

	// Wearable Treasure Init
	wearableTreasure.addEnemyEncounter(wearableTreasureEncounter1);
	wearableTreasure.addEnemyEncounter(wearableTreasureEncounter2);
	wearableTreasure.addEnemyEncounter(wearableTreasureEncounter3);

	// CondorLair Init
	condorLair.addEnemyEncounter(condorLairEncounter);

	// Cavernous Chasm Init
	// Mini Boss East Room Init
	cavernousChasm.addEnemyEncounter(miniBossEastEncounter1);
	cavernousChasm.addItem(make_shared<Story>(cassocareRoomNote));

	// West Corridor Init
	westCorridorRoom.addEnemyEncounter(westCorridorRoomEncounter);

	// Safe Room West Init
	safeRoomWest.addItem(make_shared<Potion>(lPotion));
	safeRoomWest.addItem(make_shared<Story>(safeRoomWestNote));
	safeRoomWest.addItem(make_shared<Armor>(leatherJacket));

	// Usable Treasure Room Init
	usableTreasureRoom.addEnemyEncounter(usableTreasureRoomEncounter1);
	usableTreasureRoom.addEnemyEncounter(usableTreasureRoomEncounter2);
	usableTreasureRoom.addEnemyEncounter(usableTreasureRoomEncounter3);

	// Vulture Surprise Room Init
	vultureSurpriseRoom.addEnemyEncounter(vultureSurpriseRoomEncounter);

	//Pickled Crane Room Init
	pickledCraneRoom.addItem(make_shared<Key>(secretRoomKey));
	pickledCraneRoom.addEnemyEncounter(pickledCraneRoomEncounter);
	pickledCraneRoom.addItem(make_shared<Story>(pickledCraneNote));

	// Guessing Room Init
	guessingRoom.addEnemyEncounter(guessingRoomEncounter);

	// CassoCare Room Init
	// Mini Boss West Room Init
	cassoCareRoom.addEnemyEncounter(miniBossWestEncounter1);
	cassoCareRoom.addItem(make_shared<Story>(cassocareRoomNote));

	// Bryans Parrot Init
	// Main Boss Room Init
	bryansParrot.addEnemyEncounter(mainBossEcounter1);
	bryansParrot.addItem(make_shared<Story>(bryansParrotNote));

	return allRooms;
}

vector<string> DungeonBuilder::getRoomNames()
{
	return roomNames;
}
