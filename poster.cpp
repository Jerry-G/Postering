#include <iostream>
#include <string> 
#include "CImg.cpp"
using namespace cimg_library;


int main(int argc, char* argv[]) {

  if(argc < 5){
    printf("Usage: poster image xtimes ytimes output\n");
    return 1;
  }

  int xtimes = std::stoi(argv[2]);
  int ytimes = std::stoi(argv[3]);


  CImg<double> image (argv[1]);
  int width = image.width();
  int height = image.height();
  CImg<double> greyscale(width,height,1,1,0);
  CImg<double> tile(width/xtimes,height/ytimes,1,1,0);
  CImg<double> result(width,height,1,3,0);

  int tileWidth = tile.width();
  int tileHeight = tile.height();

  for (int i = 0; i < width/xtimes; ++i) {
    for (int j = 0; j < height/ytimes; ++j) {
      double R = image(i*xtimes,j*ytimes,0,0);
      double G = image(i*xtimes,j*ytimes,0,1);
      double B = image(i*xtimes,j*ytimes,0,2);
      double value = (0.299*R+0.587*G+0.114*B);
      greyscale(i,j,0,0) = value;
      //(value<255/2)?value=0:value=255;
      value+=255/3;
      (value>255)?value=255:value+=0;
      tile(i,j,0,0) = value;
    }
  }

  for (int i = 0; i < width; ++i) {
    for (int j = 0; j < height; ++j) {
      result(i, j,0,0) = tile(i%tile.width(), j%tile.height(),0,0) * image(i,j,0,0);
      result(i, j,0,1) = tile(i%tile.width(), j%tile.height(),0,0) * image(i,j,0,1);
      result(i, j,0,2) = tile(i%tile.width(), j%tile.height(),0,0) * image(i,j,0,2);
    }
  }

  result.save(argv[4]);


  return 0;
}


