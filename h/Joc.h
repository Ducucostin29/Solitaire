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
        for(size_t i=0;i<game.breed.size();i++)
            out<<*game.breed[i];
        for(size_t i=0;i<game.desc.size();i++)
            out<<*game.desc[i];
        return out;
    }

    static std::vector<Carte *> Random(std::vector<Carte *> const &v);

    bool Win();

    void Moves();

private:
    Deck_Ascuns *hidden{};
    MyVector<Deck_Crescator *> breed;
    MyVector<Deck_Descrescator *> desc;
    void MoveCard();
    void MoveCard2();
};


#endif //OOP_JOC_H
