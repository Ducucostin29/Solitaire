//
// Created by User on 12/20/2023.
//

#ifndef OOP_MYLIST_H
#define OOP_MYLIST_H
#include <cstdlib>
#include "EroareaMea.h"
#include <ostream>

template <typename T> class MyNode {
public:
    MyNode<T> * next;
    T value;
    explicit MyNode(T value){
        this->next = nullptr;
        this->value = value ;
    }
};


template <typename T>class MyList {
private:
    MyNode<T>* start;
    MyNode<T>* end;
    size_t n{};
public:
    explicit MyList(){
        this->n = 0;
        this->start = nullptr;
        this->end = nullptr;
    }
    ~MyList(){
        this->clear();
    }
    bool empty(){
        return this->n==0;
    }
    void push_back(T obj){
        if(end== nullptr){
            this->start=new MyNode<T>(obj);
            this->end=this->start;
        }else{
            MyNode<T> *old = this->end;
            this->end=new MyNode<T>(obj);
            old->next = this->end;
        }
        this->n++;
    }
    void clear(){
        MyNode<T> *it = this->start;
        while (it != nullptr){
            MyNode<T> *aux = it->next;
            delete it;
            it = aux;
        }
    }

    friend std::ostream &operator<<(std::ostream &out, const MyList<T> &myList){
        MyNode<T> *it = myList.start;
        while (it != nullptr) {
            out << "  " << it->value;
            it=it->next;
        }
        return out;
    }

    T operator [](size_t i) const {
        if( i >= this->n) throw EroareaMea<char*>((char*) "Imposibil \n");
        MyNode<T> *it = this->start;
        while (it != nullptr){
            if ( i == 0 )
                return it->value;
            it = it->next;
            i--;
        }
    }

    T back(){
        if(this->empty())throw EroareaMea<char*>((char*) "Imposibil \n");
        return this->end->value;
    }

    [[nodiscard]] size_t size() const {
        return this->n;
    }

};


#endif //OOP_MYLIST_H
