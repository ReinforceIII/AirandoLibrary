#include "PBS.h"
// class Planet==================================================================================
Planet::Planet(int number, int x, int y) : locationX(x), locationY(y), base_mineral(5), base_gas(3) {
	name += to_string(number);
}

pair<int, int> Planet::getResource() {
	pair<int, int> r = make_pair(base_mineral, base_gas);
	return r;
}

pair<int, int> Planet::getLocation() {
	pair<int, int> l = make_pair(locationX, locationY);
	return l;
}

void Planet::setHP(int damage, bool isDamage) {
	if (isDamage) hp -= damage;
	else hp += damage;
	if (hp < 0) hp = 0;
	else if (hp > PLANET_HEALTH) hp = PLANET_HEALTH;
}

// class Planet_list=============================================================================
Planet_list::Planet_list() {
	max_player = MAX_PLAYER;
	P_List = vector<Planet>();
	for (int i = 0; i < MAX_PLAYER; i++) {
		Planet temp(i, PLANET_X[i], PLANET_Y[i]);
		P_List.push_back(temp);
	}
	now_player = 0;
}

Planet_list::Planet_list(int num_of_player) {
	if (num_of_player > MAX_PLAYER) {
		cout << "Player maximum is " << MAX_PLAYER << " automatically set Player count " << MAX_PLAYER << '\n';
		num_of_player = MAX_PLAYER;
	}
	max_player = num_of_player;
	P_List = vector<Planet>();
	for (int i = 0; i < num_of_player; i++) {
		Planet temp(i, PLANET_X[i], PLANET_Y[i]);
		P_List.push_back(temp);
	}
	now_player = 0;
}

Planet& Planet_list::GivePlanetToPlayer() {
	Planet& p = P_List[now_player++];
	return p;
}

void Planet_list::Print() {
	int n = P_List.size();
	for (int i = 0; i < n; i++) {
		cout << P_List[i];
	}
}
// class Base====================================================================================

Base::Base(int _damage, int _detected_area, int _penalty_resource) {
	store_mineral = 0;
	store_gas = 0;
	store_missile = 0;
	produce_missile = 1;	
	damage = _damage;
	detect_area = _detected_area;
	penalty_resource = _penalty_resource;
}

void Base::Store(Planet P) {
	pair<int, int> resource = P.getResource();
	store_mineral += (resource.first - penalty_resource);
	store_gas += (resource.second - penalty_resource);
	store_missile += produce_missile;
}

void Base::UseMissile() {
	store_missile = 0;
}

pair<int, int> Base::GetResource() {
	pair<int, int> p = make_pair(store_mineral, store_gas);
	return p;
}

void Base::UseResource(pair<int, int> p) {
	store_mineral -= p.first;
	store_gas -= p.second;
}

// class Building&inheritance====================================================================
void RadarStation::BaseEffect(Base& b) {
	cout << "System Log: RadarStation construction Complete" << '\n';
	cout << "System Log: Base Detect Area Incresed by 10" << '\n';
	b.detect_area += 10;
}
bool RadarStation::checkResource(Base b) {
	pair<int, int> store = b.GetResource();
	return store.first >= req_mineral && store.second >= req_gas;
}
void HydrogenFactory::BaseEffect(Base& b) {
	cout << "System Log: HydrogenFactory construction Complete" << '\n';
	cout << "System Log: Base Damage Incresed by 3" << '\n';
	b.damage += 3;
}
bool HydrogenFactory::checkResource(Base b) {
	pair<int, int> store = b.GetResource();
	return store.first >= req_mineral && store.second >= req_gas;
}
// class Player==================================================================================
Player::Player(Planet_list& p, string name) : myPlanet(p.GivePlanetToPlayer()) {
	this->name = name;
	building_count = 0;
}

void Player::SetBase(int baseType) {
	if (baseType >= BASE_CATEGORY) {
		cout << "Unable baseType. baseType < " << BASE_CATEGORY << '\n';
		cout << "Automatically set BaseType 0\n";
	}
	myBase = Base(BASE_DAMAGE[baseType], BASE_AREA[baseType], BASE_PENALTY_RESOURCE[baseType]);
}

void Player::Ready() {
	myBase.Store(myPlanet);
}

void Player::Construction(string building_name) {
	if (building_count >= MAX_BUILDING) {
		cout << "Cannot Build Building. Already Maximum\n";
		return;
	}
	Building* B;
	if (building_name == "R") B = new RadarStation();
	else if (building_name == "H") B = new HydrogenFactory();
	else {
		cout << "Cannot Build Building. Can't access non-exist Building Name\n";
		return;
	}
	if (B->checkResource(myBase) == false) {
		cout << "Cannot Build Building. Not enough resource\n";
		return;
	}
	cout << name << " select Construction" << '\n';
	B->BaseEffect(myBase);
	building_count++;

	delete B;
}
int calculateDistance(int x1, int y1, int x2, int y2) {
	return abs(x2 - x1) + abs(y2 - y1);
}
Player Player::SetTarget(vector<Player*> p) {
	pair<int, int> myLocation = myPlanet.getLocation();
	auto temp = *p.begin();
	int mini = INT_MAX;
	for (auto iter = p.begin(); iter != p.end(); iter++) {
		pair<int, int> other = (*iter)->myPlanet.getLocation();
		if (myLocation.first == other.first && myLocation.second == other.second) continue;
		if (calculateDistance(myLocation.first, myLocation.second, other.first, other.second) <= myBase.detect_area) {
			if (calculateDistance(myLocation.first, myLocation.second, other.first, other.second) < mini) {
				temp = *iter;
			}
		}
	}
	return *temp;
}

void Player::giveDamage(Player& p) {
	int damage = myBase.damage;
	int missile = myBase.GetMissile();
	p.myPlanet.setHP(damage*missile, true);
}

void Player::Attack(vector<Player*> p) {
	Player target = SetTarget(p);
	giveDamage(target);
	myBase.UseMissile();
}


// Operator(cout) Overriding=====================================================================
ostream& operator<<(ostream& os, const Planet& P) {
	os << "    Planet info : ";
	os << P.name << " Location : [x: " << P.locationX << " y: " << P.locationY << "] ";
	os << "Planet HP: " << P.hp;
	return os;
}

ostream& operator<<(ostream& os, const Base& B) {
	os << "    Base Info: mineral: " << B.store_mineral << " gas: " << B.store_gas << " Missile: " << B.store_missile << '\n';
	os << "    Base Info: damage: " << B.damage << " area: " << B.detect_area << " penalty: " << B.penalty_resource << '\n';
	return os;
}

ostream& operator<<(ostream& os, const Player& P) {
	os << P.name << '\n';
	os << P.myPlanet << '\n';
	os << P.myBase;
	os << "BuilingCount: "<<P.building_count << '\n';
	os << '\n';
	return os;
}