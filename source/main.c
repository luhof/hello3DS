#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <3ds.h>
#include <time.h>
#include <math.h>
#include <sf2d.h>
#include <sfil.h>

#include "imac_png.h"
#include "background_png.h"

//adress of the 3DS depth slider
#define CONFIG_3D_SLIDERSTATE (*(float *)0x1FF81080)


int main()
{

  sf2d_init();
  sf2d_set_clear_color(RGBA8(0x40, 0x40, 0x40, 0xFF));
  sf2d_set_3D(true);

  sf2d_texture *texBackground = sfil_load_PNG_buffer(background_png, SF2D_PLACE_RAM);
  sf2d_texture *texImac = sfil_load_PNG_buffer(imac_png, SF2D_PLACE_RAM);
  float imacPosX = 200;
  float imacPosY = 200;

  float offset3d1 = 0.0f;
  float offset3d2 = 0.0f;
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

    /*3D "power depending on 3DS slider.
    * now two hard coded values so there is a better
    * depth effect */
    offset3d1 = CONFIG_3D_SLIDERSTATE * 15.0f;
    offset3d2 = CONFIG_3D_SLIDERSTATE * 7.0f;

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

    //top left screen
    sf2d_start_frame(GFX_TOP, GFX_LEFT);
      sf2d_draw_texture(texBackground, -offset3d1, 0);
      sf2d_draw_texture(texImac, imacPosX, imacPosY);
      /*sf2d_draw_fill_circle(offset3d1 + 150, 100, 50, RGBA8(0x00, 0xFF, 0x00, 0xFF));
      sf2d_draw_rectangle_rotate(offset3d2 + 180, 40, 40, 40, RGBA8(0xFF, 0xFF, 0x00, 0xFF), 20);*/
    sf2d_end_frame();

    //top right screen
    sf2d_start_frame(GFX_TOP, GFX_RIGHT);
      sf2d_draw_texture(texBackground, 0, 0);
      sf2d_draw_texture(texImac, imacPosX+offset3d2,imacPosY);
      /*sf2d_draw_fill_circle(150, 100, 50, RGBA8(0x00, 0xFF, 0x00, 0xFF));
      sf2d_draw_rectangle_rotate(180, 40, 40, 40, RGBA8(0xFF, 0xFF, 0x00, 0xFF), 20);*/
    sf2d_end_frame();

    //bottom screen
    sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
      sf2d_draw_rectangle_rotate(touch_x-35, touch_y-30, 70, 60, RGBA8(0xFF, 0xFF, 0xFF, 0xFF), 3.0f*rad);
    sf2d_end_frame();

    rad += 0.02f;
    if(abs(circle.dx) >= 10) imacPosX += (circle.dx*0.03);
    if(abs(circle.dy) >= 10) imacPosY -= (circle.dy*0.03);

    sf2d_swapbuffers();

  }

  sf2d_free_texture(texImac);
	sf2d_free_texture(texBackground);
  sf2d_fini();

  return 0;
}
