#pragma once
#ifndef GAME_H
#define GAME_H

#include <string>
#include <map>
#include <vector>
#include <set>

#include "Item.h"
#include "Door.h"
#include "Player.h"
#include "Enemy.h"
#include "Room.h"

using namespace std;

/*
* --------------------------------------------------------------------------------------
* Class Scope
* --------------------------------------------------------------------------------------
* Game class that initalizes all objects in the game and handles all player interaction
*
* --------------------------------------------------------------------------------------
* Enums and Structures
* --------------------------------------------------------------------------------------
* GameState
*	current state of the game based around the player's status
*
* --------------------------------------------------------------------------------------
* Methods
* --------------------------------------------------------------------------------------
* initializeGame()
*	initializes all rooms for the game and all objects held within those rooms
* 
* playerWin()
*	handles logic for when the player wins - prompts for if the player wants to replay
*	the game or quit
* 
* playerDied()
*	handles logic for when the player dies - prompts for if the player wants to replay
*	the game or quit
* 
* promptReplay()
*	prompts the player if they want to replay the game or quit
* 
* encounterInteract(InteractionResult inputResult)
*	handles all interactions when the player is in an enemy encounter
* 
* openDoor(DoorIndex index)
*	handles the logic for opening the door of the current room specified by index
* 
* getDoorIndex(string doorName)
*	returns the index of the door specified by doorName, if doesn't exist returns
*	DoorIndex::NONE
* 
* helperDisplay()
*	displays helper text for all discovered commands within the actionsUsed vector
* 
* gameInteract()
*	handles all player interaction with the room and all player input
* 
* start()
*	starts the game and handles the game loop
* 
* --------------------------------------------------------------------------------------
* Variables
* --------------------------------------------------------------------------------------
* actionsUsed
*	list of all actions the player has already used and discovered
* 
* gameState
*	the current state of the game
* 
* player
*	the player object for the current game
* 
* allRooms
*	the list of all the rooms within the game
* 
* currentRoom
*	the currentRoom that the player is in
* 
* winRoom
*	the room that once reached signals that the player has won the gamme
* --------------------------------------------------------------------------------------
*/

class Game
{
private:


	enum class GameState
	{
		PLAY,	// Keep Playing
		WIN,	// Player won
		DIED	// Player died
	};

	set<string> actionsUsed;
	GameState gameState;
	Player player;

	vector<Room> allRooms;

	Room* currentRoom;
	Room* winRoom;

	void initializeGame();
	void playerDied();
	void playerWin();
	void promptReplay();
	void encounterInteract(Interaction::InteractionResult& inputResult);
	void enterNewRoom(Room* nextRoom);
	void openDoor(Room::DoorIndex index);
	Room::DoorIndex getDoorIndex(string doorName);

	static const map<string, int> roomNameToIndex;

	bool isDevMode = false;

public:
	void helperDisplay();
	void gameInteract();

public:
	// Unit Test methods
	void initializeGameTest();
	void start();
};

#endif // GAME_H

