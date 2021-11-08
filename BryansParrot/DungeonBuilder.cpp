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
	Weapon goblinFists("Goblin Fists", 0.1f, 1.5f);
	goblinFists.addAttackMove(AttackMove("Punch", 5, 10, 1, 0.9f));

	Weapon sword("Sword", 0.25f, 1.65f);
	sword.addAttackMove(AttackMove("Stab", 20, 30, 1, 0.95f));
	sword.addAttackMove(AttackMove("Slash", 35, 50, 3, 0.75f));
	sword.speedBoost = 2;
	sword.staminaBoost = 2;

	Enemy goblin("Goblin", 100, 5, 2, goblinFists);

	vector<Room> allRooms = {
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

	//create new doors that will be added to doors vector
	shared_ptr<Door> firstNorthDoor(new Door(secondRoom));
	shared_ptr<Door> secondNorthDoor(new Door(thirdRoom, 2));
	shared_ptr<Door> secondSouthDoor(new Door(firstRoom));
	shared_ptr<Door> thirdNorthDoor(new Door(forthRoom));
	shared_ptr<Door> thirdSouthDoor(new Door(secondRoom));

	//create new items that will be added to Inventory
	Potion sPotion("Small Potion", 25);
	Potion mPotion("Medium Potion", 50);
	Potion lPotion("Large Potion", 100);

	EnemyEncounter secondRoomEncounter1;
	secondRoomEncounter1.addEnemy(goblin);

	//Add drops to specific Enemy Object 
	secondRoomEncounter1.addDrop(shared_ptr<Item>(new Key(secondNorthDoor)));

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

	return allRooms;
}
