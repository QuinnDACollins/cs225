#include "../cs225/HSLAPixel.h"
#include "../Point.h"
#include <stdlib.h>
#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  if(rand() % 100 == 2){
    return HSLAPixel(59, 1, .79, 1);
  }  else {
     return HSLAPixel(224, 1, .11, 1);
  }
 
}
