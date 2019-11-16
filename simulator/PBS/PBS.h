#pragma once

#include <vector>
#include <string>
#include <iostream>

constexpr int MAX_PLAYER = 8;
constexpr int MAX_BUILDING = 8;
constexpr int PLANET_HEALTH = 100;
constexpr int BASE_CATEGORY = 3;
using namespace std;

const vector<int> PLANET_X = { 0,5,10,5,0,-5,-10,-5 };
const vector<int> PLANET_Y = { 0,0,0,5,5,-5,-5,10 };
const int BASE_DAMAGE[BASE_CATEGORY] = { 1,3,3 };
const int BASE_AREA[BASE_CATEGORY] = { 10,10,5 };
const int BASE_PENALTY_RESOURCE[BASE_CATEGORY] = { 0,1,0 };

class Planet {
private:
	int hp = PLANET_HEALTH;
	string name = "Planet ";
	const int locationX;
	const int locationY;
	const int base_mineral;
	const int base_gas;
public:
	Planet(int number, int x, int y);
	pair<int, int> getResource();
	pair<int, int> getLocation();
	void setHP(int damage, bool isDamage);
	friend ostream& operator<<(ostream& os, const Planet& P);
};

class Planet_list {
private:
	vector<Planet> P_List;
	int max_player;
	int now_player;
public:
	Planet_list();
	Planet_list(int num_of_player);
	Planet& GivePlanetToPlayer();
	void Print();
};

class Base {
private:
	int store_mineral;
	int store_gas;
	int store_missile;
public:
	int damage;
	int produce_missile;
	int detect_area;
	int penalty_resource;
	Base() {};
	Base(int _damage, int _detected_area, int _penalty_resource);
	void Store(Planet P);
	pair<int, int> GetResource();
	int GetMissile() { return store_missile; };
	void UseResource(pair<int, int> r);
	void UseMissile();
	friend ostream& operator<<(ostream& os, const Base& B);
};

class Building {
public:
	virtual ~Building() {};
	virtual void BaseEffect(Base& b) = 0;
	virtual bool checkResource(Base b) = 0;
};

class RadarStation : public Building {
private:
	int req_mineral = 10;
	int req_gas = 0;
public:
	RadarStation() {};
	~RadarStation() {};
	void BaseEffect(Base& b);
	bool checkResource(Base b);
};

class HydrogenFactory : public Building {
private:
	int req_mineral = 5;
	int req_gas = 5;
public:
	HydrogenFactory() {};
	~HydrogenFactory() {};
	void BaseEffect(Base& b);
	bool checkResource(Base b);
};

class Player {
private:
	string name;
	Planet& myPlanet;
	Base myBase;
	int building_count;
	Player SetTarget(vector<Player*> p);
	void giveDamage(Player& p);
public:
	Player(Planet_list& p, string name);
	~Player() {};
	void SetBase(int baseType);
	void Ready();
	void Construction(string building_name);
	void Attack(vector<Player*> p);
	friend ostream& operator<<(ostream& os, const Player& P);
};
