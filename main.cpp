#include <iostream>
#include "Image.h"
#include "matrix/Matrix.h"
#include "matrix/Vec.h"
#include <cmath>


//对图片坐标进行转换

Pixel shader(double x, double y, double centerX, double centerY, double r){
    if(sqrt(pow(x - centerX,2) + pow(y - centerY,2)) <= r){
        return Pixel{
            0,238,118,255
        };
    } else{
        return Pixel{
            255,255,255,255
        };
    }
}
int main() {
    Image image(4096,4096);
    Matrix<double > imageTransMatrix = {
            {1,0,0},
            {0,-1,image.height},
            {0,0,0}
    };
    //行向量右乘，所以需要转置
    imageTransMatrix = imageTransMatrix.TFunc();
    for(double i = 0;i<=image.width;i++){
        for(double j = 0;j<=image.height;j++){
            Vec<double > tmpVec = Matrix<double >::point(Vec<double >{
                    {i + 0.0,j+0.0,1}
            },imageTransMatrix);
            Pixel pixel = shader(tmpVec[0],tmpVec[1],700,700,500);
            image.setPixel(pixel,i,j);
        }
    }
    image.reverse().print();
    
    return 0;
}
