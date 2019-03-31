#include "Viewport.h"

//-------------------------------------------------------------------------

void Viewport::uploadSize(const GLsizei aw, const GLsizei ah) {
  setSize(aw, ah);
  upload();
}
//-------------------------------------------------------------------------

void Viewport::uploadPos(const GLsizei al, const GLsizei ab) {
  setPos(al, ab);
  upload();
}
//-------------------------------------------------------------------------

void Viewport::upload() const {
  glViewport(xLeft_, yBot_, width_, height_);  // transfers viewport to the GPU
}
//-------------------------------------------------------------------------
