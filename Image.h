//
// Created by Curie on 2020/2/22.
//

#ifndef HEARTTRACE_IMAGE_H
#define HEARTTRACE_IMAGE_H

#include <vector>
#include <iostream>
#include <fstream>

/**
 * 图片输出为PPM P3格式，便于阅读
 * 格式：P3 w h max_color [r g b] [r g b] ...
 */

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
    double width;
    double height;
    Image(double w, double h){
        width = w;
        height = h;
        pixels = vector<vector<Pixel>>(w,vector<Pixel>(h));
    }
    void setPixel(const Pixel & pixel, double x, double y){
        if(x < width && y < height  ){
            pixels[x][y] = pixel;
        }
    }
    Image reverse(){
        Image result(width,height);
        for(int i=0;i<width;i++){
            for(int j=0;j<height;j++){
                result.setPixel(pixels[j][i],i,j);
            }
        }
        return result;
    }
    
    void print(){
        exportToFile("./m.png");
        
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
        fs<<"P3 "<<width<<" "<<height<<" 255 ";
        for(int i=0;i<width;i++){
            for(int j=0;j<height;j++){
                Pixel pixel = pixels[i][j];
                fs<<pixel.R<<" "<<pixel.G<<" "<<pixel.B<<" ";
            }
        }
        fs.flush();
    }
};


#endif //HEARTTRACE_IMAGE_H
