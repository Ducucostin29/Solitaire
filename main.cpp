#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <random>
#include <ctime>

using namespace std;

const unsigned int seed = time(nullptr);
mt19937_64 rng(seed);
uniform_int_distribution<unsigned long long int> uniformIntDistribution;

class EroareaMea : public exception{
public:
    explicit EroareaMea(char* msg){
        this->msg = msg;
    }
    char* afiseaza(){
        return this->msg;
    }
private:
    char* msg;
};

enum Suite {
    Inima_Rosie [[maybe_unused]], Romb [[maybe_unused]], Trefla [[maybe_unused]], Inima_Neagra [[maybe_unused]]
};

enum Gen {
    As,
    Doi [[maybe_unused]],
    Trei [[maybe_unused]],
    Patru [[maybe_unused]],
    Cinci [[maybe_unused]],
    Sase [[maybe_unused]],
    Sapte [[maybe_unused]],
    Opt [[maybe_unused]],
    Noua [[maybe_unused]],
    Zece [[maybe_unused]],
    Juvete [[maybe_unused]],
    Regina [[maybe_unused]],
    Rege
};

bool matchOpus(Suite culoare, Suite match) {
    if (culoare <= 1 && match >= 2) return true;
    if (culoare >= 2 && match <= 1) return true;
    return false;
}


class Carte {
public:
    Carte(Suite s, Gen g, bool carteinsus) : suit(s), gen(g), CarteinSus(carteinsus) {}

    void Flip() { CarteinSus = !CarteinSus; }

    Gen GetGen() {
        return this->gen;
    }

    Suite GetSuit() {
        return this->suit;
    }

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

class Deck {

public:
    explicit Deck(const char *nume, int indice, unsigned long long int cartiNecesareCatig) {
        this->nume = nume;
        this->indice = indice;
        this->cartiNecesareCatig = cartiNecesareCatig;
    }

    virtual ~Deck() {
        for (auto &i: this->carti)
            delete i;
    }

    bool Adauga_Carte(Carte *carte) {
        if (validare(carte)) {
            this->carti.push_back(carte);
            return true;
        }
        return false;
    }

    friend ostream &operator<<(ostream &out, const Deck &deck) {
        out << deck.nume << " "<< deck.indice+1 << endl;
        for (Carte *const i: deck.carti)
            out << "  " << *i;
        return out;
    }


    virtual bool finalizat(){
        return this->carti.size() == this->cartiNecesareCatig;
    };

    Carte *damiUltimaCarte() {
        if (this->carti.empty()) { return nullptr; }
        return this->carti.back();
    }

protected:
    string nume;
    int indice;
    unsigned long long int cartiNecesareCatig;
protected:

    virtual bool validare(Carte *cart ) =0;

    vector<Carte *> carti;
};

class Deck_Ascuns : public Deck {
public:
    Deck_Ascuns() : Deck("ascuns", 0, 0){
    }

protected:
    bool validare(Carte *) override {
        return true;
    }

};

class Deck_Crescator : public Deck {
public:
    explicit Deck_Crescator(Suite culoare, int indice) : Deck("crescator", indice, 13) {
        this->culoare = culoare;
    }

    bool finalizat()  override {

        if (!Deck::finalizat()) return false;

        for (unsigned long long i = 0; i < this->carti.size()-1; i++){
            if (this->carti[i]->GetGen() >= this->carti[i+1]->GetGen())
                return false;
        }
        return true;
    }


protected:
    Suite culoare;

    bool validare(Carte *cart) override {
        if (this->culoare != cart->GetSuit())return false;

        if (this->damiUltimaCarte() == nullptr) {
            if (cart->GetGen() == As) return true;
        } else {
            if (this->damiUltimaCarte()->GetGen() + 1 == cart->GetGen()) return true;
        }

        return false;
    }
};

class Deck_Descrescator : public Deck {
public:
    explicit Deck_Descrescator(const vector<Carte *> &cartiInitiale, int indice) : Deck("descrescator", indice, 0) {
        for (auto i: cartiInitiale)
            this->carti.push_back(i);
    }

protected:
    bool validare(Carte *cart) override {
        if (this->damiUltimaCarte() == nullptr) {
            if (cart->GetGen() == Rege)return true;
        } else if (this->damiUltimaCarte()->GetGen() == cart->GetGen() + 1 &&
                   matchOpus(cart->GetSuit(), damiUltimaCarte()->GetSuit()))
            return true;
        return false;
    }

};

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

