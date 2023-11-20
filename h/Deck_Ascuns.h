//
// Created by User on 11/18/2023.
//

#ifndef OOP_DECK_ASCUNS_H
#define OOP_DECK_ASCUNS_H
#include "Deck.h"


class HiddenBord : public Deck {
public:
    HiddenBord() : Deck("hidden", 0, 0){
    }

protected:
    bool validation(Card *) override {
        return true;
    }
};


#endif //OOP_DECK_ASCUNS_H
