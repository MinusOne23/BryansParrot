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

int Health::getCurrentHealth()
{
	return currentHealth;
}

int Health::getMaxHealth()
{
	return maxHealth;
}

void Health::removeHealth(int amt)
{
	currentHealth -= amt;
}

void Health::addHealth(int amt)
{
	currentHealth += amt;
}
