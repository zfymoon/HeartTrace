#include <iostream>
#include "Image.h"
#include "Matrix.h"


Pixel shader(unsigned x, unsigned y){

}
int main() {
    
    unsigned weight = 1024;
    unsigned height = 1024;
    
    Image image(weight,height);
    
    for(unsigned i = 0;i<weight;i++){
        for(unsigned j = 0;j<height;j++){
            Pixel pixel = shader(i,j);
            image.setPixel(pixel,i,j);
        }
    }
    
    image.exportToFile(string("./test.png"));
    
    Matrix<unsigned> matrix(2,2);
    matrix.setItem(1,0,0);
    matrix.setItem(2,0,1);
    matrix.setItem(1,1,0);
    matrix.setItem(1,1,1);
    matrix.dump();
    Matrix<unsigned> next = matrix * matrix;
    next.dump();
    
    return 0;
}
