#pragma once
#include "PosLight.h"

class SpotLight final : public PosLight {
 protected:
  glm::fvec4 spotDir_ = {0.0, -1.0, 0.0, 0};

 public:
  SpotLight();
  ~SpotLight();

  void upload(glm::dmat4 const& modelMat) const override;
  void setDir(glm::fvec3 dir);
  void setExponent(double exponent);
  void setAngle(double angle);
};
