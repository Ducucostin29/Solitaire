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


class Game {
public:
    explicit Game() {
        this->GameInitialization();
    }

    ~Game() {
        delete this->hidden;
        for (int i = 0; i < 4; i++)
            delete this->breed[i];
        for (int i = 0; i < 7; i++)
            delete this->desc[i];

    }
    void GameInitialization();

    friend std::ostream &operator<<(std::ostream &out, const Game &game) {
        out << "joc: " << std::endl;
        out << *game.hidden;
        for (BreedingBord *const i: game.breed)
            out << *i;
        for (DescendingBord *const i: game.desc)
            out << *i;
        return out;
    }

    static std::vector<Card *> Random(std::vector<Card *> const &v);

    bool Win();

    void Moves();

private:
    HiddenBord *hidden{};
    std::vector<BreedingBord *> breed;
    std::vector<DescendingBord *> desc;
    void MoveCard();
};


#endif //OOP_JOC_H
