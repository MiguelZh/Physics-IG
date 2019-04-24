#pragma once
#include <gtc/type_ptr.hpp>

#include "Light.h"

class DirLight : public Light {
 protected:
  glm::fvec4 direction_ = {0, 0, 1, 0};  // w=0 -> vector
 public:
  DirLight();
  ~DirLight();

  void upload(glm::dmat4 const& modelViewMat) override;
  void setDir(glm::fvec3 dir);
};
