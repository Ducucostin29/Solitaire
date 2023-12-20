//
// Created by User on 12/20/2023.
//

#ifndef OOP_MYVECTOR_H
#define OOP_MYVECTOR_H
#include <cstdlib>
#include <ostream>
#include "EroareaMea.h"

template <typename  T>class MyVector {
private:
    T* point;
    size_t n{};
public:
    MyVector(){
        this->point= nullptr;
        this->clear();
    }
    ~MyVector() {
        this->clear();
    };
    void clear(){
        if (this->point != nullptr)
            free(this->point);
        this->point= (T*) calloc(0,sizeof (T));
        this->n=0;
    }
    void push_back(T obj){
        this->point=(T*)realloc(this->point,sizeof(T) * (this->n +1));

        this->n++;
        this->point[this->n-1]=obj;
    }
    friend std::ostream &operator<<(std::ostream &out, const MyVector<T> myVector){
        for(int i=0;i<myVector.n;i++)
            out << "  " << myVector.point[i];
        return out;
    }

    T operator [](size_t i) const {
        if( i >= this->n) throw EroareaMea<char*>((char*) "Imposibil \n");
        return this->point[i];
    }
    bool empty(){
        return this->n==0;
    }
    T back(){
        if(this->empty())throw EroareaMea<char*>((char*) "Imposibil \n");
        return this->point[n-1];
    }

    [[nodiscard]] size_t size() const {
        return this->n;
    }

};


#endif //OOP_MYVECTOR_H
