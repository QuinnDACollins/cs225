#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

 
  Image pooh; pooh.readFromFile("a.png");
  pooh.scale(2);
  StickerSheet pooh_pants(pooh, 2);
  Image pooh_stick_1; pooh_stick_1.readFromFile("a.png");
  Image pooh_stick_2; pooh_stick_2.readFromFile("a.png");

  pooh_stick_1.scale(0.7);
  pooh_pants.addSticker(pooh_stick_1, pooh.width() * .6, 100);

  pooh_stick_2.scale(0.3);
  pooh_stick_2.rotateColor(190);
  pooh_pants.addSticker(pooh_stick_2, pooh.width() * .8, 90);

  pooh_pants.render().writeToFile("myImage.png");

  return 0;
}
