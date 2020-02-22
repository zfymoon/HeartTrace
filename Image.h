//
// Created by Curie on 2020/2/22.
//

#ifndef HEARTTRACE_IMAGE_H
#define HEARTTRACE_IMAGE_H

#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

struct Pixel{
    int R;
    int G;
    int B;
    int A;
};
class Image {
private:
    vector<vector<Pixel>> pixels;
public:
    unsigned width;
    unsigned height;
    Image(unsigned w, unsigned h){
        width = w;
        height = h;
        pixels = vector<vector<Pixel>>(w,vector<Pixel>(h));
    }
    void setPixel(const Pixel & pixel, unsigned x, unsigned y){
        if(x < width && y < height  ){
            pixels[x][y] = pixel;
        }
    }
    void exportToFile(const string & path){
        ofstream  fs;
        fs.open(path,ios::out);
        if(!path.ends_with(".png")){
            cerr<<"Path should end with png"<<endl;
        }
        if(!fs.is_open()){
            cerr<<"Can not open file"<<endl;
        }
        //write width height
        fs.write(to_string(0x4d42).c_str(),1);
        fs.write(to_string(width * height).c_str(),1);
        fs.flush();
    }
};


#endif //HEARTTRACE_IMAGE_H
