#include "kun.h"
#include <algorithm>

Kun::Kun(): name("KUN"), hp(10), attack(1), defense(1), level(1), experience(0), MAX_LEVEL(100) {

}

Kun::Kun(string name): name(name), hp(10), attack(1), defense(1), level(1), experience(0), MAX_LEVEL(100) {

}

Kun::Kun(const Kun& another): MAX_LEVEL(another.MAX_LEVEL) {
    name = another.name;
    level = another.level;
    hp = another.hp;
    attack = another.attack;
    defense = another.defense;
    experience = another.experience;
    for (vector<Move*>::const_iterator it = another.moveList.cbegin(); it != another.moveList.cend(); ++it) {
        moveList.push_back(new Move(**it));
    }
}

string Kun::getName() const {
    return name;
}

void Kun::setName(string name) {
    this->name = name;
}

int Kun::getLevel() const {
    return level;
}

bool Kun::increaseLevelTo(int level) {
    if (level > MAX_LEVEL) level = MAX_LEVEL;
    int levelDiff = level - this->level;
    if (levelDiff <= 0) return false;
    this->level = level;
    hp += 10*levelDiff;
    attack += 2*levelDiff;
    defense += 2*levelDiff;
    experience = 0;
    if (level == MAX_LEVEL) return false;
    else return true;
}

double Kun::getHP() const {
    return hp;
}

bool Kun::isAlive() const {
    return (hp > 0);
}

void Kun::setHP(double hp) {
    if (hp < 0) hp = 0;
    this->hp = hp;
}

void Kun::heal() {
    hp = level*10;
}

double Kun::getAttack() const {
    return attack;
}

void Kun::setAttack(double attack) {
    this->attack = attack;
}

double Kun::getDefense() const {
    return defense;
}

void Kun::setDefense(double defense) {
    this->defense = defense;
}

double Kun::getExperience() const {
    return experience;
}

bool Kun::gainExperience(double experience) {
    if (level >= MAX_LEVEL) return false;
    double reduntantExp = this->experience + experience - 100*level;
    if (reduntantExp >= 0) {
        if (increaseLevelTo(level + 1)) {
            gainExperience(reduntantExp);
        }
    } else {
        this->experience += experience;
    }
    return true;
}

Move* Kun::getMove(int index) const {
    /*
    * Get a move from moveList by index (index % moveList.size() preventing
    * index out of bound).
    *
    * Return pointer to the move for the given index, or NULL if no move exists
    * in the moveList.
    *
    * Add your code here!
    */

    return moveList[index % moveList.size()];
}

void Kun::addMove(Move* move) {
    /*
    * Add a move into the moveList.
    *
    * Remember to check the duplication to avoid add the same move object twice.
    *
    * Return void.
    *
    * Use std::vector begin(), end(). Use iterator of vector.
    *
    * Add your code here!
    */
    if (find(moveList.begin(), moveList.end(), move) == moveList.end())
      moveList.push_back(move);
}

void Kun::removeAllMoves() {
    /*
    * Remove all the moves in the moveList.
    *
    * Iterate throught the moveList to free the memory of each Move object.
    *
    * Return void.
    *
    * Use std::vector begin(), end() and clear(). Use iterator of vector.
    *
    * Add your code here!
    */
    for (vector<Move*>::iterator i = moveList.begin(); i != moveList.end(); i++)
    {
      delete *i;
    }
    moveList.clear();
}

void Kun::eatItem(const Item* item) {
    /*
    * Add the item's hp, attack and defense onto kun but do not delete the item.
    *
    * Return void.
    *
    * Add your code here!
    */
    hp += item->getHP();
    attack += item->getAttack();
    defense += item->getDefense();
}

void Kun::eatKun(const Kun* kun) {
    /*
    * Add the kun's stats onto self's stats with a factor 0.1 and gain
    * Exp by kun->level * 30..
    *
    * Do not delete the kun.
    *
    * myHP += kun's HP * 0,1
    * myATK += kun's ATK * 0.1
    * myDEF += kun's DEF * 0.1
    * myEXP += kun's LEVEL * 30
    *
    * Return void.
    *
    * Add your code here!
    */
    hp += kun->hp * 0.1;
    attack += kun->attack * 0.1;
    defense += kun->defense + 0.1;
    gainExperience(kun->level * 30);
}

Kun& Kun::operator=(const Kun kun) {
    /*
    * Operator overloading for assignment operator.
    *
    * copy the input kun parameters similar to the copy constructor.
    *
    * Return reference to self.
    *
    * Add your code here!
    */
    if (this == &kun) return *this;
    name = kun.name;
    hp = kun.hp;
    attack = kun.attack;
    defense = kun.defense;
    level = kun.level;
    experience = kun.experience;
    moveList = kun.moveList;
    return *this;
}

Kun& Kun::operator<<(Kun* kun) {
    /*
    * Operator overloading for the left shift operator.
    *
    * eatKun by the left shift operator.
    *
    * Return reference to self.
    *
    * Add your code here!
    */
    eatKun(kun);
    return *this;
}

Kun& Kun::operator<<(Item* item) {
    /*
    * Operator overloading for the left shift operator.
    *
    * eatItem by the left shift operator.
    *
    * Return reference to self.
    *
    * Add your code here!
    */
    eatItem(item);
    return *this;
}

Kun* Kun::operator+(const Kun kun) const {
    /*
    * Operator overloading for the add operator.
    *
    * create new baby. Need memory allocation through 'new', because the newly born kun need to be added into KunGroup (Container) and it requires dynamic memory.
    * hp: 10% of sum of its parents' hp
    * attack: 10% of sum of its parents' attack
    * defense: 10% of sum of its parents' defense
    * movelist:
    *     kun_A + kun_B => kun_baby
    *     kun_baby's movelist is (kun_A.movelist + kun_B.movelist)
    *     order of movelist is important because in arena the move is used in order.
    *
    * Return pointer pointing to the baby.
    *
    * Use std::vector insert(), begin() and end().
    *
    * Add your code here!
    */
    Kun* baby_kun = new Kun(name + " " + kun.name);
    baby_kun->hp = (hp + kun.hp) / 10;
    baby_kun->attack = (attack + kun.attack) / 10;
    baby_kun->defense = (defense + kun.defense) / 10;
    vector<Move*> baby_moveList = moveList;
    baby_moveList.insert(baby_moveList.end(), kun.moveList.begin(), kun.moveList.end());
    baby_kun->moveList = baby_moveList;
    return baby_kun;
}

Kun::~Kun() {
    /*
    * Destructor for Kun.
    *
    * Free the memory allocated in the Kun (in moveList).
    *
    * Use std::vector interator, begin(), end() and clear().
    *
    * Add your code here!
    */
    for (vector<Move*>::iterator i = moveList.begin(); i != moveList.end(); i++)
    {
      delete *i;
    }
    moveList.clear();
}
