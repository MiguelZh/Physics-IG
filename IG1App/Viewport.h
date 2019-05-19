#pragma once
#include <GL/freeglut.h>

class Viewport final {
 public:
  Viewport(GLsizei aw, GLsizei ah);
  ~Viewport();

  GLsizei getLeft() const;  // viewport left position
  GLsizei getBot() const;   // viewport bottom position
  GLsizei getW() const;     // viewport width
  GLsizei getH() const;     // viewport height

  void setPos(GLsizei al,
              GLsizei ab);  // set viewport position (left and bottom)
  void setSize(GLsizei aw, GLsizei ah);  // set viewport size (width and height)

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
