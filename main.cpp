#include "h/Joc.h"
#include "h/MyVector.h"
#include "h/MyList.h"

int main() {

    auto *v = new MyVector<int>();
    v->clear();
    v->push_back(1);
    v->push_back(2);
    v->push_back(3);
    v->push_back(4);
    v->push_back(5);
    std::cout << *v << std::endl;
    delete v;

    auto *l = new MyList<int>();
    l->push_back(10);
    l->push_back(20);
    l->push_back(30);
    l->push_back(40);
    l->push_back(50);
    std::cout << *l << std::endl ;
    std::cout << "element de pe pozitia 3 " << (*l)[2] << std::endl;
    std::cout << "lungime lista " << l->size() << std::endl;
    std::cout << "ultimul element " << l->back() << std::endl;
    delete l;

    Game *joc ;
    joc = new Game();
    std::cout << *joc;
    joc->Moves();


//    MyVector<Game*> *v2 = new MyVector<Game*>();
//    v2->push_back(joc);
//    std::cout << *v2;
//    std::cout << " element pe v0"  << *(*v2)[0];
//    v2->clear();
//    delete v2

    delete joc;
    return 0;
}
