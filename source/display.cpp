#include "display.h"

void draw(std::vector<Drawable> drawableVec){

  drawOnScreen(GFX_TOP, GFX_LEFT, drawableVec);
  drawOnScreen(GFX_TOP, GFX_RIGHT, drawableVec);
  drawOnScreen(GFX_BOTTOM, GFX_LEFT, drawableVec);
  sf2d_swapbuffers();

};

void drawOnScreen(gfxScreen_t screen, gfx3dSide_t side, std::vector<Drawable> drawableVec){
  std::vector<Drawable>::iterator it;
  sf2d_start_frame(screen, side);
  for(it=drawableVec.begin() ; it < drawableVec.end(); it++){
    if(it->getScreen() == screen) it->draw(screen, side);
  }
  sf2d_end_frame();
}
