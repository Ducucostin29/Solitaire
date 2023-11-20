//
// Created by User on 11/18/2023.
//

#ifndef OOP_DECK_ASCUNS_H
#define OOP_DECK_ASCUNS_H
#include "Deck.h"


#include "Deck.h"


class Deck_Ascuns : public Deck{
public:
    Deck_Ascuns() : Deck("ascuns", 0, 0){
    }

protected:
    bool validare(Carte *) override {
        return true;
    }
};



#endif //OOP_DECK_ASCUNS_H
