#include "Light.h"

#include <gtc/type_ptr.hpp>

GLuint Light::cont_ = 0;

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

void Light::disable() {
  if (id_ < GL_LIGHT0 + GL_MAX_LIGHTS) {
    glDisable(id_);
  }
}

void Light::enable() {
  if (id_ < GL_LIGHT0 + GL_MAX_LIGHTS) {
    glEnable(id_);
  }
}

void Light::setAmb(const glm::fvec4 amb) { ambient_ = amb; }

bool Light::getEnabled() const { return enabled_; }
void Light::setEnabled(const bool enable) { enabled_ = enable; }
