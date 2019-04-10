#pragma once
#include "Light.h"

class DirLight : public Light {
 protected:
  glm::fvec4 direction = {0, 0, 1, 0};  // w=0 -> vector
 public:
  DirLight() : Light(){};  // Constructora con parámetros !!!
  virtual void upload(glm::dmat4 const& modelViewMat) {
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixd(value_ptr(modelViewMat));
    glLightfv(id_, GL_POSITION, value_ptr(direction));
    uploadLI();
  };
  void setDir(glm::fvec3 dir) { direction = glm::fvec4(dir, 0.0); };
  // -dir ?
};
