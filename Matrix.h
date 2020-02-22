//
// Created by Curie on 2020/2/22.
//

#ifndef HEARTTRACE_MATRIX_H
#define HEARTTRACE_MATRIX_H

#include <vector>
#include <iostream>
using namespace std;

template<class T>
class Matrix{
private:
    vector<vector<T>> items;
public:
    unsigned width;
    unsigned height;
    Matrix(unsigned w, unsigned h){
        width = w;
        height = h;
        items = vector<vector<T>>(w,vector<T>(h));
    }
    void setItem(const T & item, unsigned x, unsigned y){
        if(x < width && y < height){
            items[x][y] = item;
        }
    }
    T  getItem(unsigned x, unsigned y){
        return items[x][y];
    }
    vector<T> getRow(unsigned x){
        return items[x];
        
    }
    vector<T> getColumn(unsigned y){
        vector<T> result;
        for(int i=0;i<width;i++){
            result.push_back(items[i][y]);
        }
        return result;
    }
    void dump(){
        cout<<"Matrix("<<width<<" x "<<height<<")"<<endl;
        for(int i=0;i<width;i++){
            cout<<"[ ";
            for(int j=0;j<height;j++){
                cout<<items[i][j]<<" ";
            }
            cout<<"]"<<endl;
        }
    }
    
    Matrix<T> operator+(Matrix<T> &other) {
        Matrix<T> result(width, height);
        if (other.width == width && other.height == height) {
            for (int i = 0; i < width; i++) {
                for (int j = 0; j < height; j++) {
                    result.setItem(getItem(i, j) + other.getItem(
                            i, j
                    ), i, j);
                }
            }
        }
        return result;
    }
    Matrix<T> operator-(Matrix<T> &other){
        Matrix<T> result(width, height);
        if (other.width == width && other.height == height) {
            for (int i = 0; i < width; i++) {
                for (int j = 0; j < height; j++) {
                    result.setItem(getItem(i, j) - other.getItem(
                            i, j
                    ), i, j);
                }
            }
        }
        return result;
    }
    
    Matrix<T> operator*(Matrix<T> &other){
        Matrix<T> result(width,other.height);
        if(width == other.height && height == other.width){
            for(int i=0;i<result.width;i++){
                for(int j=0;j<result.height;j++){
                    result.setItem(getItem(i,j) * other.getItem(j,i),i,j);
                }
            }
            
        }
        return result;
    }
};
#endif //HEARTTRACE_MATRIX_H
