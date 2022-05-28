/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once

#include "Image.h"
#include <utility>

class StickerSheet {
    public:
        StickerSheet(const Image &picture, unsigned max);
        ~StickerSheet();
        StickerSheet(const StickerSheet &other);
        const StickerSheet & operator=(const StickerSheet &other);
        void drawSticker(std::pair<Image, std::pair<unsigned, unsigned>>);
        void changeMaxStickers(unsigned max);
        int addSticker(Image &sticker, unsigned x, unsigned y);
        bool translate(unsigned index, unsigned x, unsigned y);
        void removeSticker(unsigned index);
        Image * getSticker(unsigned index);
        Image render() const;
    private:
        Image *scene;
        Image nullstkr;
        Image *o_scene;
        void copy(const StickerSheet &other);
        void clear();
        int max_stickers;
        std::pair<Image, std::pair<unsigned, unsigned>>* sheet;
        };


 
