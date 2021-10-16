#pragma once
#ifndef DAMAGEABLE_H
#define DAMAGEABLE_H

#include "Health.h"

class Damageable
{
protected:
	Health health;

public:
	inline virtual void damage(int amt) { health.removeHealth(amt); }
	inline virtual void heal(int amt) { health.addHealth(amt); }
	inline bool isDead() { return health.getCurrentHealth() == 0; }
};

#endif // DAMAGEABLE_H