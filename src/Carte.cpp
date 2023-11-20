//
// Created by User on 11/14/2023.
//

#include "../h/Carte.h"

Gen Carte::GetGen() {
    return this->gen;
}

Suite Carte::GetSuit() {
    return this->suit;
}

void Carte::Flip() {
    CarteinSus = !CarteinSus;
}