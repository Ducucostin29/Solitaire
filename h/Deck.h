//
// Created by User on 11/15/2023.
//

#ifndef OOP_DECK_H
#define OOP_DECK_H


#include "Carte.h"
#include <string>
#include <vector>
#include "MyVector.h"

class  Deck {
public:
    Deck(const char *nume , int indice, unsigned long long int cartiNecesareCatig):nume(nume),indice(indice),cartiNecesareCatig(cartiNecesareCatig){}

    virtual ~Deck(){
        for (size_t i=0; i< this->carti.size(); i++)
            delete this->carti[i];
    }
    bool Adauga_Carte(Carte *carte);

    friend std::ostream &operator<<(std::ostream &out, const Deck &deck) {
        out << deck.nume << " "<< deck.indice+1 << std::endl;

        for (size_t i=0; i< deck.carti.size(); i++)
            out << " " << *deck.carti[i];

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
    MyVector<Carte *> carti;
};
#endif //OOP_DECK_H
