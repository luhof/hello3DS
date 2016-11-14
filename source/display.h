#pragma once
#include <vector>
#include "drawable.h"

void draw(std::vector<Drawable> drawableVec);
void drawOnScreen(gfxScreen_t screen, gfx3dSide_t side, std::vector<Drawable> drawableVec);
