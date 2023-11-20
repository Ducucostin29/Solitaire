//
// Created by User on 11/18/2023.
//

#ifndef OOP_DECK_CRESCATOR_H
#define OOP_DECK_CRESCATOR_H
#include "Deck.h"
#include "Carte.h"


class BreedingBord : public Deck {
public:
    explicit BreedingBord(Suite color, int index) : Deck("ascedenting", index, 13) {
        this->color = color;
    }

    bool completed()  override {

        if (!Deck::completed()) return false;

        for (unsigned long long i = 0; i < this->cards.size()-1; i++){
            if (this->cards[i]->GetGen() >= this->cards[i+1]->GetGen())
                return false;
        }
        return true;
    }


protected:
    Suite color;

    bool validation(Card *cart) override {
        if (this->color != cart->GetSuit())return false;

        if (this->giveLastCard() == nullptr) {
            if (cart->GetGen() == Ace) return true;
        } else {
            if (this->giveLastCard()->GetGen() + 1 == cart->GetGen()) return true;
        }

        return false;
    }
};


#endif //OOP_DECK_CRESCATOR_H
