#pragma once
#ifndef HEALTH_H
#define HEALTH_H

/*
* --------------------------------------------------------------------------------------
* Class Scope
* --------------------------------------------------------------------------------------
* Health class to handle health points for all characters in the game. Can be damaged
* or healed and also contains a maximum limit to the amount of health points that can
* be held
*
* --------------------------------------------------------------------------------------
* Methods
* --------------------------------------------------------------------------------------
* removeHealth(int amt)
*	decreases currentHealth by amt, clamps currentHealth to not fall below 0
* 
* addHealth(int amt)
*	increases currentHealth by amt, clamps currentHealth to not exceed maxHealth
*
* --------------------------------------------------------------------------------------
* Variables
* --------------------------------------------------------------------------------------
* maxHealth
*	the upper limit to what currentHealth can be
* 
* currentHealth
*	the current amount of health points held within this health
* --------------------------------------------------------------------------------------
*/
class Health
{
private:
	int maxHealth;
	int currentHealth;

public:
	Health();
	Health(int max);

	int getCurrentHealth() const;
	int getMaxHealth() const;

	void removeHealth(int amt);
	void addHealth(int amt);
};

#endif // HEALTH_H