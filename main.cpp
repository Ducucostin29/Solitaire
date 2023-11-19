#include "h/Joc.h"


int main() {

    Joc *joc;
    joc = new Joc();
    std::cout << *joc;
    joc->mutari();
    delete joc;

    return 0;
}