    void InitializareJoc() {

        vector<Carte *> cartiJoc;
        for (int i = 0; i <= 12; i += 1) {
            for (int j = 0; j <= 3; j += 1) {
                Carte *cart;
                cart = new Carte(Suite(j), Gen(i), true);
                cartiJoc.push_back(cart);
            }
        }

        vector <Carte*> cartiJocAleatorii = aranjareRandom(cartiJoc);

        for (int i = 0; i < 4; i++)
            this->crescatori.push_back(new Deck_Crescator(Suite(i), i));

        int c = 0;
        for (int i = 0; i < 7; i++) {
            vector<Carte *> cartiInitiale;
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
            this->ascuns->Adauga_Carte(cartiJocAleatorii[i]);
        }

    }

    friend ostream &operator<<(ostream &out, const Joc &joc) {
        out << "joc: " << endl;
        out << *joc.ascuns;
        for (Deck_Crescator *const i: joc.crescatori)
            out << *i;

        for (Deck_Descrescator *const i: joc.descrescatori)
            out << *i;
        return out;
    }

    static vector<Carte *> aranjareRandom(vector<Carte *> const &v) {

        vector<Carte *> aleatoriu;
        vector<bool> selectat;

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

    bool castigare(){
        if (!this->ascuns->finalizat()) return false;
        for ( Deck_Crescator* const it : this->crescatori ){
            if (!it->finalizat()) return false;
        }
        for ( Deck_Descrescator* const it : this->descrescatori){
            if (!it->finalizat()) return false;
        }
        return true ;
    }

    void mutari(){

        bool ok = true;
        while (ok){

            cout << "Status joc: ";
            if (!this->castigare()) cout << "NECASTIGATOR";
            else {
                cout << "CASITGATOR!!!!" << endl;
                ok = false;
                continue;
            }

            cout << "Vrei sa muti o carte? y/n" << endl;
            string optiune;
            cin >> optiune;
            if ( optiune == "y")
                this->mutaCarte();
            if (optiune == "n")
                break;


        }
    }

private:
    Deck_Ascuns *ascuns{};
    vector<Deck_Crescator *> crescatori;
    vector<Deck_Descrescator *> descrescatori;



    void mutaCarte(){
        try{
            cout << "selecteaza deck de unde vrei sa muti: "<< endl;
            int deUnde;
            cin >> deUnde;

            if (deUnde < 1) throw EroareaMea((char*)"Deck selectat prea mic. Nr trebuie sa fie mare decat 0");
            if (deUnde > 7) throw EroareaMea((char*)"Deck selectat prea mare. Nr trb sa fie mai mic decat 8");

            cout << "selecteaza deck unde vrei sa o muti: "<<endl;
            int unde;
            cin >> unde;

            if (unde < 1) throw EroareaMea((char*)"Deck selectat prea mic. Nr trebuie sa fie mare decat 0");
            if (unde > 7) throw EroareaMea((char*)"Deck selectat prea mare. Nr trb sa fie mai mic decat 8");

            Carte* carteSelectata = this->descrescatori[deUnde-1]->damiUltimaCarte();
            if ( this->descrescatori[unde-1]->Adauga_Carte(carteSelectata) ){
                cout << "Cartea a fost mutata cu success " << endl;
                cout << *this;
            }
            else throw EroareaMea((char*)"Nu se poate \n");

        }catch( EroareaMea &err ){
            cout << "EROARE =" << err.afiseaza();
        }
    }

};

int main() {


    /*Carte *cart1, *cart2, *cart3, *cart13, *cart14;
    cart3 = new Carte( Inima_Rosie,  Trei, true );

    cart2=new Carte(Inima_Neagra,Doi,true);
    cart1=new Carte(Inima_Neagra,As,true);
    cout<< *cart3;
    cart13=new Carte(Inima_Neagra,Regina,true);
    cart14=new Carte(Inima_Neagra,Rege,true);

    Deck *deck;
    deck=new Deck("obisnuit");
    deck->Adauga_Carte(cart3);
    deck->Adauga_Carte(cart3);
    cout<<*deck;


    Deck_Crescator *deck_cres;
    deck_cres=new Deck_Crescator(Inima_Neagra);
    deck_cres->Adauga_Carte(cart2);
    deck_cres->Adauga_Carte(cart1);
    deck_cres->Adauga_Carte(cart2);
    deck_cres->Adauga_Carte(cart3);

    cout<<*deck_cres;

    Deck_Descrescator *deck_desc;
    vector<Carte*>cartiInitiale;
    cartiInitiale.push_back(cart3);
    deck_desc=new Deck_Descrescator(cartiInitiale);
    deck_desc->Adauga_Carte(cart2);
    deck_desc->Adauga_Carte(cart1);
    deck_desc->Adauga_Carte(cart2);
    deck_desc->Adauga_Carte(cart14);
    deck_desc->Adauga_Carte(cart13);
    deck_desc->Adauga_Carte(cart3);


    cout<<*deck_desc;





    */
    Joc *joc;
    joc = new Joc();
    cout << *joc;

    joc->mutari();



    delete joc;

    return 0;
}
