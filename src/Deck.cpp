//
// Created by User on 11/15/2023.
//

#include "../h/Deck.h"

bool Deck :: Adauga_Carte(Carte *carte){
    if (validare(carte)) {
        this->carti.push_back(carte);
        return true;
    }
    return false;
}

bool Deck :: finalizat() {
    return this->carti.size() == this->cartiNecesareCatig;
}
