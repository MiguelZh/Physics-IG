#include "Light.h"
#include <gtc/type_ptr.hpp>

Light::Light() {
  if (cont_ < GL_MAX_LIGHTS) {
    id_ = GL_LIGHT0 + cont_;
    ++cont_;
  }
}

Light::~Light() { disable(); }

void Light::uploadLI() {
  glLightfv(id_, GL_AMBIENT, value_ptr(ambient_));
  glLightfv(id_, GL_DIFFUSE, value_ptr(diffuse_));
  glLightfv(id_, GL_SPECULAR, value_ptr(specular_));
}

void Light::disable() const {
  if (id_ < GL_LIGHT0 + GL_MAX_LIGHTS) {
    glDisable(id_);
  }
}

void Light::enable() const {
  if (id_ < GL_LIGHT0 + GL_MAX_LIGHTS) {
    glEnable(id_);
  }
}

void Light::setAmb(const glm::fvec4 amb) { ambient_ = amb; }
