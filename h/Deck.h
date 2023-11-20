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
    Deck(const char *nume , int indice, unsigned long long int cartiNecesareCatig){
        this->nume = nume;
        this->indice = indice;
        this->cartiNecesareCatig = cartiNecesareCatig;
    }

    virtual ~Deck(){
        for (auto &i: this->carti)
            delete i;
    }
    bool Adauga_Carte(Carte *carte);

    friend std::ostream &operator<<(std::ostream &out, const Deck &deck) {
        out << deck.nume << " "<< deck.indice+1 << std::endl;
        for (Carte *const i: deck.carti)
            out << "  " << *i;
        return out;
    }

    virtual bool finalizat();

    Carte *damiUltimaCarte(){
        if (this->carti.empty()) { return nullptr; }
        return this->carti.back();
    }

protected:
    std::string nume;
    int indice;
    unsigned long long int cartiNecesareCatig;
    virtual bool validare(Carte *cart ) =0;
    std::vector<Carte *> carti;
};
#endif //OOP_DECK_H
