#include "DirLight.h"

DirLight::DirLight() = default;
DirLight::~DirLight() = default;

void DirLight::upload(glm::dmat4 const& modelViewMat) const {
  glMatrixMode(GL_MODELVIEW);
  glLoadMatrixd(value_ptr(modelViewMat));
  glLightfv(id_, GL_POSITION, value_ptr(direction_));
  uploadLI();
}

void DirLight::setDir(const glm::fvec3 dir) {
  direction_ = glm::fvec4(dir, 0.0);
}
