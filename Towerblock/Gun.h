#ifndef GUN_H
#define GUN_H

#include "Bullet.h"

class Gun
{
public:

	Gun()
	{
		_Cooldown = 0.f;
	};

	virtual std::vector<Bullet> Fire(int fpx, int fpy, float facing) = 0;

	float _Cooldown;
};

class Pistol : public Gun
{
public:

	Pistol()
	{
		_Cooldown = 0.2f;
	};

	std::vector<Bullet> Fire(int fpx, int fpy, float facing)
	{
		std::vector<Bullet> results;
		
		Bullet b1;
		b1._Position.Set(fpx, fpy);
		b1._Velocity = Vec(CalcXComp(facing), CalcYComp(facing)).UnitVec() * 100.f;
		results.push_back(b1);
		
		return results;
	};
};

class Shotgun : public Gun
{
public:

	Shotgun()
	{
		_Cooldown = 0.5f;
	};

	std::vector<Bullet> Fire(int fpx, int fpy, float facing)
	{
		std::vector<Bullet> results;

		Bullet temp;
		temp._Position.Set(fpx, fpy);
		temp._Velocity = Vec(CalcXComp(facing), CalcYComp(facing)).UnitVec() * 100.f;
		results.push_back(temp);

		float spread = DegreeToRad(45.f);

		temp._Velocity = Vec(CalcXComp(facing - spread), CalcYComp(facing - spread)).UnitVec() * 100.f;
		results.push_back(temp);

		temp._Velocity = Vec(CalcXComp(facing + spread), CalcYComp(facing + spread)).UnitVec() * 100.f;
		results.push_back(temp);
		
		temp._Velocity = Vec(CalcXComp(facing - (spread / 2.f)), CalcYComp(facing - (spread / 2.f))).UnitVec() * 100.f;
		results.push_back(temp);
		
		temp._Velocity = Vec(CalcXComp(facing + (spread / 2.f)), CalcYComp(facing + (spread / 2.f))).UnitVec() * 100.f;
		results.push_back(temp);

		return results;
	};
};

#endif