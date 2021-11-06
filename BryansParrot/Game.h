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

/// GAME CLASS
/// -DEFINES ACTION ENUMS
/// -Used to interact with all rooms
/// -Game loops untill player dies or enters the winning room
/// 
/// INITIALIZE_GAME: Creates all rooms filled with items and enemies
/// ENUM_INPUT_CHECKER: Converst uiser input into an action
/// PLAYER_DIED: PLayer health reaches 0 - ends game
/// PLAYER_WIN: PLayer enters winning room - ends game
/// PROMPT_REPLAY: Game is over and asks to play game again
/// OPEN_DOOR: Player enters new room
/// START: Starts game and checks untill PLayer dies or player wins
/// GAME_INTERACT: Game loops and performs actions

class Game
{
private:

	set<string> actionsUsed;

	enum class GameState
	{
		PLAY,
		WIN,
		DIED
	};

	static const int MAX_ACTION_WORDS;

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

	static const map<string, int> roomString_to_roomIndex;

	bool isDevMode = false;

public:
	void helperDisplay();
	void start();
	void gameInteract();
};

#endif // GAME_H

