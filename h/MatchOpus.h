//
// Created by User on 11/15/2023.
//

#ifndef OOP_MATCHOPUS_H
#define OOP_MATCHOPUS_H

#include "Suite.h"
#include "Gen.h"

static bool matchOpus(Suite color, Suite match) {
    if (color <= 1 && match >= 2) return true;
    if (color >= 2 && match <= 1) return true;
    return false;
}
#endif //OOP_MATCHOPUS_H
