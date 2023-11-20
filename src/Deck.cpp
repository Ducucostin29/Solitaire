//
// Created by User on 11/15/2023.
//

#include "../h/Deck.h"

    bool Deck :: AddCard(Card *carte){
        if (validation(carte)) {
            this->cards.push_back(carte);
            return true;
        }
        return false;
    }

    bool Deck :: completed(){
        return this->cards.size() == this->cardsNeed;
    }

