#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <3ds.h>
#include <time.h>
#include <math.h>
#include <sf2d.h>
#include <sfil.h>
#include "display.h"
#include "drawable.h"

#include "imac_png.h"
#include "background_png.h"

using namespace std;

//adress of the 3DS depth slider
#define CONFIG_3D_SLIDERSTATE (*(float *)0x1FF81080)


int main()
{

  std::vector<Drawable> drawableVec;
  sf2d_init();
  sf2d_set_clear_color(RGBA8(0x40, 0x40, 0x40, 0xFF));
  sf2d_set_3D(true);

  Drawable player = Drawable(200, 200, sfil_load_PNG_buffer(imac_png, SF2D_PLACE_RAM), GFX_TOP);
  Drawable background = Drawable(0, 0, sfil_load_PNG_buffer(background_png, SF2D_PLACE_RAM), GFX_TOP);

  drawableVec.push_back(background);
  drawableVec.push_back(player);

  float rad = 0.0f;

  u16 touch_x = 320/2;  // we center these values
  u16 touch_y = 240/2;

  touchPosition touch;    //stylus position
  circlePosition circle;  //joystick position
  u32 held;
  u32 pressed;

  while(aptMainLoop()){

    hidScanInput();
    hidCircleRead(&circle);
    held = hidKeysHeld();
    pressed = hidKeysDown();

    //start to exit homebrew
    if(held & KEY_START){
      break;
    }

    //touchscreen to change touch coordinates
    if(held & KEY_TOUCH){
      hidTouchRead(&touch);
      touch_x = touch.px;
      touch_y = touch.py;
    }

    //triggers to randomly change background color
    if(pressed & (KEY_L | KEY_R)){
      sf2d_set_clear_color(RGBA8(rand()%255, rand()%255, rand()%255, 255));
    }

    draw(drawableVec);

  }

  delete(&player);
  sf2d_fini();

  return 0;
}
