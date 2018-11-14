#include <iostream>
#include <string>
#include "move.h"
#include "kun.h"

using namespace std;

void void_move(Kun*, Kun*) {}

/*
* Default constructor of class Move.
*
*/
Move::Move(): name("void move"), lg(void_move) {}

/*
* Constructor of class Move.
*
* Add your code here!
*/
Move::Move(std::string move_name, Move_logic move_logic): name(move_name), lg(move_logic) {}

/*
* Copy constructor of class Move.
*
* Add your code here!
*/
Move::Move(const Move& m): name(m.name), lg(m.lg) {}


void Move::operator()(Kun* attacker, Kun* defender) {
    /*
    * Operator overloading for function call operator.
    *
    * This help compose the function object. Make use of the stored move_logic
    * on the attacker and defender.
    *
    * Add your code here!
    */
    lg(attacker, defender);
}

string Move::getName() {
    /*
    * Return the name of this move object by std::string.
    *
    * Getter for class Move.
    *
    * Add your code here!
    */
    return name;
}
