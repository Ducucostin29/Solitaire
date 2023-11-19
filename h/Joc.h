//
// Created by User on 11/18/2023.
//

#ifndef OOP_JOC_H
#define OOP_JOC_H
#include "Deck.h"
#include "Carte.h"
#include "EroareaMea.h"
#include <vector>
#include <iostream>
#include <ostream>
#include "../h/Deck_Ascuns.h"
#include "../h/Deck_Descrescator.h"
#include "../h/Deck_Crescator.h"


class Joc {
public:
    explicit Joc() {
        this->InitializareJoc();
    }

    ~Joc() {
        delete this->ascuns;
        for (int i = 0; i < 4; i++)
            delete this->crescatori[i];
        for (int i = 0; i < 7; i++)
            delete this->descrescatori[i];

    }
    void InitializareJoc();

    friend std::ostream &operator<<(std::ostream &out, const Joc &joc) {
        out << "joc: " << std::endl;
        out << *joc.ascuns;
        for (Deck_Crescator *const i: joc.crescatori)
            out << *i;

        for (Deck_Descrescator *const i: joc.descrescatori)
            out << *i;
        return out;
    }

    static std::vector<Carte *> aranjareRandom(std::vector<Carte *> const &v);

    bool castigare();

    void mutari();

private:
    Deck_Ascuns *ascuns{};
    std::vector<Deck_Crescator *> crescatori;
    std::vector<Deck_Descrescator *> descrescatori;
    void mutaCarte();
};


#endif //OOP_JOC_H
