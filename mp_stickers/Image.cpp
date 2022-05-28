#include "Image.h"
#include <cmath>

void Image::darken(){
    for(unsigned y = 0; y < height(); y++){
        for(unsigned x = 0; x < width(); x++){
            if(getPixel(x, y).l >= 0.1){
                getPixel(x, y).l -= 0.1;
            } else {
                getPixel(x, y).l = 0.0;
            }
        }
    }
}

void Image::darken(double amount){
    for(unsigned y = 0; y < height(); y++){
        for(unsigned x = 0; x < width(); x++){
            if(getPixel(x, y).l  - amount >= 0.0){
                getPixel(x, y).l -= amount;
            } else {
                getPixel(x, y).l = 0.0;
            }
        }
    }
}

void Image::desaturate(){
    for(unsigned y = 0; y < height(); y++){
        for(unsigned x = 0; x < width(); x++){
            if(getPixel(x, y).s >= 0.1){
                getPixel(x, y).s -= 0.1;
            } else {
                getPixel(x, y).s = 0.0;
            }
        }
    }
}

void Image::desaturate(double amount){
    for(unsigned y = 0; y < height(); y++){
        for(unsigned x = 0; x < width(); x++){
            if(getPixel(x, y).s >= amount){
                getPixel(x, y).s -= amount;
            } else {
                getPixel(x, y).s = 0.0;
            }
        }
    }
}

void Image::grayscale(){
    for(unsigned y = 0; y < height(); y++){
        for(unsigned x = 0; x < width(); x++){
            getPixel(x, y).s = 0.0;
        }
    }
}

void Image::illinify(){
    for(unsigned y = 0; y < height(); y++){
        for(unsigned x = 0; x < width(); x++){
    
            double orange_dist = 180.0 - std::fabs(std::fmod(std::fabs(11 - getPixel(x, y).h), 360.0) - 180.0);
            double blue_dist = 180.0 - std::fabs(std::fmod(std::fabs(216 - getPixel(x, y).h), 360.0) - 180.0);
            if (orange_dist < blue_dist){
                getPixel(x, y).h = 11;
            } else {
                getPixel(x, y).h = 216;
            }
        }
    }    
}
void Image::lighten(){
    for(unsigned y = 0; y < height(); y++){
        for(unsigned x = 0; x < width(); x++){
            if(getPixel(x, y).l <= 0.9){
                getPixel(x, y).l += 0.1;
            } else {
                getPixel(x, y).l = 1.0;
            }
        }
    }
}

void Image::lighten(double amount){
    for(unsigned y = 0; y < height(); y++){
        for(unsigned x = 0; x < width(); x++){
            if(getPixel(x, y).l + amount <= 1.0){
                getPixel(x, y).l += amount;
            } else {
                getPixel(x, y).l = 1.0;
            }
        }
    }
}

void Image::rotateColor(double degrees){
    for(double y = 0; y < height(); y++){
        for(double x = 0; x < width(); x++){
            getPixel(x, y).h += degrees;
            if(getPixel(x, y).h > 360.0){
                getPixel(x, y).h -= 360;
            } else if(getPixel(x, y).h < 0){
                getPixel(x, y).h += 360;
            }
        }
    }
}

void Image::saturate(){
    for(unsigned y = 0; y < height(); y++){
        for(unsigned x = 0; x < width(); x++){
            if(getPixel(x, y).s <= 0.9){
                getPixel(x, y).s += 0.1;
            } else {
                getPixel(x, y).s = 1.0;
            }
        }
    }
}

void Image::saturate(double amount){
    for(unsigned y = 0; y < height(); y++){
        for(unsigned x = 0; x < width(); x++){
            if(getPixel(x, y).s + amount <= 1.0){
                getPixel(x, y).s += amount;
            } else {
                getPixel(x, y).s = 1.0;
            }
        }
    }
}

void Image::scale(double factor){
    double newWidth = width() * factor;
    double newHeight = height() * factor;
    Image old = *this;
    resize(newWidth, newHeight);
    for(unsigned y = 0; y < newHeight; y++){
        for(unsigned x = 0; x < newWidth; x++){
            int scaleX = floor((old.width() * (x / newWidth)));
            int scaleY = floor((old.height() * (y / newHeight)));
            getPixel(x, y) = old.getPixel(scaleX, scaleY);
         }
    }
}

void Image::scale(unsigned w, unsigned h){
    double newWidth = (double) w;
    double newHeight =(double) h;
    Image * old = new Image(*this);
    resize(newWidth, newHeight);
    for(double y = 0; y < newHeight; y++){
        for(double x = 0; x < newWidth; x++){
            int scaleX = floor((old->width() * (x / newWidth)));
            int  scaleY = floor((old->height() * (y / newHeight)));
            getPixel(x, y) = old->getPixel(scaleX, scaleY);
         }
    }
}