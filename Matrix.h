//
// Created by Curie on 2020/2/22.
//

#ifndef HEARTTRACE_MATRIX_H
#define HEARTTRACE_MATRIX_H

#include "Vec.h"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

template<class T>
class Matrix{
public:
    unsigned width;
    unsigned height;
    vector<Vec<T>> vectors;
    Matrix(initializer_list<Vec<T>> list){
        vectors = vector<Vec<T>>(list);
        width = list.size();
        height = vectors[0].size();
    }
    
    Matrix(unsigned width, unsigned height):width(width),height(height){
        vector<T> vl(height);
        vectors = vector<Vec<T>>(width,Vec<T>(vl));
    }
    
    Vec<T> & operator[](unsigned position){
        return vectors[position];
    }
    Matrix<T> operator+(Matrix<T> &other) {
        Matrix<T> result(width, height);
        if (other.width == width && other.height == height) {
            for (int i = 0; i < width; i++) {
                for (int j = 0; j < height; j++) {
                    result[i][j] = vectors[i][j] + other[i][j];
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
                    result[i][j] = vectors[i][j] - other[i][j];
                }
            }
        }
        return result;
    }
    Vec<T> column(unsigned position){
        vector<T > vl(width);
        Vec<T> result(vl);
        for (int i = 0; i < width; i++) {
            result[i] = vectors[i][position];
        }
        return result;
    }
    Matrix<T> operator*(Matrix<T> &other){
        Matrix<T> result(width,other.height);
        if(width == other.height && height == other.width){
            for(int i=0;i<result.width;i++){
                for(int j=0;j<result.height;j++){
                    result[i][j] = vectors[i] * other.column(j);
                }
            }
        }
        return result;
    }
    void dump(){
        cout<<"Matrix("<<width<<" x "<<height<<")"<<endl;
        for(int i=0;i<width;i++){
            cout<<"[ ";
            for(int j=0;j<height;j++){
                cout<<vectors[i][j]<<" ";
            }
            cout<<"]"<<endl;
        }
    }
    
    Matrix<T> invert(){
    
    }
    //获取单位矩阵
    Matrix<T> e(){
        Matrix<T> result(width,height);
        for(int i=0;i<width;i++){
            result[i][i] = 1;
        }
        return result;
    }
    Matrix<T> copy(){
        Matrix<T> result(width,height);
        result.vectors = vectors;
        result.width = result.vectors.size();
        result.height = result.vectors[0].size();
        return result;
    }
    /**
     * LU分解
     * @return
     */
    pair<Matrix<T>,Matrix<T>> LU(){
        Matrix<T> matrix = copy();
        vector<Matrix<T>> list;
        //LU start
        for(int i=0;i<height;i++){
            T startValue = matrix[i][i];
            for(int j=i + 1;j<height;j++){
                Matrix<T> tmpE = e();
                T tmpValue = -(matrix[j][i] / startValue);
                matrix[j] = matrix[j] + (matrix[i] * tmpValue);
                tmpE[j] = tmpE[j] + (tmpE[i] * (-tmpValue));
                list.push_back(tmpE);
            }
        }
        Matrix<T> lResult = list[0];
        int size = list.size();
        for(int i=1;i<size;i++){
            lResult =  lResult * list[i];
        }
        return pair<Matrix<T>,Matrix<T>>(lResult,matrix);
    }
    void LUDump(){
        pair<Matrix<int>,Matrix<int>> r = LU();
        cout<<"L :"<<endl;
        r.first.dump();
        cout<<"U :"<<endl;
        r.second.dump();
    }
    static void test(){
        Matrix<int > matrix{
                {1,2,3},
                {2,5,7},
                {3,5,3}
        };
        matrix.dump();
        matrix.LUDump();
    }
};
#endif //HEARTTRACE_MATRIX_H
