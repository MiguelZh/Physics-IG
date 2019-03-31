#pragma once
#include <GL/freeglut.h>

//-------------------------------------------------------------------------

class Viewport final {
 public:
  Viewport(const GLsizei aw, const GLsizei ah) : width_(aw), height_(ah) {}
  ~Viewport() = default;

  GLsizei getLeft() const { return xLeft_; }  // viewport left position
  GLsizei getBot() const { return yBot_; }    // viewport bottom position
  GLsizei getW() const { return width_; }     // viewport width
  GLsizei getH() const { return height_; }    // viewport height

  void setPos(const GLsizei al, const GLsizei ab) {
    xLeft_ = al;
    yBot_ = ab;
  }  // set viewport position (left and bottom)
  void setSize(const GLsizei aw, const GLsizei ah) {
    width_ = aw;
    height_ = ah;
  }  // set viewport size (width and height)

  // transfers viewport to the GPU
  void upload() const;

  // set viewport position (left and bottom) and transfers it to the GPU
  void uploadPos(GLsizei al, GLsizei ab);

  // set viewport size (width and height) and transfers it to the GPU
  void uploadSize(GLsizei aw, GLsizei ah);

 protected:
  GLint xLeft_ = 0, yBot_ = 0;  // viewport position: left and bottom
  GLsizei width_, height_;      // viewport size: width and height
};
