//
// Created by User on 11/18/2023.
//

#ifndef OOP_DECK_DESCRESCATOR_H
#define OOP_DECK_DESCRESCATOR_H
#include "Deck.h"
#include <vector>
#include "MatchOpus.h"


#include "Deck.h"
#include <vector>
#include "MatchOpus.h"



class Deck_Descrescator : public Deck {
public:
    explicit Deck_Descrescator(const std::vector<Carte *> &cartiInitiale, int indice) : Deck("descrescator", indice, 0) {
        for (auto i: cartiInitiale)
            this->carti.push_back(i);
    }

protected:
    bool validare(Carte *cart) override {
        if (this->damiUltimaCarte() == nullptr) {
            if (cart->GetGen() == Rege)return true;
        } else if (this->damiUltimaCarte()->GetGen() == cart->GetGen() + 1 &&
                   matchOpus(cart->GetSuit(), damiUltimaCarte()->GetSuit()))
            return true;
        return false;
    }
};

#endif //OOP_DECK_DESCRESCATOR_H
