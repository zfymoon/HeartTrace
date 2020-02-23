#include <iostream>
#include "Image.h"
#include "Matrix.h"
#include "Vec.h"
#include <stack>


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
    
   Matrix<int >::test();
    
   // (e * matrix).dump();
   
   
    
    //求第一个消元矩阵
    
    image.exportToFile(string("./test.png"));
   
    
    return 0;
}
