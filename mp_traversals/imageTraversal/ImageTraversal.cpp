#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

using namespace std; 
#include <vector> 
#include <list> 
#include <stack> 
#include <queue> 

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  traversal_ = NULL;
}

bool ImageTraversal::inBounds(Point &p1, const Point &p2, double tolerance, PNG &canvas){
  if(p2.x >= canvas.width() || p2.x < 0 || p2.y >= canvas.height() || p2.y < 0){
    return false;
  }
  if(calculateDelta(canvas.getPixel(p1.x, p1.y), canvas.getPixel(p2.x, p2.y)) >= tolerance){
    return false;
  }

  return true;
}
/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator(ImageTraversal * trav, PNG canvas, double tolerance, Point start) {
  start_ = start;
  canvas_ = canvas;
  tolerance_ = tolerance;
  traversal_ = trav;
  current_ = start;

  visited_.resize(canvas.width(), vector<bool>(canvas.height(), false));
}
/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  if(traversal_->empty()){
    Point pop = traversal_->pop();
    pop = traversal_->pop();
    current_ = pop;
  }

  visited_[current_.x][current_.y] = true;

  HSLAPixel startPixel = canvas_.getPixel((start_.x),(start_.y));
  HSLAPixel tempPixel;
  Point below = Point(current_.x, current_.y + 1);
  Point left =  Point(current_.x - 1, current_.y);
  Point above = Point(current_.x, current_.y - 1);
  Point right = Point(current_.x + 1, current_.y);



  std::vector<Point> neighbors {above, left, below, right};
  while(!neighbors.empty()){
    if(inBounds(start_, neighbors.back(), tolerance_, canvas_)){
      traversal_->add(neighbors.back());
    }
    neighbors.pop_back();
  }
  neighbors.clear();

  while(!traversal_->empty()){
    if(visited_[traversal_->peek().x][traversal_->peek().y] == true){
      traversal_->pop();
    } else {
      break;
    }
  }
    
  
  if(!traversal_->empty())
    current_ = traversal_->peek();
  
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */

Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return traversal_->peek();
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  bool thisEmpty = false; 
  bool otherEmpty = false;

  if (traversal_ == NULL)
    thisEmpty = true; 
  if (other.traversal_ == NULL)
    otherEmpty = true;

  if (!thisEmpty)
    thisEmpty = traversal_->empty();
  if (!otherEmpty)
    otherEmpty = other.traversal_->empty();

  if (thisEmpty && otherEmpty) 
    return false; // 
  else if (!thisEmpty && !otherEmpty) 
    return (traversal_ != other.traversal_);
  else 
    return true;
}

