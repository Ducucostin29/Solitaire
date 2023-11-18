//
// Created by User on 11/15/2023.
//

#ifndef OOP_MATCHOPUS_H
#define OOP_MATCHOPUS_H

#include "Suite.h"
#include "Gen.h"

bool matchOpus(Suite culoare, Suite match) {
    if (culoare <= 1 && match >= 2) return true;
    if (culoare >= 2 && match <= 1) return true;
    return false;

#endif //OOP_MATCHOPUS_H
}