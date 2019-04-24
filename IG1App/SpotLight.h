#pragma once
#include "PosLight.h"

class SpotLight : public PosLight {
 protected:
  glm::fvec4 spotDir = {0.0, -1.0, 0.0, 0};

 public:
  SpotLight();
  ~SpotLight();
  virtual void upload(glm::dmat4 const &modelMat) {
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixd(value_ptr(modelMat));
    glLightf(id_, GL_SPOT_CUTOFF, 90);
    glLightf(id_, GL_SPOT_EXPONENT, 4);
  }
  virtual void setDir(glm::fvec3 dir) { spotDir = glm::fvec4(dir, 0); }
  virtual void setExponent(const double exponent) {
    glLightf(id_, GL_SPOT_EXPONENT, exponent);
  }
  virtual void setAngle(const double angle) {
    glLightf(id_, GL_SPOT_CUTOFF, angle);
  }
};
