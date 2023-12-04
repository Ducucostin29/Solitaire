//
// Created by User on 11/18/2023.
//

#include "../h/Joc.h"
#include <random>
#include <ctime>
#include <iostream>

const unsigned int seed = time(nullptr);
std::mt19937_64 rng(seed);
std::uniform_int_distribution<unsigned long long int> uniformIntDistribution;


void Game::GameInitialization() {

    std::vector<Carte *> cards;
    for (int i = 0; i <= 12; i += 1) {
        for (int j = 0; j <= 3; j += 1) {
            Carte *cart;
            cart = new Carte(Suite(j), Gen(i), true);
            cards.push_back(cart);
        }
    }

    std::vector <Carte*> cardsGameRandom = Random(cards);

    for (int i = 0; i < 4; i++)
        this->breed.push_back(new Deck_Crescator(Suite(i), i));

    int c = 0;
    for (int i = 0; i < 7; i++) {
        std::vector<Carte *> cardsInit;
        for (int j = 0; j <= i; j++) {
            if (j != i )cardsGameRandom[c]->Flip();

            cardsInit.push_back(cardsGameRandom[c]);
            c++;
        }
        this->desc.push_back(new Deck_Descrescator(cardsInit, i));
    }

    this->hidden = new Deck_Ascuns();
    for (long long unsigned int i = c; i < cardsGameRandom.size(); i++) {
        cardsGameRandom[i]->Flip();
        this->hidden->Deck::Adauga_Carte(cardsGameRandom[i]);
    }

}

 std::vector<Carte *>Game::Random(const std::vector<Carte *> &v) {

    std::vector<Carte *> rando;
    std::vector<bool> select;

    for (unsigned long long int i =0; i < v.size(); i++ ){
        select.push_back(false);
        rando.push_back(nullptr);
    }

    for(  Carte * it : v){
        unsigned long long int pozitie = uniformIntDistribution(rng) %  v.size();
        while (select[pozitie]){
            pozitie = uniformIntDistribution(rng) %  v.size();
        }
        select[pozitie] = true;
        rando[pozitie] = it;
    }
    return rando;
}

bool Game::Win(){
    if (!this->hidden->Deck::finalizat()) return false;
    for ( Deck_Crescator* const it : this->breed ){
        if (!it->finalizat()) return false;
    }
    for( Deck_Descrescator* const it : this->desc){
        if (!it->Deck::finalizat()) return false;
    }
    return true ;
}

void Game::Moves(){

    bool ok =true;
    while (ok){

        std::cout << "Game status: ";
        if (!this->Win()) std::cout << "LOSING";
        else {
            std::cout << "WIN!!!!" << std::endl;
            ok = false;
            continue;
        }

        std::cout << "Do you want to move a card? 1/2/3" << std::endl;
        std::string opt;
        std::cin >> opt;
        if ( opt == "1")
            this->MoveCard();
        if( opt == "2")
            this->MoveCard2();
        if (opt == "3")
            break;

        return;

    }
}

void Game::MoveCard() {
    try {
        std::cout << "Select where to move: " << std::endl;
        int whereFrom;
        std::cin >> whereFrom;

        if (whereFrom < 1) throw EroareaMea((char *) "Deck selected too small. The number must be greater than 0");
        if (whereFrom > 7) throw EroareaMea((char *) "Deck selected too large. The number must be less than 8");

        std::cout << "Select where to move: " << std::endl;
        int unde;
        std::cin >> unde;

        if (unde < 1) throw EroareaMea((char *) "Deck selected too small. The number must be greater than 0");
        if (unde > 7) throw EroareaMea((char *) "Deck selected too large. The number must be less than 8");

        Carte *carteSelectata = this->desc[whereFrom - 1]->Deck::damiUltimaCarte();
        auto* descDeck = dynamic_cast<Deck_Descrescator*>(this->desc[unde - 1]);
        if (descDeck) {
            if (descDeck->Adauga_Carte(carteSelectata)) {
                std::cout << "The card was moved successfully " << std::endl;
                std::cout << *this;
            } else {
                throw EroareaMea((char*) "You can not \n");
            }
        } else {
            throw EroareaMea((char*) "Invalid deck type selected\n");
        }
    } catch (EroareaMea& err) {
        std::cout << "ERROR =" << err.afiseaza();
    }
}
void Game::MoveCard2(){
    try {
        std::cout << "Select where to move:" << std::endl;
        int putFrom;
        std::cin >> putFrom;

        if (putFrom < 1)throw EroareaMea((char *) "Deck selected too small. The number must be greater than 0");
        if (putFrom > 4) throw EroareaMea((char *) "Deck selected too large. The number must be less than 8");

        std::cout << "select deck where to put card" << std::endl;
        int where;
        std::cin >> where;

        Carte *cardSelect = this->desc[putFrom - 1]->Deck::damiUltimaCarte();
        auto* breedDeck = dynamic_cast<Deck_Crescator*>(this->breed[where]);

        if (breedDeck) {
            if (breedDeck->Adauga_Carte(cardSelect)) {
                std::cout << "The card was moved successfully  " << std::endl;
                std::cout << this;
            } else {
                throw EroareaMea((char*) "You can not \n");
            }
        } else {
            throw EroareaMea((char*) "Invalid deck type selected\n");
        }
    } catch (EroareaMea& err) {
        std::cout << "ERROR =" << err.afiseaza();
    }
}