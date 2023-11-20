#include "h/Joc.h"

int main() {

    Game *joc ;
    joc = new Game();
    std::cout << *joc;
    joc->Moves();
    delete joc;
    return 0;
}
