/* Your code here! */
#pragma once
#include "cs225/PNG.h"
#include "dsets.h"
#include <map>
class SquareMaze {
    public:
        SquareMaze();
        void makeMaze(int width, int height);
        bool canTravel(int x, int y, int dir) const;
        void setWall(int x, int y, int dir, bool exists);
        std::vector<int> solveMaze();
        cs225::PNG * drawMaze() const;
        cs225::PNG * drawMazeWithSolution();
    private:
        int getIdx(int x, int y) const;
        std::pair<int, int> getCoords(int idx) const;
        int idxPop(std::vector<int>& idx);
        int w;
        int h;
        DisjointSets maze;
        std::map<std::tuple<int, int, int>, std::tuple<int, bool>> cells;

};