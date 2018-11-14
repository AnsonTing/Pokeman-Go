#ifndef ARENA_H
#define ARENA_H

#include <ctime>
#include "trainer.h"

//      There are four types of combat results for kun-battles.
//
//      ATTACKER_WINS: Defender dies.
//      DEFENDER_WINS: Attacker dies.
//      ENDLESS: The number of battle rounds exceeds MAX_NUM_OF_ROUNDS. Maybe both sides uses heal all the time.
//      DIETOGETHER: Both sides die at the same round.

enum CombatResult { ATTACKER_WINS, DEFENDER_WINS, ENDLESS, DIETOGETHER };

class Arena {

public:

// default constructor, both MAX_BATTLE_TIME and MAX_NUM_OF_ROUNDS should be 1000
    Arena();
    
//  To know how battles work, you should know what battle rounds are.
//
//  Battle Rounds:
//
//  A battle consists of multiple rounds. For each round, Two kuns deal damage at the same time.
//
//  The workflow is:
//      a. Calculate the kun's move based on its movelist and the current round's index. If no moves specified, use WATER_SPRAY.
//
//          currentMove = movelist[currentRound % moveCount]
//
//      b. Calculate attack and defense values for both sides based on their selected move,
//      then calculate damage value for both sides, and heal value for both sides.
//
//      The calculated attack and defense values should only affect the current round.
//
//      NOTE: A kun will not deal damage if it uses heal that round.
//
//      Damage formula:
//          my_damage = my_attack - his_defense // if smaller than 1, make it 1
//          his_damage = his_attack - my_defense // if smaller than 1, make it 1
//
//          my_heal = 0 // or 5 if my_move is AQUA_RING
//          his_heal = 0 // or 5 if his_move is AQUA_RING
//
//          my_hp = my_hp - his_damage + my_heal
//          his_hp = his_hp - my_damage + his_heal
//
//      c. Set new hp based on the calculated damage and heal.
//
//      d. Return a CombatResult if any side is dead.

    CombatResult battle(Kun* attacker, Kun* defender);

//  Once you finished battle between two kuns, trainer battles will be easy.
//
//  The battle between trainers will always have a winner. If something endless occured,
//  or two sides have their Kuns all died at the same time, the attacker wins the battle.
//
//  There is a time limit of 1000ms for trainer battles (MAX_BATTLE_TIME). If the battle exceeds 1000ms,
//  the attacker wins the battle. You may read http://www.cplusplus.com/reference/ctime/clock/ for more details on calculating time.
//
//  Workflow for trainer battles:
//
//      1. Attacker and defender use their first alive kun to do the kun battle, and wait for the CombatResult.
//
//      2. Based on the result, 0, 1, or 2 sides have to pick their following alive kun to do the combat.
//      Continue using the kun's stats in the following battles.
//      This means that if a kun's HP drops to 5 and wins the battle,
//      it should battle the opponent's following kun with a starting HP of 5.
//
//      3. Do the same procedure until a side has no alive kun. The other side becomes winner.
//      Simply return the winner (DO NOT do a copy).

    Trainer* battle(Trainer* attacker, Trainer* defender);

private:

    const int MAX_BATTLE_TIME;    // max 1000 ms for battle between trainers
    const int MAX_NUM_OF_ROUNDS;  // max 1000 rounds for battle between kuns
};

#endif /* ARENA_H */
