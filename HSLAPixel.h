#pragma once

namespace cs225
  class HSLAPixel{
      double h, s, l, a;
    public:
      HSLAPixel();
      HSLAPixel(double hue, double saturation, double luminance);
      HLSAPixel(double hue, double saturation, double luminance, double alpha);
    }
