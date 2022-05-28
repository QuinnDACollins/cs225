#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"

#include <string>
#include <utility>
#include <vector>
using cs225::PNG;
using cs225::HSLAPixel;
void rotate(std::string inputFile, std::string outputFile) {
  PNG* img = new PNG();
  img->readFromFile(inputFile);
  unsigned w = img->width();
  unsigned h = img->height();
  PNG output = PNG(w, h);
  for(unsigned y = 0; y < h; y++){
    for(unsigned x = 0; x < w; x++){
      output.getPixel((w-1) - x, (h-1) - y) =  img->getPixel(x, y);
    }
  }
  output.writeToFile(outputFile);


}

cs225::PNG myArt(unsigned int width, unsigned int height) {
  cs225::PNG png(width, height);
  unsigned x = 0;

  std::vector<std::pair<unsigned, unsigned>>one_coords;
  std::vector<std::pair<unsigned, unsigned>>two_coords;
  std::vector<std::pair<unsigned, unsigned>>three_coords;
  while(5*x <= (height -1)){
   
    one_coords.push_back(std::make_pair(x, 5*x));
    png.getPixel(x, 5*x) = HSLAPixel(0, 0.0, 0.0);
    x += 1;
  }
  x = 0;
  while(-2*x + 500 <= (height -1)){
    two_coords.push_back(std::make_pair(x, -2*x + 500));
    png.getPixel(x, -2*x + 500) = HSLAPixel(0, 0.0, 0.0);
    x += 1;
  }

  x = 0;
  while(1.001*x + 200 <= (height -1)){
    three_coords.push_back(std::make_pair(x, 1.001*x + 200));
    png.getPixel(x, 1.001*x + 200) = HSLAPixel(0, 0.0, 0.0);
    x += 1;
  }

for (auto it = two_coords.rbegin(); it != two_coords.rend(); ++it){
  for(unsigned x = 0; x < it->first; x++){
    
    png.getPixel(x, it->second) = HSLAPixel(x, 1.0, 0.5);
  }
}

for (auto it = two_coords.rbegin(); it != two_coords.rend(); ++it){
  for(unsigned x = it->first; x < it->first + 255; x++){
    
    png.getPixel(x, it->second) = HSLAPixel(255 - x, 1.0, 0.5);
  }
}

for (auto it = three_coords.rbegin(); it != three_coords.rend(); ++it){
  for(unsigned x = it->first; x < width; x++){
    
    png.getPixel(x, it->second) = HSLAPixel(255 - x, 1.0, 0.5);
  }
}

for (auto it = one_coords.rbegin(); it != one_coords.rend(); ++it){
  for(unsigned x = it->first; x < width; x++){
    
    png.getPixel(x, it->second) = HSLAPixel(x, 1.0, 0.5);
  }
}

for (auto it = one_coords.rbegin(); it != one_coords.rend(); ++it){
  for(unsigned x = 0; x < it->first; x++){
    png.getPixel(x, it->second) = HSLAPixel(x * 2, 1.0, x * .01);
  }
}
  return png;
}
