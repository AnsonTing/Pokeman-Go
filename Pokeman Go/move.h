#ifndef MOVE_H
#define MOVE_H

#include <string>

class Kun;

typedef void (*Move_logic)(Kun *, Kun *);

class Move {
    private:
        std::string name;
        Move_logic lg;
    public:
        Move();
        Move(std::string move_name, Move_logic move_logic);
        Move(const Move& m);

        void operator()(Kun* attacker, Kun* defender);
        std::string getName();
};

#endif /* MOVE_H */
