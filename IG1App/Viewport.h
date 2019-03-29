#pragma once
#include <GL/freeglut.h>

//-------------------------------------------------------------------------

class Viewport {
 public:
  Viewport(GLsizei aw, GLsizei ah) : width(aw), height(ah){};
  ~Viewport() = default;

  GLsizei getLeft() const { return xLeft; };  // viewport left position
  GLsizei getBot() const { return yBot; };    // viewport bottom position
  GLsizei getW() const { return width; };     // viewport width
  GLsizei getH() const { return height; };    // viewport height

  void setPos(GLsizei al, GLsizei ab) {
    xLeft = al;
    yBot = ab;
  };  // set viewport position (left and bottom)
  void setSize(GLsizei aw, GLsizei ah) {
    width = aw;
    height = ah;
  };  // set viewport size (width and height)

  // transfers viewport to the GPU
  void upload() const;

  // set viewport position (left and bottom) and transfers it to the GPU
  void uploadPos(GLsizei al, GLsizei ab);

  // set viewport size (width and height) and transfers it to the GPU
  void uploadSize(GLsizei aw, GLsizei ah);

 protected:
  GLint xLeft = 0, yBot = 0;  // viewport position: left and bottom
  GLsizei width, height;      // viewport size: width and height
};
