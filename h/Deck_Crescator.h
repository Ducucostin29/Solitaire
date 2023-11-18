//
// Created by User on 11/18/2023.
//

#ifndef OOP_DECK_CRESCATOR_H
#define OOP_DECK_CRESCATOR_H
#include "Deck.h"
#include "Carte.h"


class Deck_Crescator : public Deck {
public:
    explicit Deck_Crescator(Suite culoare, int indice) : Deck("crescator", indice, 13) {
        this->culoare = culoare;
    }

    bool finalizat()  override {

        if (!Deck::finalizat()) return false;

        for (unsigned long long i = 0; i < this->carti.size()-1; i++){
            if (this->carti[i]->GetGen() >= this->carti[i+1]->GetGen())
                return false;
        }
        return true;
    }


protected:
    Suite culoare;

    bool validare(Carte *cart) override {
        if (this->culoare != cart->GetSuit())return false;

        if (this->damiUltimaCarte() == nullptr) {
            if (cart->GetGen() == As) return true;
        } else {
            if (this->damiUltimaCarte()->GetGen() + 1 == cart->GetGen()) return true;
        }

        return false;
    }
};


#endif //OOP_DECK_CRESCATOR_H
