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
        for(int i=0;i<width;i++){
            cout<<endl;
            for(int j=0;j<height;j++){
                Pixel pixel = pixels[i][j];
                if(pixel.R == 255 && pixel.G == 255 && pixel.B == 255){
                    cout<<"# ";
                } else{
                    cout<<"@ ";
                }
            }
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
