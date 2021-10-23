#include "Health.h"

Health::Health()
{
	maxHealth = 100;
	currentHealth = 100;
}

Health::Health(int max)
{
	maxHealth = max;
	currentHealth = max;
}

int Health::getCurrentHealth() const
{
	return currentHealth;
}

int Health::getMaxHealth() const
{
	return maxHealth;
}

void Health::removeHealth(int amt)
{
	currentHealth -= amt;
	
	if (currentHealth < 0)
		currentHealth = 0;
}

void Health::addHealth(int amt)
{
	currentHealth += amt;
	if (currentHealth > maxHealth)
	{
		currentHealth = maxHealth;
	}
}
