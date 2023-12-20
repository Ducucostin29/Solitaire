#include "h/Joc.h"
#include "h/MyVector.h"
#include "h/MyList.h"

int main() {

    MyVector<int> *v = new MyVector<int>();
    v->clear();
    v->push_back(876);
    v->push_back(2876);
    v->push_back(3876);
    v->push_back(8576);
    v->push_back(8276);
    std::cout << *v << std::endl;

    MyList <int> *l = new MyList<int>();
    l->push_back(876);
    l->push_back(2876);
    l->push_back(3876);
    l->push_back(8576);
    l->push_back(8276);
    std::cout << *l << std::endl ;
    std::cout << "element de pe pozitia 3" << (*l)[2] << std::endl;

    Game *joc ;
    joc = new Game();
    std::cout << *joc;
    joc->Moves();


//    MyVector<Game*> *v2 = new MyVector<Game*>();
//    v2->push_back(joc);
//    std::cout << *v2;
//    std::cout << " element pe v0"  << *(*v2)[0];
//    v2->clear();

    delete joc;
    return 0;
}
