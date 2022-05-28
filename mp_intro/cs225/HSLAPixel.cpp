/**
 * @file HSLAPixel.cpp
 * Implementation of the HSLAPixel class for use in with the PNG library.
 *
 * @author CS 225: Data Structures
 * @version 2018r1-lab1
 */

#include "HSLAPixel.h"
#include <cmath>
#include <iostream>
using namespace std;

namespace cs225{
  HSLAPixel::HSLAPixel() {
    //Only need these two to be 100% for white color
    a = 1.0;
    l = 1.0;
    //-
    s = 0.0;
    h = 0.0;
    
  }

HSLAPixel::HSLAPixel(double hue, double saturation, double luminance){
  a = 1.0;
  s = saturation;
  l = luminance;
  h = hue;
}

HSLAPixel::HSLAPixel(double hue, double saturation, double luminance, double alpha){
  a = alpha;
  s = saturation;
  l = luminance;
  h = hue;
  }
}
