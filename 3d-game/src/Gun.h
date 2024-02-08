#pragma once

struct Gun
{
	Gun()
		: timer(0.0f), cooldownTime(0.0f), reloadTime(0.0f), maxAmmunition(1), ammunition(1)
	{}
	Gun(float _cooldownTime, float _reloadTime, unsigned int _maxAmmunition)
		: timer(0.0f), cooldownTime(_cooldownTime), reloadTime(_reloadTime), maxAmmunition(_maxAmmunition), ammunition(_maxAmmunition)
	{}

	float timer;

	float cooldownTime;
	float reloadTime;

	unsigned int maxAmmunition;
	unsigned int ammunition;

	bool canFire()
	{
		return ammunition > 0 && timer <= 0.0f;
	}
	void onFire()
	{
		timer = cooldownTime;
		ammunition--;
	}
	void onReload()
	{
		timer = reloadTime;
		ammunition = maxAmmunition;
	}
};