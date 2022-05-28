/* Your code here! */
#include "maze.h"

#include <iostream>
#include <algorithm>
#include <numeric>
#include <iostream>
#include <random>
#include <tuple>
#include <map>
#include <ctime>
SquareMaze::SquareMaze(){

}
void SquareMaze::makeMaze(int width, int height){

    w = width;
    h = height;

    maze.addelements(width * height);

    int i = 0;
    for(int y = 0; y < h; y++){
        for(int x = 0; x < w; x++){
            cells[std::make_tuple(x, y, 0)] = std::make_tuple(i, true);
            cells[std::make_tuple(x, y, 1)] = std::make_tuple(i, true);
            i += 1;
        }
    }

    auto builder = std::vector<std::pair<std::tuple<int, int, int>, std::tuple<int, bool>>>();
    for(auto i = cells.begin(); i != cells.end(); i++){
        builder.push_back(std::make_pair(i->first, i->second));
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(builder.begin(), builder.end(), g);

    int removed = 0;
    
    while(removed != (w*h) - 1){
        bool replace = true;
        
        std::pair<std::tuple<int, int, int>, std::tuple<int, bool>> curr = builder.back();
        builder.pop_back();
        int dir = std::get<2>(curr.first);
        
        int x = std::get<0>(curr.first);
        int y = std::get<1>(curr.first);
        auto other = curr.first;
        if(dir == 0){
            std::get<1>(other) += 1;
        } else if(dir == 1){
            std::get<0>(other) += 1;
        }

        if(cells.find(other) == cells.end()){
            continue;
        }

        int c_par = maze.find(std::get<0>(cells.at(curr.first)));
        int o_par = maze.find(std::get<0>(cells.at(other)));
        if(c_par != o_par){
            maze.setunion(std::get<0>(cells.at(curr.first)), std::get<0>(cells.at(other)));
            
            setWall(x, y, dir, false);
  
            removed += 1;
        }
    }
}
    
bool SquareMaze::canTravel(int x, int y, int dir) const{


    if(dir == 0){
        if(y == h){

            return false;
        }
    }

    if(dir == 1){
        if(x == w){
            return false;
        }
    }
    auto curr = std::make_tuple(x, y, dir);
    if(dir == 2){
        if(x == 0){
            return false;
        }
        curr = std::make_tuple(x - 1, y, dir);
    }else if(dir == 3){
        if(y == 0){
            return false;
        }
        curr = std::make_tuple(x, y - 1, dir);
    }
    return !std::get<1>(curr);
}

void SquareMaze::setWall(int x, int y, int dir, bool exists){

    std::get<1>(cells[std::make_tuple(x, y, dir)]) = exists;
}

std::vector<int> SquareMaze::solveMaze(){
   //Scuffed Iterator TIme.
   /*std::vector<int> sol = std::vector<int>();
   int found = 0;
   int origin = std::get<0>(cells.at(std::make_tuple(0, 0, 0)));
   std::vector<int> bottom = std::vector<int>();
   for(int i = 0; i < w; i++){
       bottom.push_back(std::get<0>(cells.at(std::make_tuple(i, h - 1, 0))));
   }
   while(found == 0){
       int curr = maze.next(origin);
       sol.emplace_back(curr);
       auto it = std::find(bottom.begin(), bottom.end(), curr);
       if(it != bottom.end()){
           found = curr;
       }
   }
   return sol;*/
   return std::vector<int>();



}

cs225::PNG * SquareMaze::drawMaze() const{
    cs225::HSLAPixel black = cs225::HSLAPixel(0, 0, 0, 1);
    cs225::PNG * drawn = new cs225::PNG(w * 10 + 1, h * 10 + 1);
    drawn->getPixel(0, 0) = cs225::HSLAPixel(0, 0, 0, 1);
    for(unsigned i = 10; i < drawn->width(); i++){
        drawn->getPixel(i, 0) = cs225::HSLAPixel(0, 0, 0, 1);
    }

    for(unsigned i = 0; i < drawn->height(); i++){
        drawn->getPixel(0, i) = cs225::HSLAPixel(0, 0, 0, 1);
    }

    for(int y = 0; y < h; y++){
        for(int x = 0; x < w; x++){
            if(std::get<1>(cells.at(std::make_tuple(x, y, 0)))){
                for(unsigned k = 0; k <= 10; k++){
                    drawn->getPixel((x*10) + k, (y+1)*10) = black;
                }
            }
            if(std::get<1>(cells.at(std::make_tuple(x, y, 1)))){
                for(unsigned k = 0; k <= 10; k++){
                    drawn->getPixel(((x+1) * 10), (y*10) + k) = black;
                }
            }
        }
    }

  return drawn;
}
cs225::PNG * SquareMaze::drawMazeWithSolution(){
    return new cs225::PNG();
}

int SquareMaze::getIdx(int x, int y) const{
    return y * x - (w - x);
}

std::pair<int, int> SquareMaze::getCoords(int idx) const{
    int y = floor(idx / w);
    int x = idx - (y * w);
    return std::make_pair(x, y);

}

int SquareMaze::idxPop(std::vector<int>& idx){
    int r = idx.back();
    idx.pop_back();
    return r;
}