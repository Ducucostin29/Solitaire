//
// Created by User on 11/14/2023.
//

#ifndef OOP_EROAREAMEA_H
#define OOP_EROAREAMEA_H

#include <exception>

class MyError  : public std::exception{
public:
    explicit MyError(char* msg);
    char* afis();
private:
    char* msg;
};


#endif //OOP_EROAREAMEA_H
