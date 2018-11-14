#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iostream>
#include "container.h"

using namespace std;

class Item {

public:

    friend class Container<Item>;

    inline Item(string name, double hp=1, double attack=1, double defense=1): name(name), hp(hp), attack(attack), defense(defense) {};

    // combine two item A and B:
    // return a new item: 
    //     name = A.name + " " + B.name
    //     hp = A.hp + B.hp
    //     attack = A.attack + " " + B.attack
    //     defense = A.defense + " " + B.defense
    inline Item operator+(const Item item) const {
        return Item(name + " " + item.name,
                    hp + item.hp,
                    attack + item.attack,
                    defense + item.defense);
    };

    inline string getName() const { return name; };

    inline double getHP() const { return hp; };

    inline double getAttack() const { return attack; };

    inline double getDefense() const { return defense; };

    inline void printDetails() const { cout<<name.c_str()<<" \n\t\tIncreases hp "<<hp<<", atk "<<attack<<", def "<<defense<<".\n"; };

private:

    const string name;      // the item's name

    const double hp;        // the amount of hp that a kun can increase when eaten

    const double attack;    // the amount of attack that a kun can increase when eaten

    const double defense;   // the amount of defense that a kun can increase when eaten
};

#endif /* ITEM_H */
