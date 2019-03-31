#include "Texture.h"

void Texture::init() {
  glGenTextures(1, &id_);  // Generates an identification for a new texture
  glBindTexture(GL_TEXTURE_2D, id_);  // filters and wrapping
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void Texture::bind(const GLint mode) const {
  glBindTexture(GL_TEXTURE_2D, id_);  // Activate the texture
  // The color mixture mode does not get saved in the object
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, mode);
  // Modes: GL_REPLACE, GL_MODULATE, GL_ADD …
}

void Texture::loadColorBuffer() {
  if (id_ == 0) {
    init();
  }
  glReadBuffer(GL_FRONT);
  glBindTexture(GL_TEXTURE_2D, id_);  // filters and wrapping
  glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, glutGet(GLUT_WINDOW_WIDTH),
                   glutGet(GLUT_WINDOW_HEIGHT), 0);
  glReadBuffer(GL_BACK);
}

void Texture::save(const std::string& bmpName) {
  PixMap32RGBA pic;
  pic.create_pixmap(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));

  glReadBuffer(GL_FRONT);
  glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, glutGet(GLUT_WINDOW_WIDTH),
                   glutGet(GLUT_WINDOW_HEIGHT), 0);
  glReadBuffer(GL_BACK);

  glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, pic.data());

  pic.save_bmp24BGR(bmpName);
}

void Texture::load(const std::string& bmpName, const GLubyte alpha) {
  if (id_ == 0) init();
  PixMap32RGBA pixMap;

  pixMap.load_bmp24BGR(bmpName);  // Load and set alpha=255
  if (alpha != 255) pixMap.set_alpha(alpha);

  w_ = pixMap.width();
  h_ = pixMap.height();
  glBindTexture(GL_TEXTURE_2D, id_);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w_, h_, 0, GL_RGBA, GL_UNSIGNED_BYTE,
               pixMap.data());
  // Transfer to GPU
}
