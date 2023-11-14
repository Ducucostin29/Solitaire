//
// Created by User on 11/14/2023.
//

#ifndef OOP_CARTE_H
#define OOP_CARTE_H

#include <ostream>
#include <string>
#include <sstream>

#include "suite.h"
#include "gen.h"

using namespace std;

class Carte {
public:
    Carte(Suite s, Gen g, bool carteinsus) : suit(s), gen(g), CarteinSus(carteinsus) {}

    Gen GetGen();

    Suite GetSuit();

    void Flip();

    friend ostream &operator<<(ostream &out, const Carte &carte) {

        ostringstream str;
        if (carte.CarteinSus) {
            const string suite[] = {"Inima_Rosie", "Romb", "Trefla", "Inima_Neagra"};
            const string gene[] = {"As", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
            str << gene[carte.gen] << " " << suite[carte.suit] << endl;
        } else {
            str << "Cu fata in jos" << endl;
        }
        out << str.str();
        return out;
    }

private:
    Suite suit;
    Gen gen;
    bool CarteinSus;
};


#endif //OOP_CARTE_H
