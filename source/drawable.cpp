#include "drawable.h"

  Drawable::Drawable(int x, int y, sf2d_texture * texture, gfxScreen_t screen) : x(x), y(y), tex(texture), screen(screen){
  };
  Drawable::~Drawable(){
    x = 0;
    y = 0;
  };

  void Drawable::draw(gfxScreen_t screen, gfx3dSide_t side){
    if(screen == GFX_TOP){
     if(tex){
        sf2d_draw_texture(this->tex, this->x + (side==GFX_RIGHT ? this->offset3d : 0), this->y);
      }
      else{
        sf2d_draw_rectangle(this->x, this->y, this->x+20, this->y+20, RGBA8(0xFF, 0x00, 0x00, 0xFF));
      }
    }
  };

  void Drawable::setPosX(int _x){
    x = _x;
  }

  void Drawable::setPosY(int _y){
    y = _y;
  }

  void Drawable::setPos(int _x, int _y){
    x = _x;
    y = _y;
  }

  int Drawable::getPosX(){
    return x;
  }

  int Drawable::getPosY(){
    return y;
  }

  gfxScreen_t Drawable::getScreen(){
    return screen;
  }
