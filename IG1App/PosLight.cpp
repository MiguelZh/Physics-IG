#include "PosLight.h"

PosLight::PosLight() = default;
PosLight::~PosLight() = default;

void PosLight::upload(glm::dmat4 const& modelViewMat) const {
  glMatrixMode(GL_MODELVIEW);
  glLoadMatrixd(value_ptr(modelViewMat));
  glLightfv(id_, GL_POSITION, value_ptr(position_));
  // uploadLI();
}

void PosLight::setPos(const glm::fvec3 pos) {
  position_ = glm::fvec4(pos, 1.0);
}
