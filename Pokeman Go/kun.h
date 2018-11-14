#ifndef KUN_H
#define KUN_H

#include <string>
#include <iostream>
#include "item.h"
#include "container.h"
#include "move.h"

class Move;

class Kun
{

  public:
    friend class Container<Kun>;

    Kun();                         // default constructor
    Kun(string name);              // conversion constructor
    Kun(const Kun &another);       // copy constructor
    Kun &operator=(const Kun kun); // assign constructor

    // assimilate partial power (0.1 hp, 0.1 attact, 0.1 defense) of another kun, and gain 30*<level_of_anothr_kun> experience
    Kun &operator<<(Kun *kun);
    // kun eat item
    // this overloaded operator is used by the trainer as trainer manage his/her own kun and item.
    // It is used in the function (trainer.cpp)
    //    void Trainer::feedItemToKun(Item* item, Kun* kun)
    Kun &operator<<(Item *item);
    // create new baby. Need memory allocation through 'new', because the newly born kun need to be added into KunGroup (Container) and it requires dynamic memory.
    // hp: 10% of sum of its parents' hp
    // attack: 10% of sum of its parents' attack
    // defense: 10% of sum of its parents' defense
    // movelist: 
    //     kun_A + kun_B => kun_baby
    //     kun_baby's movelist is (kun_A.movelist + kun_B.movelist)
    //     order of movelist is important because in arena the move is used in order. 
    //     No need to care about the replication.
    Kun* operator+(const Kun kun) const; 

    string getName() const;
    void setName(string name); // methods for getting & setting name

    double getHP() const;
    void setHP(double hp); // methods for getting & setting HP

    bool isAlive() const; // if hp > 0, return true
    void heal();          // set hp to be level * 10

    double getAttack() const;
    void setAttack(double attack); // methods for getting & setting attack

    double getDefense() const;
    void setDefense(double defense); // methods for getting & setting defense

    /*
     *  return level
     */
    int getLevel() const;
    /*
     *  set a new value to level
     *  if level > MAX_LEVEL, do nothing
     *  if level <= current level, do nothing
     *  otherwise, for each level increased, increase HP by 10, attack by 2, and defense by 2
     *  then set experience to 0
     */
    bool increaseLevelTo(int level);

    /*
     *  return experience
     */
    double getExperience() const;

    /*
     *  increase current experience by the new value
     *  if totalExp exceeds level*100, kun should level up
     *  you may use recursion
     *
     *  Example:
     *  initial -> level 1, Exp 0
     *  gainExp(350)
     *  final -> level 3, Exp 50
     */
    bool gainExperience(double experience);

    /*
     *  return move for the given index
     */
    Move* getMove(int index) const;

    /*
     *  add a move to the current moveList
     *  remember to update moveCount
     */
    void addMove(Move* move);

    /*
     *  remove all moves
     *  deallocate memory, and set moveList to NULL
     */
    void removeAllMoves();

    /*
     *  add the item's stats directy onto kun's stats
     *  do not delete the item
     */
    void eatItem(const Item *item);

    /*
     *  add the kun's stats onto self's stats
     *  do not delete the kun
     *  myHP += kun's HP * 0,1
     *  myATK += kun's ATK * 0.1
     *  myDEF += kun's DEF * 0.1
     *  myEXP += kun's LEVEL * 30
     */
    void eatKun(const Kun *kun);

    /*
     *  helper function to print kun's details
     */
    inline void printDetails() const
    {
        std::cout << "\"" << name.c_str() << "\": \n\t\tLevel " << level << " Exp " << experience << ", hp " << hp << ", atk " << attack << ", def " << defense << std::endl;
        std::cout << "\t\tmoveList:"<< std::endl;
        for (vector<Move*>::const_iterator it = moveList.cbegin(); it != moveList.cend(); ++it) {
            std::cout<<"\t\t\t"<<(*it)->getName()<<std::endl;
        }
        
    };

    ~Kun();

  private:
    std::string name; // kun's name

    double hp;      // kun's hp
    double attack;  // kun's attack
    double defense; // kun's defense

    int level;         // kun's level
    double experience; // kun's experience

    const int MAX_LEVEL; // the max level that the kun can reach

    std::vector<Move*> moveList; // kun's moveList
};

#endif /* KUN_H */
