//
// Created by User on 11/14/2023.
//

#ifndef OOP_EROAREAMEA_H
#define OOP_EROAREAMEA_H

#include <exception>

class EroareaMea  : public std::exception{
public:
    explicit EroareaMea(char* msg);
    char* afiseaza();
private:
    char* msg;
};


#endif //OOP_EROAREAMEA_H
