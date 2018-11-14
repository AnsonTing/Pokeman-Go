#ifndef SKILL_H
#define SKILL_H

#include "kun.h"

void water_spray(Kun* a, Kun* b) {
    double aatk = a->getAttack();
    double bdef = b->getDefense();
    double bhp = b->getHP();

    double damage = (aatk - bdef) > 1 ? (aatk - bdef) : 1;
    b->setHP(bhp - damage);
}

void hydro_pump(Kun* a, Kun* b) {
    double aatk = a->getAttack() * 1.5;
    double adef = a->getDefense() * 0.8;
    double bdef = b->getDefense();
    double bhp = b->getHP();

    double damage = (aatk - bdef) > 1 ? (aatk - bdef) : 1;
    a->setDefense(adef);
    b->setHP(bhp - damage);
}

void aqua_ring(Kun* a, Kun*) {
    double ahp = a->getHP();
    a->setHP(ahp+5);
}

void double_edge(Kun* a, Kun* b) {
    double aatk = a->getAttack();
    double bdef = b->getDefense();
    double ahp = a->getHP();
    double bhp = b->getHP();

    double diff = aatk - bdef;
    double damage = diff > 1 ? diff : 1;
    a->setHP(ahp - damage);
    b->setHP(bhp - damage * 2);
}

#endif /* SKILL_H */
