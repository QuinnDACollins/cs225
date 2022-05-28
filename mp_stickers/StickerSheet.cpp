#include "StickerSheet.h"
#include "Image.h"
#include <utility>

StickerSheet::StickerSheet(const Image & picture, unsigned max){
    max_stickers = max;
    scene = new Image(picture);
    o_scene = new Image(picture);
    sheet = new std::pair<Image, std::pair<unsigned, unsigned>>[max_stickers];
    nullstkr = Image();
}

StickerSheet::~StickerSheet(){
    clear();
}

StickerSheet::StickerSheet(const StickerSheet &other){
    copy(other);

}

const StickerSheet &StickerSheet::operator=(const StickerSheet &other){
    if(this != &other){
        clear();
        copy(other);
    }
    return *this;  
}


void StickerSheet::copy(const StickerSheet &other){
    max_stickers = other.max_stickers;
    scene = new Image(*other.scene);
    sheet = new std::pair<Image, std::pair<unsigned, unsigned>>[max_stickers];
    o_scene = new Image(*other.o_scene);
    for(int x = 0;  x < max_stickers; x++){
        sheet[x] = other.sheet[x];
    }
}


void StickerSheet::clear(){
    delete[] sheet;
    delete scene;
    delete o_scene;
}

void StickerSheet::changeMaxStickers(unsigned max){
    //Set the new max
    //Make a copy of the old sheet
  
    int  old_max = max_stickers;

    std::pair<Image, std::pair<unsigned, unsigned>> *old_sheet = new std::pair<Image, std::pair<unsigned, unsigned>>[old_max];
    for(int i = 0; i < old_max; i++){
        old_sheet[i] = std::make_pair(sheet[i].first, std::make_pair(sheet[i].second.first, sheet[i].second.second));
    }  

    max_stickers = max;

    sheet = new std::pair<Image, std::pair<unsigned, unsigned>>[max_stickers];
    //Make a new sheet with the new max
    
    //Set our current sheet equal to the new sheet
    std::cout << max_stickers << std::endl;
    for(int i = 0; i < old_max; i++){
        if(i >= max_stickers){
            break;
        }
        sheet[i] = std::make_pair(old_sheet[i].first, std::make_pair(old_sheet[i].second.first, old_sheet[i].second.second));
    }  
    
  
    


}


int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y){
    for(int i = 0; i < max_stickers; i++){
        if(sheet[i].first == nullstkr){
            sheet[i] = std::make_pair(sticker, std::make_pair(x, y));
            return i;
        }
    }
    return 0;
}



bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
    if((int)index <= max_stickers){
        if(sheet[index].first != nullstkr){
            sheet[index].second = std::make_pair(x, y);
        return true;
        }
    }
    
    return false;
}

void StickerSheet::removeSticker(unsigned index){

   sheet[index].first = nullstkr;
}

Image* StickerSheet::getSticker(unsigned index){
    if((int)index <= max_stickers){
        if(sheet[index].first != nullstkr){
            return &sheet[index].first;
        }
    }
    return NULL;
}

Image StickerSheet::render() const{
    int max_w = scene->width();
    int max_h = scene->height();
    if(max_stickers == 0){
        *scene = *o_scene;
        return *scene;
    }
    for(int i = 0; i < max_stickers; i++){
        if((int)sheet[i].first.width() + (int)sheet[i].second.first > max_w){
            max_w = sheet[i].first.width() + sheet[i].second.first;
        }

        if((int)sheet[i].first.height() + (int)sheet[i].second.second > max_h){
            max_h = sheet[i].first.height() + sheet[i].second.second;
        }
    }
    if(max_w > (int)scene->width()){
        scene->scale(scene->width() + (max_w - scene->width()), scene->height());
    } else if(scene->width() != o_scene->width()){
        *scene = *o_scene;
    }

    if(max_h > (int)scene->height()){
        scene->scale(scene->width(), scene->height() + (max_h - scene->height()));
    } else if(scene->height() != o_scene->height()){
        *scene = *o_scene;
    }


    for(int i = 0; i < max_stickers; i++){
        if(sheet[i].first != nullstkr){
            int sticker_x = sheet[i].second.first;
            int sticker_y = sheet[i].second.second;
        
            int sticker_h = sheet[i].first.height();
            int sticker_w = sheet[i].first.width();

            int y_sticker_bound = (sheet[i].first.height()) + sticker_y;
            int x_sticker_bound = (sheet[i].first.width()) + sticker_x;
            


            if((sticker_h + sticker_y) > (int)scene->height()){
                scene->scale(scene->width(), scene->height() + ((sticker_y+sticker_h) - scene->height()));
            }

            for(int y = sticker_y; y < sticker_y + sticker_h; y++){
                if(y >= (int)scene->height()){
                    break;
                }
                for(int x = sticker_x; x <  sticker_x + sticker_w; x++){
                    if(x >= (int)scene->width()){
                        break;
                    }
                    if(sheet[i].first.getPixel((x - sticker_x) , (y  - sticker_y)).a > 0.0) {

                        scene->getPixel(x, y) = sheet[i].first.getPixel(x - sticker_x , y - sticker_y);
                    } 
                }
            }
        }
        }
    return *scene;
}

