#pragma once
#include <gtc/type_ptr.hpp>
#include "Light.h"

class PosLight : public Light {
 protected:
  glm::fvec4 position_ = {0, 0, 0, 1};

 public:
  PosLight();
  ~PosLight();

  virtual void upload(glm::dmat4 const& modelViewMat) const;
  void setPos(glm::fvec3 pos);
};
