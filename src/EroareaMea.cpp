//
// Created by User on 11/14/2023.
//

#include "../h/EroareaMea.h"

EroareaMea::EroareaMea(char* msg) {
    this->msg = msg;
}

char* EroareaMea::afiseaza(){
    return this->msg;
}