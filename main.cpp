#include <iostream>
#include <utility>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

enum Suite { Inima_Rosie [[maybe_unused]], Romb [[maybe_unused]], Trefla [[maybe_unused]], Inima_Neagra [[maybe_unused]]
};
enum Gen { As, Doi [[maybe_unused]], Trei [[maybe_unused]], Patru [[maybe_unused]], Cinci [[maybe_unused]], Sase [[maybe_unused]], Sapte [[maybe_unused]], Opt [[maybe_unused]], Noua [[maybe_unused]], Zece [[maybe_unused]], Juvete [[maybe_unused]], Regina [[maybe_unused]], Rege };

bool matchOpus(Suite culoare, Suite match ){
    if (culoare <= 1 && match >= 2) return true;
    if (culoare >= 2 && match <= 1) return true;
    return false;
}


class Carte {
public:
    Carte(Suite s, Gen g, bool carteinsus) : suit(s), gen(g), CarteinSus(carteinsus){}
    void Flip() { CarteinSus = !CarteinSus; }
    Gen GetGen(){
        return this->gen;
    }
    Suite GetSuit(){
        return this->suit;
    }
    friend ostream & operator << (ostream &out, const Carte &carte ){

        ostringstream str;
        if (carte.CarteinSus) {
            string suite[] = { "Inima_Rosie", "Romb", "Trefla", "Inima_Neagra" };
            string gene[] = { "As", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
            str<< gene[carte.gen] << " " << suite[carte.suit] << endl;
        }
        else {
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

class Deck{

public:
    explicit Deck(string nume){
        this->nume = std::move(nume);
    }
    ~Deck()=default;
    bool Adauga_Carte(Carte* carte){
        if(validare(carte)){
            this->carti.push_back(carte);
            return true;
        }
        return false;
    }
    friend ostream & operator << (ostream &out, const Deck &deck ){
        out << "deck: " << deck.nume << endl;
        for(auto i : deck.carti)
            out<< "  "<<*i;
        return out;

    }
private:
    string nume;
protected:
    Carte* damiUltimaCarte(){
        if (this->carti.empty()) { return nullptr; }
        return this->carti.back();
    }
    virtual bool validare(Carte *cart [[maybe_unused]])
    {
        return true;
    }
    vector<Carte*>carti;
};

class Deck_Ascuns : public Deck{
public:
    Deck_Ascuns () : Deck("ascuns") {
    }
};

class Deck_Crescator : public Deck{
public:
    explicit Deck_Crescator (Suite culoare) : Deck("crescator") {
        this->culoare = culoare;
    }
protected:
    Suite culoare;

    bool validare(Carte *cart) override
    {
        if(this->culoare != cart->GetSuit() )return false;

        if (this->damiUltimaCarte() == nullptr){
            if (cart->GetGen() == As) return true;
        }else {
            if( this->damiUltimaCarte()->GetGen()+1 == cart->GetGen()  ) return true;
        }


        return false;
    }
};

class Deck_Descrescator : public Deck{
public:
    explicit Deck_Descrescator ( const vector<Carte*>&cartiInitiale ) : Deck("descrescator"){
        for(auto i : cartiInitiale)
            this->carti.push_back(i);
    }
protected:
    bool validare(Carte* cart) override{
        if(this->damiUltimaCarte()==nullptr){
            if(cart->GetGen()== Rege)return true;
        }else
        if(this->damiUltimaCarte()->GetGen() == cart->GetGen() +1 && matchOpus(cart->GetSuit(),damiUltimaCarte()->GetSuit()) ) return true;
            return  false;
    }

};

class Joc{
public:
    explicit Joc(){
        this->InitializareJoc();
    }
    ~Joc()=default;
    void InitializareJoc() {

        vector<Carte*>cartiJoc;
        for(int i=0;i<=12; i+=1){
            for (int j=0; j <=3; j+=1){
                Carte* cart;
                cart=new Carte( Suite(j), Gen(i), true);
                cartiJoc.push_back(cart);
            }
        }

        cartiJoc = aranjareRandom(cartiJoc);


        for(int i=0;i<4;i++)
            this->crescatori.push_back( new Deck_Crescator( Suite(i)  ));

        int c=0;
        for(int i=0;i<7;i++){
            vector<Carte*>cartiInitiale;
            for (int j=0; j< i; j++){
                if (j != i-1) cartiJoc[c]->Flip();

                cartiInitiale.push_back(cartiJoc[c]);
                c++;
            }
            this->descrescatori.push_back(new Deck_Descrescator(cartiInitiale));
        }

        this->ascuns=new Deck_Ascuns();
        for(long long unsigned int i=c; i < cartiJoc.size(); i++){
            cartiJoc[i]->Flip();
            this->ascuns->Adauga_Carte(cartiJoc[i]);
        }

    }
    friend ostream & operator << (ostream &out, const Joc &joc ){
        out << "joc: " << endl;
        out << *joc.ascuns;
        for (auto i : joc.crescatori)
            out << *i;

        for (auto i : joc.descrescatori)
            out << *i;
        return out;
    }
    static vector<Carte*> aranjareRandom(vector<Carte*>v){
        vector<Carte*> aleatoriu = std::move(v);
        //pe viitor
        return aleatoriu;
    }
    /*bool castigare(){
        for (int i = 0; i < crescatori.size(); i++) {
       if (crescatori[i]->carti.size() < 13) {
           return false;
       }
   }
   for (int i = 0; i < descrescatori.size(); i++) {
       if (descrescatori[i]->carti.size() > 0) {
           return false;
       }
   }
   if (ascuns->carti.size() > 0) {
       return false;
   }
   return true;

    }*/
private:
    Deck_Ascuns *ascuns{};
    vector<Deck_Crescator*>crescatori;
    vector<Deck_Descrescator*>descrescatori;
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
    joc=new Joc();
    cout << *joc;
    joc->~Joc();

    return 0;
}
