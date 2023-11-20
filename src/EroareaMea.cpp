//
// Created by User on 11/14/2023.
//

#include "../h/EroareaMea.h"

MyError::MyError(char* msg){
    this->msg = msg;
}

char* MyError::afis(){
    return this->msg;
}