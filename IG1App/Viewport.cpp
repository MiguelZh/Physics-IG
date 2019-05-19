#include "Viewport.h"

void Viewport::uploadSize(const GLsizei aw, const GLsizei ah) {
  setSize(aw, ah);
  upload();
}

void Viewport::uploadPos(const GLsizei al, const GLsizei ab) {
  setPos(al, ab);
  upload();
}

Viewport::Viewport(const GLsizei aw, const GLsizei ah)
    : width_(aw), height_(ah) {}

Viewport::~Viewport() = default;
GLsizei Viewport::getLeft() const { return xLeft_; }
GLsizei Viewport::getBot() const { return yBot_; }
GLsizei Viewport::getW() const { return width_; }
GLsizei Viewport::getH() const { return height_; }

void Viewport::setPos(const GLsizei al, const GLsizei ab) {
  xLeft_ = al;
  yBot_ = ab;
}

void Viewport::setSize(const GLsizei aw, const GLsizei ah) {
  width_ = aw;
  height_ = ah;
}

void Viewport::upload() const {
  glViewport(xLeft_, yBot_, width_, height_);  // transfers viewport to the GPU
}
