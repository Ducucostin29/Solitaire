//
// Created by User on 11/18/2023.
//

#include "../h/Joc.h"
#include <iostream>
#include <random>
#include <ctime>

const unsigned int seed = time(nullptr);
std::mt19937_64 rng(seed);
std::uniform_int_distribution<unsigned long int> uniformIntDistribution;



void Joc::InitializareJoc() {

    std::vector<Carte *> cartiJoc;
    for (int i = 0; i <= 12; i += 1) {
        for (int j = 0; j <= 3; j += 1) {
            Carte *cart;
            cart = new Carte(Suite(j), Gen(i), true);
            cartiJoc.push_back(cart);
        }
    }

    std::vector <Carte*> cartiJocAleatorii = aranjareRandom(cartiJoc);

    for (int i = 0; i < 4; i++)
        this->crescatori.push_back(new Deck_Crescator(Suite(i), i));

    int c = 0;
    for (int i = 0; i < 7; i++) {
        std::vector<Carte *> cartiInitiale;
        for (int j = 0; j <= i; j++) {
            if (j != i ) cartiJocAleatorii[c]->Flip();

            cartiInitiale.push_back(cartiJocAleatorii[c]);
            c++;
        }
        this->descrescatori.push_back(new Deck_Descrescator(cartiInitiale, i));
    }

    this->ascuns = new Deck_Ascuns();
    for (long long unsigned int i = c; i < cartiJocAleatorii.size(); i++) {
        cartiJocAleatorii[i]->Flip();
        this->ascuns->Deck::Adauga_Carte(cartiJocAleatorii[i]);
    }

}

 std::vector<Carte *>Joc::aranjareRandom(const std::vector<Carte *> &v) {

    std::vector<Carte *> aleatoriu;
    std::vector<bool> selectat;

    for (unsigned long long int i =0; i < v.size(); i++ ){
        selectat.push_back(false);
        aleatoriu.push_back(nullptr);
    }

    for(  Carte * it : v){
        unsigned long long int pozitie = uniformIntDistribution(rng) %  v.size();
        while (selectat[pozitie]){
            pozitie = uniformIntDistribution(rng) %  v.size();
        }
        selectat[pozitie] = true;
        aleatoriu[pozitie] = it;
    }
    return aleatoriu;
}

bool Joc::castigare(){
    if (!this->ascuns->Deck::finalizat()) return false;
    for ( Deck_Crescator* const it : this->crescatori ){
        if (!it->finalizat()) return false;
    }
    for( Deck_Descrescator* const it : this->descrescatori){
        if (!it->Deck::finalizat()) return false;
    }
    return true ;
}

void Joc::mutari(){

    bool ok =true;
    while (ok){

        std::cout << "Status joc: ";
        if (!this->castigare()) std::cout << "NECASTIGATOR";
        else {
            std::cout << "CASITGATOR!!!!" << std::endl;
            ok = false;
            continue;
        }

        std::cout << "Vrei sa muti o carte? y/n" << std::endl;
        std::string optiune;
        std::cin >> optiune;
        if ( optiune == "y")
            this->mutaCarte();
        if (optiune == "n")
            break;

        return;

    }
}

void Joc::mutaCarte(){
    try{
        std::cout << "selecteaza deck de unde vrei sa muti: "<< std::endl;
        int deUnde;
        std::cin >> deUnde;

        if (deUnde < 1) throw EroareaMea((char*)"Deck selectat prea mic. Nr trebuie sa fie mare decat 0");
        if (deUnde > 7) throw EroareaMea((char*)"Deck selectat prea mare. Nr trb sa fie mai mic decat 8");

        std::cout << "selecteaza deck unde vrei sa o muti: "<<std::endl;
        int unde;
        std::cin >> unde;

        if (unde < 1) throw EroareaMea((char*)"Deck selectat prea mic. Nr trebuie sa fie mare decat 0");
        if (unde > 7) throw EroareaMea((char*)"Deck selectat prea mare. Nr trb sa fie mai mic decat 8");

        Carte* carteSelectata = this->descrescatori[deUnde-1]->Deck::damiUltimaCarte();
        if ( this->descrescatori[unde-1]->Deck::Adauga_Carte(carteSelectata) ){
            std::cout << "Cartea a fost mutata cu success " << std::endl;
            std::cout << *this;
        }
        else throw EroareaMea((char*)"Nu se poate \n");

    }catch( EroareaMea &err ){
        std::cout << "EROARE =" << err.afiseaza();
    }
}