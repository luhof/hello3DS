#pragma once
#include <sf2d.h>
#include <sfil.h>

class Drawable{

  private:
    int x; int y;
    sf2d_texture * tex;
    int offset3d = 0;
    gfxScreen_t screen;

  public:
    Drawable(int x, int y, sf2d_texture * texture, gfxScreen_t screen);
    ~Drawable();
    void setPosX(int _x);
    void setPosY(int _y);
    void setPos(int _x, int _y);
    int getPosX();
    int getPosY();
    gfxScreen_t getScreen();

    // draws element on correct screen and side.
    void draw(gfxScreen_t screen, gfx3dSide_t side);
};
