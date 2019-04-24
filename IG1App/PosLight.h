#pragma once
#include <gtc/type_ptr.hpp>

#include "Light.h"

class PosLight : public Light {
 protected:
  glm::fvec4 position_ = {0, 0, 0, 1};

 public:
  PosLight();
  ~PosLight();

  void upload(glm::dmat4 const& modelViewMat) override {
    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixd(value_ptr(modelViewMat));
    glLightfv(id_, GL_POSITION, value_ptr(position_));
    uploadLI();
  };
  void setPos(const glm::fvec3 pos) { position_ = glm::fvec4(pos, 1.0); };
};
