#include "trainer.h"

Trainer::Trainer(string name): name(name) {
}

string Trainer::getName() const {
    return name;
}

Backpack& Trainer::getBackpack() {
    return backpack;
}

KunGroup& Trainer::getKunGroup() {
    return kunGroup;
}

void Trainer::feedItemToKun(Item* item, Kun* kun) {
    if (!backpack.hasValue(item) || !kunGroup.hasValue(kun)) return;
    *kun << item;
    backpack.removeValue(item, true);
}

void Trainer::receiveNewbornKunFromProf() {
    Kun* tmp = new Kun();
    kunGroup.addValue(tmp);
}

void Trainer::trainKunInTheWild(Kun* kun, int times) {
    if (!kunGroup.hasValue(kun)) return;
    for (int i=0;i<times;i++) kun->gainExperience(100);
}
