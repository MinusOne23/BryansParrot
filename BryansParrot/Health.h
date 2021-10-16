#pragma once
#ifndef HEALTH_H
#define HEALTH_H

class Health
{
private:
	int maxHealth;
	int currentHealth;

public:
	Health();
	Health(int max);

	int getCurrentHealth();
	int getMaxHealth();

	void removeHealth(int amt);
	void addHealth(int amt);
};

#endif // HEALTH_H