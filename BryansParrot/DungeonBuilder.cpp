#include "DungeonBuilder.h"

/// HOW TO CREATE NEW ROOM:
///		-Add Room() to the allRooms array
///		- create the new room object linking it to the index of the room you added in addRooms
///			Room& [ROOMNAME] = allRooms[INDEX]
/// 
///	ADDING A DOOR TO A ROOM:
///		-shared_ptr<Door>DOOR_NAME(new Door(NEXT ROOM, LOCKS AMOUNT)); 
///			DOOR_NAME: firstNorthDoor
///			NEXT_ROOM: secondRoom
///			LOCKS: INT <-If no locks then only have Next Room in ( )
/// 
///		-ROOM_OBJ.setDoor(Room::DoorIndex::[CARDNAL_DIRECTION_DOOR, DOOR_NAME_FORM_ABOVE);
/// 
/// ADDING ITEMS TO A ROOM:
///		-create object for item
///			Potion sPotion
///		-add item to specific room
///			ROOM_OBJ.addItem(make_shared<ITEM_CLASS>(OBJ_NAME))
///				- ITEM_CLASS: Potion
///				- OBJ_NAME: sPotion
/// 
/// CREATE NEW WEAPON
///		- create weapon object
///			Weapon [WEAPON_NAME]("[NAME]", baseDamage{min, max}, critChance, critDamage{min, max})
/// 
/// CREATE NEW ENEMY
///		- create enemy object
///			Enemy [ENEMY_NAME]("[NAME]", maxHealth, weapon)
/// 
/// CREATING AN ENEMYY ENCOUNTER
///		- create enemy encounter object
///			EnemyEncounter [ROOM_NAME]Encounter[ENCOUNTER_NUMBER]
///				ex) controlRoomEncounter1
///		- add enemies to the encounter
///			encounter.addEnemy([ENEMY_NAME])
///		- add encounter to the room
///			controlRoom.addEnemyEncounter(controlRoomEncounter1)
/// 
/// ** WHEN ADDING ROOM, ALWAYS UPDATE THE WINROOM OBJ IF NESSESARY **
vector<Room> DungeonBuilder::buildDungeon()
{
	// Name - Light: Min/Max/Acceracy -Heavy: Min/Max/Acceracy, critchance, critMulti
	Weapon goblinFists("Goblin Fists", { 5, 10, 0.9f }, { 12, 18, 0.6f }, 0.1f, 1.5f);
	Weapon sword("Sword", { 20, 30, 0.95f }, { 35, 50, 0.7f }, 0.25f, 1.65f);

	Enemy goblin("Goblin", 100, goblinFists);
	Enemy mini1("Mini Boss West", 100, goblinFists);
	Enemy mini2("Mini Boss East", 100, goblinFists);
	Enemy mini3("Mini Boss North", 100, goblinFists);
	Enemy boss("Boss", 100, goblinFists);

	vector<Room> allRooms = {
		Room(),
		Room(),
		Room(),
		Room(),
		Room(),
		Room(),
		Room(),
		Room(),
		Room(),
		Room()
	};

	//Create room object that will set it to array of all all rooms
	Room& firstRoom = allRooms[0];
	Room& secondRoom = allRooms[1];
	Room& thirdRoom = allRooms[2];
	Room& forthRoom = allRooms[3];
	Room& miniBossWestRoom = allRooms[4];
	Room& miniBossEastRoom = allRooms[5];
	Room& miniBossNorthRoom = allRooms[6];
	Room& mainBossRoom = allRooms[7];
	Room& fithRoom = allRooms[9];


	//create new doors that will be added to doors vector
	//Room1				door name		connecting room
	shared_ptr<Door> firstNorthDoor(new Door(secondRoom));
	//Room2
	shared_ptr<Door> secondNorthDoor(new Door(thirdRoom, 2));
	shared_ptr<Door> secondSouthDoor(new Door(firstRoom));
	//Room3
	shared_ptr<Door> thirdNorthDoor(new Door(forthRoom)); 
	shared_ptr<Door> thirdSouthDoor(new Door(secondRoom));
	//Room4
	shared_ptr<Door> forthWestDoor(new Door(miniBossWestRoom));
	shared_ptr<Door> forthEastDoor(new Door(miniBossEastRoom));
	shared_ptr<Door> forthNorthDoor(new Door(miniBossNorthRoom));
	shared_ptr<Door> forthSouthDoor(new Door(thirdRoom));
	//West Mini Boss 1
	shared_ptr<Door> miniWest_EasthDoor(new Door(forthRoom));
	//East Mini Boss 2
	shared_ptr<Door> miniEast_WestDoor(new Door(forthRoom)); 
	//North Mini Boss 3
	shared_ptr<Door> miniNorth_NorthDoor(new Door(mainBossRoom, 3)); 
	shared_ptr<Door> miniNorth_SouthDoor(new Door(forthRoom)); 
	//Boss 
	shared_ptr<Door> bossNorthDoor(new Door(fithRoom,1)); 
	shared_ptr<Door> bossSouthDoor(new Door(miniBossNorthRoom));
	//Fith Room
	shared_ptr<Door> fithSouthDoor(new Door(mainBossRoom)); 


	//create new items that will be added to Inventory
	Potion sPotion("Small Potion", 25);
	Potion mPotion("Medium Potion", 50);
	Potion lPotion("Large Potion", 100);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// Encounters
	//Second Room Encounter: Initialization
	EnemyEncounter secondRoomEncounter1;
	secondRoomEncounter1.addEnemy(goblin);
	secondRoomEncounter1.addDrop(shared_ptr<Item>(new Key(secondNorthDoor))); //Add drops to specific Enemy Object 

	//Mini 1 Room Encounter: INitialization
	EnemyEncounter miniBossWestEncounter2;
	miniBossWestEncounter2.addEnemy(mini1);
	miniBossWestEncounter2.addDrop(shared_ptr<Item>(new Key(miniNorth_NorthDoor)));

	//Mini 2 Room Encounter: INitialization
	EnemyEncounter miniBossEastEncounter3;
	miniBossEastEncounter3.addEnemy(mini2);
	miniBossEastEncounter3.addDrop(shared_ptr<Item>(new Key(miniNorth_NorthDoor)));

	//Mini 3 Room Encounter: INitialization
	EnemyEncounter miniBossNorthEncounter4;
	miniBossNorthEncounter4.addEnemy(mini3);
	miniBossNorthEncounter4.addDrop(shared_ptr<Item>(new Key(miniNorth_NorthDoor)));

	//Mini Room Encounter: Initialization
	EnemyEncounter BossNorthEncounter5;
	BossNorthEncounter5.addEnemy(boss);
	BossNorthEncounter5.addDrop(shared_ptr<Item>(new Key(bossNorthDoor)));
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Room 1: Initialization
	firstRoom.setDoor(Room::DoorIndex::NORTH_DOOR, firstNorthDoor);
	firstRoom.addItem(shared_ptr<Item>(new Key(secondNorthDoor)));
	firstRoom.addItem(make_shared<Weapon>(sword));

	//Room 2: Initialization
	secondRoom.setDoor(Room::DoorIndex::NORTH_DOOR, secondNorthDoor);
	secondRoom.setDoor(Room::DoorIndex::SOUTH_DOOR, secondSouthDoor);
	secondRoom.addEnemyEncounter(secondRoomEncounter1);

	//Room3: Initialization
	thirdRoom.setDoor(Room::DoorIndex::NORTH_DOOR, thirdNorthDoor);
	thirdRoom.setDoor(Room::DoorIndex::SOUTH_DOOR, thirdSouthDoor);
	thirdRoom.addItem(make_shared<Potion>(sPotion)); // make_shared: makes smart prt with contents of sPotion

	//Room4: Initialization
	forthRoom.setDoor(Room::DoorIndex::NORTH_DOOR, forthNorthDoor);
	forthRoom.setDoor(Room::DoorIndex::SOUTH_DOOR, forthSouthDoor);
	forthRoom.setDoor(Room::DoorIndex::EAST_DOOR, forthEastDoor);
	forthRoom.setDoor(Room::DoorIndex::WEST_DOOR, forthWestDoor);
	forthRoom.addItem(make_shared<Potion>(lPotion)); // make_shared: makes smart prt with contents of sPotion

	//Mini West: Initialization
	miniBossWestRoom.setDoor(Room::DoorIndex::EAST_DOOR, miniWest_EasthDoor);
	//miniBossWestRoom.addItem(shared_ptr<Item>(new Key(miniNorth_NorthDoor)));
	miniBossWestRoom.addEnemyEncounter(miniBossWestEncounter2);

	//Mini East: Initialization
	miniBossEastRoom.setDoor(Room::DoorIndex::WEST_DOOR, miniEast_WestDoor);
	//miniBossEastRoom.addItem(shared_ptr<Item>(new Key(miniNorth_NorthDoor)));
	miniBossEastRoom.addEnemyEncounter(miniBossEastEncounter3);

	//Mini North: Initialization
	miniBossNorthRoom.setDoor(Room::DoorIndex::NORTH_DOOR, miniNorth_NorthDoor);
	miniBossNorthRoom.setDoor(Room::DoorIndex::SOUTH_DOOR, miniNorth_SouthDoor);
	//miniBossNorthRoom.addItem(shared_ptr<Item>(new Key(miniNorth_NorthDoor)));
	miniBossNorthRoom.addEnemyEncounter(miniBossNorthEncounter4);

	//Boss: Initialization
	mainBossRoom.setDoor(Room::DoorIndex::NORTH_DOOR, bossNorthDoor);
	mainBossRoom.setDoor(Room::DoorIndex::SOUTH_DOOR, bossSouthDoor);
	mainBossRoom.addEnemyEncounter(BossNorthEncounter5);

	//FithRoom: Initialization
	fithRoom.setDoor(Room::DoorIndex::SOUTH_DOOR, fithSouthDoor);

	return allRooms;
}
