#pragma once
#include <GL/freeglut.h>
#include <glm.hpp>

class Light {
 protected:
  static GLuint cont_;                     
  GLuint id_ = GL_LIGHT0 + GL_MAX_LIGHTS;  
  glm::fvec4 ambient_ = {0.1, 0.1, 0.1, 1};
  glm::fvec4 diffuse_ = {0.5, 0.5, 0.5, 1};
  glm::fvec4 specular_ = {0.5, 0.5, 0.5, 1};
  bool enabled_ = true;

 public:  
  Light();
  virtual ~Light();
  virtual void uploadLI();
  virtual void upload(glm::dmat4 const& modelViewMat) = 0;
  void disable();
  void enable();
  void setAmb(glm::fvec4 amb);
  bool getEnabled() const;
  void setEnabled(bool enable);
};
