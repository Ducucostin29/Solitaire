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



class Carte {
public:
    Carte(Suite s, Gen g, bool carteinsus) : suit(s), gen(g), CarteinSus(carteinsus) {}

    Gen GetGen();

    Suite GetSuit();

    void Flip();

    friend std::ostream &operator<<(std::ostream &out, const Carte &carte) {

        std::ostringstream str;
        if (carte.CarteinSus) {
            const std::string suite[] = {"Red_Heart", "Diamond", "Club", "Black_Heart"};
            const std::string gene[] = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
            str << gene[carte.gen] << " " << suite[carte.suit] << std::endl;
        } else {
            str << "Cu fata in jos" << std::endl;
        }
        out << str.str() ;
        return out;
    }

private:
    Suite suit;
    Gen gen;
    bool CarteinSus;
};
#endif //OOP_CARTE_H
