//
// Created by Curie on 2020/2/22.
//

#ifndef HEARTTRACE_MATRIX_H
#define HEARTTRACE_MATRIX_H

#include "Vec.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

template<class T>
class Matrix{
private:
    double  detCache = 0;
    bool detCacheFlag = false;
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
    /**
     * 逆矩阵
     * @return
     */
    Matrix<T> Invert(){
        Matrix<T> result= Adjugate();
        double value = det();
        //result.dump();
        for(int i=0;i<width;i++){
            for(int j=0;j<height;j++){
                result[i][j] = result[i][j] / (value + 0.0);
            }
        }
        return result;
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
    Matrix<T> LUInvert(){
        pair<Matrix<T>,Matrix<T>> luResult = LU();
        Matrix<T> lInvert = luResult.first.Invert();
        Matrix<T> uInvert = luResult.second.Invert();
        return uInvert * lInvert;
    }
    void LUDump(){
        pair<Matrix<int>,Matrix<int>> r = LU();
        cout<<"L :"<<endl;
        r.first.dump();
        cout<<"U :"<<endl;
        r.second.dump();
    }
    /**
     * 计算行列式
     * @return
     */
    double det(){
        if(detCacheFlag){
            return detCache;
        }
        if(this->width == 2 && this->height == 2){
            return vectors[0][0]*vectors[1][1] - vectors[0][1]*vectors[1][0];
        }
        double result = 0;
        for(int i=0;i<width;i++){
            T tmpValue = vectors[0][i];
            result += tmpValue == 0 ? 0 : pow(-1,i+2)*tmpValue *  M(0,i).det();
        }
        detCacheFlag = true;
        detCache = result;
        return result;
    }
    /**
     * 转置矩阵
     * @return
     */
    Matrix<T> TFunc(){
        Matrix<T> result(height,width);
        for(int i=0;i<result.width;i++){
            for(int j=0;j<result.height;j++){
                result[i][j] = vectors[j][i];
            }
        }
        return result;
    }
    /**
     * 伴随矩阵
     * @return
     */
    Matrix<T> Adjugate(){
        Matrix<T> result(width,height);
        for(int i=0;i<width;i++){
            for(int j=0;j<height;j++){
                result[i][j] = pow(-1,i+j+2) * M(i,j).det();
            }
        }
        return result.TFunc();
    }
    Matrix<T> M(unsigned positionX, unsigned positionY){
        Matrix<T> result(width-1,height-1);
        for(int i=0;i<width;i++){
            for(int j=0;j<height;j++){
                if(i != positionX && j != positionY ){
                    result[i >= positionX ? i-1 : i][ j >= positionY ? j-1 :j]
                    = vectors[i][j];
                }
            }
        }
        return result;
    }
    static void test(){
        
        //测试LU分解
        Matrix<int > matrix{
                {1,2,3},
                {2,5,7},
                {3,5,3}
        };
        matrix.LUDump();
        
        //测试行列式
        Matrix<int > detMatrix{
                {5,-5,1,3,0},
                {3,2,4,4,3},
                {4,-1,-2,-3,2},
                {0,-3,4,3,3},
                {0,2,-2,2,4}
        };
        cout<<detMatrix.det()<<endl;
        
        //测试伴随矩阵
        Matrix<int > adjMatrix{
                {-3,2,-5},
                {-1,0,-2},
                {3,-4,1}
        
        };
        adjMatrix.Adjugate().dump();
        
        //测试逆矩阵
        Matrix<double > invertMatrix = {
                {1,4,3},
                {-1,-2,0},
                {2,2,3}
        };
        invertMatrix.Invert().dump();
        invertMatrix.LUInvert().dump();
    }
    
    
};
#endif //HEARTTRACE_MATRIX_H
