#include <iostream>
#include <random>
//#include <ctime>
#include "h/EroareaMea.h"
#include "h/MatchOpus.h"
#include "h/Joc.h"

using namespace std;

/*const unsigned int seed = time(nullptr);
mt19937_64 rng(seed);
uniform_int_distribution<unsigned long int> uniformIntDistribution;*/


int main() {

    Joc *joc;
    joc = new Joc();
    cout << *joc;
    joc->mutari();
    delete joc;

    return 0;
}
