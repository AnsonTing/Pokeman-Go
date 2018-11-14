#ifndef TRAINER_H
#define TRAINER_H

#include <string>
#include <iostream>
#include "container.h"
#include "kun.h"
#include "item.h"

/*
* Typedef the Backpack and KunGroup with Container template.
*
* Use Backpack and KunGroup instead of other name to fit the implementation
* in the trainer.cpp and trainer.h files.
*
* Add your code here!
*/

typedef Container<Item> Backpack;
typedef Container<Kun> KunGroup;

using namespace std;

class Trainer {

public:

    /*
     *  constructor
     */
    Trainer(string name);

    /*
     *  returns trainer's name
     */
    string getName() const;

    /*
     *  returns a refernence to trainer's backpack
     */
    Backpack& getBackpack();
    /*
     *  returns a refernence to trainer's kungroup
     */
    KunGroup& getKunGroup();

    /*
     *  First, check whether the item & kun belong to the trainer
     *  If no, do nothing
     *  If yes, let the kun eat the item. Then remove it from backpack and delete it
     */
    void feedItemToKun(Item* item, Kun* kun);

    /*
     *  init a kun in heap using the default constructor and add it to kungroup
     */
    void receiveNewbornKunFromProf();

    /*
     *  increase the exp of kun, each time 100
     */
    void trainKunInTheWild(Kun* kun, int times = 1);

    /*
     *  helper function to see trainer's details
     */
    inline void printDetails() const {
        cout<<"\n----- Trainer \""<<name.c_str()<<"\" -----\n";
        cout<<"Backpack:"<<endl;
        backpack.printDetails();
        cout<<"KunGroup:"<<endl;
        kunGroup.printDetails();
    };

private:

    const string name;  // the string that stores the trainer's name

    Backpack backpack;  // the backpack that stores the trainer's items
    KunGroup kunGroup;  // the kungroup that stores the trainer's kuns
};

#endif /* TRAINER_H */
