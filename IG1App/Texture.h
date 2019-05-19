#pragma once
#include "Pixmap32RGBA.h"

class Texture final {
 public:
  Texture();
  ~Texture();
  void load(const std::string& bmpName, GLubyte alpha = 255);
  // Load and transfer to the GPU
  void bind(GLint mode = GL_REPLACE) const;
  static void unbind();
  ;
  void loadColorBuffer();
  static void save(const std::string& bmpName);

 protected:
  GLuint w_, h_;  // Image's dimensions
  GLuint id_;     // Texture's Internal identifier for the GPU
  void init();
};
