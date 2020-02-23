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
    Vec(initializer_list<T> list){
        items = vector<T>(list);
    }
    explicit Vec(vector<T> list){
        items = list;
    }
    
    [[nodiscard]] size_t size() const{
        return items.size();
    }
    
    Vec<T> operator+( const Vec<T> & other){
        size_t length = size();
        if(length ==  other.size()){
            vector<T> result;
            for(int i=0;i<length;i++){
                result.push_back(other[i] + items[i]);
            }
            return Vec<T>(result);
        } else{
            throw logic_error("Size not match");
        }
    }
    Vec<T> operator-( const Vec<T> & other){
        size_t length = size();
        if(length ==  other.size()){
            vector<T> result;
            for(int i=0;i<length;i++){
                result.push_back(other[i] - items[i]);
            }
            return Vec<T>(result);
        } else{
            throw logic_error("Size not match");
        }
    }
    Vec<T> operator*(double val){
        
        Vec<T> result(items);
        size_t length = size();
        for(int i=0;i<length;i++){
            result[i] *= val;
        }
        return result;
    }
    T & operator[](unsigned position){
        return items[position];
    }
    Vec<T> copy(){
       return Vec<T>(items);
    }
    double operator*(const Vec<T> & other){
        size_t length = size();
        if(length == other.size()){
            double result = 0;
            for(int i=0;i<length;i++){
                result += (items[i] * other[i]);
            }
            return result;
        } else{
            throw logic_error("Size not match");
        }
    }
    const T & operator[](unsigned position) const{
        return items[position];
    }
    void dump(){
        cout<<"Vector("<<size()<<")"<<endl;
        cout<<"[ ";
        for(auto & item : items ){
            cout<<item<<" ";
        }
        cout<<"]"<<endl;
    }
};


#endif //HEARTTRACE_VEC_H
