#include <iostream>
using namespace std;

class Player {
    public:
    string name;
    int health;
    int weapon;
    int armor;
    int level;
    int exp;
    std::vector<item> inventory;
};

class item {
    public:
    string name;
    int id;
    bool isweapon; // true if weapon, false if armor
};

class Enemy {
    public:
    string name;
    int health;
    int armorpoint;
    int dmg;
    int exp;
};