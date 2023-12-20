//
// Created by User on 11/14/2023.
//

#ifndef OOP_EROAREAMEA_H
#define OOP_EROAREAMEA_H

#include <exception>

template <typename  T> class EroareaMea : public std::exception{
public:
    explicit EroareaMea(T msg){
        this->mesaj = msg;
    };
    T afiseaza(){
        return this->mesaj;
    }
private:
    T mesaj;
};


#endif //OOP_EROAREAMEA_H
