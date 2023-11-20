//
// Created by User on 11/14/2023.
//

#ifndef OOP_CARTE_H
#define OOP_CARTE_H

#include <ostream>
#include <string>
#include <sstream>
#include "Suite.h"
#include "Gen.h"



class Card {
public:
    Card(Suite s, Gen g, bool cardup) : suit(s), gen(g), cardUp(cardup) {}

    Gen GetGen();

    Suite GetSuit();

    void Flip();

    friend std::ostream &operator<<(std::ostream &out, const Card &cart) {

        std::ostringstream str;
        if (cart.cardUp) {
            const std::string suite[] = {"Inima_Rosie", "Romb", "Trefla", "Inima_Neagra"};
            const std::string gene[] = {"As", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
            str << gene[cart.gen] << " " << suite[cart.suit] <<std::endl;
        } else {
            str << "Face down" << std::endl;
        }
        out << str.str();
        return out;
    }

private:
    Suite suit;
    Gen gen;
    bool cardUp;
};
#endif //OOP_CARTE_H
