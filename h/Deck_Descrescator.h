//
// Created by User on 11/18/2023.
//

#ifndef OOP_DECK_DESCRESCATOR_H
#define OOP_DECK_DESCRESCATOR_H
#include "Deck.h"
#include <vector>
#include "MatchOpus.h"


class DescendingBord : public Deck {
public:
    explicit DescendingBord(const std::vector<Card *> &cardInit, int indice) : Deck("descending", indice, 0) {
        for (auto i: cardInit)
            this->cards.push_back(i);
    }

protected:
    bool validation(Card *cart) override {
        if (this->giveLastCard() == nullptr) {
            if (cart->GetGen() == King)return true;
        } else if (this->giveLastCard()->GetGen() == cart->GetGen() + 1 &&
                   matchOpus(cart->GetSuit(), giveLastCard()->GetSuit()))
            return true;
        return false;
    }

};

#endif //OOP_DECK_DESCRESCATOR_H
