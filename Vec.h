//
// Created by Curie on 2020/2/22.
// 向量

#ifndef HEARTTRACE_VEC_H
#define HEARTTRACE_VEC_H

#include <vector>
#include <iostream>

using namespace std;

template <class T>
class Vec{
private:
    vector<T> items;
public:
    unsigned  length;
    Vec(unsigned size){
        this->length = size;
        items = vector<T>(size);
    }
    Vec(vector<T> originalList){
        items.clear();
        items.insert(originalList.end(),originalList.begin(),originalList.end());
        length = items.size();
    }
    Vec(initializer_list<T> list){
        items.insert(list.end(),list.begin(),list.end());
        length = items.size();
    }
    void setItem(unsigned position,T item){
        if(position < length) {
            items[position] = item;
        }
    }
    T getItem(unsigned position){
        if(position < length){
            return items[position];
        } else{
            return nullptr;
        }
    }
    
    Vec<T> operator+(const Vec<T> & other){
        if(length ==  other.length){
            vector<T> result(length);
            for(int i=0;i<length;i++){
                result[i] = other[i] + getItem(i);
            }
            return Vec(result);
        } else{
            return nullptr;
        }
    }
    void dump(){
        cout<<"Vector("<<length<<")"<<endl;
        cout<<"[ ";
        for(auto & item : items ){
            cout<<item<<" ";
        }
        cout<<"]";
    }
};


#endif //HEARTTRACE_VEC_H
