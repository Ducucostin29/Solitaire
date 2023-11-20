//
// Created by User on 11/14/2023.
//

#include "../h/Carte.h"

Gen Card::GetGen() {
    return this->gen;
}

Suite Card::GetSuit() {
    return this->suit;
}

void Card::Flip() {
    cardUp = !cardUp;
}