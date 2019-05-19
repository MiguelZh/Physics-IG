#include "SpotLight.h"

SpotLight::SpotLight() = default;
SpotLight::~SpotLight() = default;

void SpotLight::upload(glm::dmat4 const& modelMat) const {
  glMatrixMode(GL_MODELVIEW);
  glLoadMatrixd(value_ptr(modelMat));
  glLightf(id_, GL_SPOT_CUTOFF, 90);
  glLightf(id_, GL_SPOT_EXPONENT, 4.0);
  glLightfv(id_, GL_POSITION, glm::value_ptr(position_));
}

void SpotLight::setDir(const glm::fvec3 dir) { spotDir_ = glm::fvec4(dir, 0); }

void SpotLight::setExponent(const double exponent) {
  glLightf(id_, GL_SPOT_EXPONENT, exponent);
}

void SpotLight::setAngle(const double angle) {
  glLightf(id_, GL_SPOT_CUTOFF, angle);
}
