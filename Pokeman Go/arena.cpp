#include "arena.h"

Arena::Arena(): MAX_BATTLE_TIME(1000), MAX_NUM_OF_ROUNDS(1000) {}

Trainer* Arena::battle(Trainer* attacker, Trainer* defender) {

    KunGroup::iterator atit = attacker->getKunGroup().begin();
    KunGroup::iterator deit = defender->getKunGroup().begin();
    if (deit == defender->getKunGroup().end()) return attacker;
    if (atit == attacker->getKunGroup().end()) return defender;

    const clock_t begin_time = clock();
    while (clock() - begin_time < MAX_BATTLE_TIME) {
        switch (battle(*atit, *deit)) {
            case ATTACKER_WINS:
                ++deit;
                break;
            case DEFENDER_WINS:
                ++atit;
                break;
            case DIETOGETHER:
                ++atit;
                ++deit;
                break;
            case ENDLESS:
                break;
        }
        if (deit == defender->getKunGroup().end()) return attacker;
        if (atit == attacker->getKunGroup().end()) return defender;
    }
    return attacker;
}

CombatResult Arena::battle(Kun* attacker, Kun* defender) {
    for (int i=0;i<MAX_NUM_OF_ROUNDS;i++) {
        Move* atMove = attacker->getMove(i);
        Move* deMove = defender->getMove(i);

        if (atMove) (*atMove)(attacker, defender);
        //        else water_spray(attacker, defender);
        if (deMove) (*deMove)(defender, attacker);
        //        else water_spray(defender, attacker);

        if (!attacker->isAlive() && !defender->isAlive()) return DIETOGETHER;
        else if (!attacker->isAlive()) return DEFENDER_WINS;
        else if (!defender->isAlive()) return ATTACKER_WINS;
    }
    return ENDLESS;
}
