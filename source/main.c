#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <3ds.h>
#include <time.h>
#include <math.h>
#include <sf2d.h>

//adress of the 3DS depth slider
#define CONFIG_3D_SLIDERSTATE (*(float *)0x1FF81080)


int main()
{

  sf2d_init();
  sf2d_set_clear_color(RGBA8(0x40, 0x40, 0x40, 0xFF));
  sf2d_set_3D(true);


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
    offset3d1 = CONFIG_3D_SLIDERSTATE * 30.0f;
    offset3d2 = CONFIG_3D_SLIDERSTATE * 15.0f;

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
      sf2d_draw_fill_circle(offset3d1 + 150, 100, 50, RGBA8(0x00, 0xFF, 0x00, 0xFF));
      sf2d_draw_rectangle_rotate(offset3d2 + 180, 40, 40, 40, RGBA8(0xFF, 0xFF, 0x00, 0xFF), 20);
    sf2d_end_frame();

    //top right screen
    sf2d_start_frame(GFX_TOP, GFX_RIGHT);
      sf2d_draw_fill_circle(150, 100, 50, RGBA8(0x00, 0xFF, 0x00, 0xFF));
      sf2d_draw_rectangle_rotate(180, 40, 40, 40, RGBA8(0xFF, 0xFF, 0x00, 0xFF), 20);
    sf2d_end_frame();

    //bottom screen
    sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
      sf2d_draw_rectangle_rotate(touch_x, touch_y, 70, 60, RGBA8(0xFF, 0xFF, 0xFF, 0xFF), 3.0f*rad);
    sf2d_end_frame();

    rad += 0.02f;

    sf2d_swapbuffers();

  }

  sf2d_fini();

  return 0;
}
