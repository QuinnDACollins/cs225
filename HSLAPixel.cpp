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