#include <iterator>
#include <cmath>

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"
#include "DFS.h"


/**
 * Initializes a depth-first ImageTraversal on a given `png` image,
 * starting at `start`, and with a given `tolerance`.
 * 
 * @param png The image this DFS is going to traverse
 * @param start The start point of this DFS
 * @param tolerance If the current point is too different (difference larger than tolerance) with the start point,
 * it will not be included in this DFS
 */
DFS::DFS(const PNG & png, const Point & start, double tolerance) {  
  /** @todo [Part 1] */
  canvas = png;

  v = new std::vector<Point>;
  add(start);
  t = tolerance;
  s = start;
  for(unsigned i = 0; i < v->size(); i++){
    std::cout<<(v->at(i))<<std::endl;
  }
}

DFS::~DFS(){
  v->clear();
  delete v;
}

/**
 * Returns an iterator for the traversal starting at the first point.
 */
ImageTraversal::Iterator DFS::begin() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator(this, canvas, t, s);
}

/**
 * Returns an iterator for the traversal one past the end of the traversal.
 */
ImageTraversal::Iterator DFS::end() {
  /** @todo [Part 1] */
  return ImageTraversal::Iterator();
}

/**
 * Adds a Point for the traversal to visit at some point in the future.
 */
void DFS::add(const Point & point) {
  /** @todo [Part 1] */
  v->emplace_back(Point(point.x, point.y));
}

/**
 * Removes and returns the current Point in the traversal.
 */
Point DFS::pop() {
  /** @todo [Part 1] */
  Point val = v->back();
  if(!v->empty()){
    v->pop_back();
  }
  return val;
}

/**
 * Returns the current Point in the traversal.
 */
Point DFS::peek() const {
  /** @todo [Part 1] */
  return v->back();
}

/**
 * Returns true if the traversal is empty.
 */
bool DFS::empty() const {
  /** @todo [Part 1] */
  return v->empty();
}


