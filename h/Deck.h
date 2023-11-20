//
// Created by User on 11/15/2023.
//

#ifndef OOP_DECK_H
#define OOP_DECK_H


#include "Carte.h"
#include <string>
#include <vector>

class  Deck {
public:
    Deck(const char *name, int index, unsigned long long int cartNeedWin){
        this->name = name;
        this->index = index;
        this->cardsNeed = cartNeedWin;
    }

    virtual ~Deck(){
        for (auto &i: this->cards)
            delete i;
    }
    bool AddCard(Card *card);

    friend std::ostream &operator<<(std::ostream &out, const Deck &deck) {
        out << deck.name << " "<< deck.index+1 << std::endl;
        for (Card *const i: deck.cards)
            out << "  " << *i;
        return out;
    }

    virtual bool completed();

    Card *giveLastCard(){
        if (this->cards.empty()) { return nullptr; }
        return this->cards.back();
    }

protected:
    std::string name;
    int index;
    unsigned long long int cardsNeed;
    virtual bool validation(Card *cart) =0;
    std::vector<Card *> cards;
};
#endif //OOP_DECK_H
