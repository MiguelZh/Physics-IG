#pragma once
#include <GL/freeglut.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "Camera.h"
#include "Mesh.h"
#include "Texture.h"
using namespace glm;

//-------------------------------------------------------------------------

class Entity {
public:
  Entity() : modelMat_(1.0), auxMat_(1.0){};
  virtual ~Entity() = default;

  virtual void render(Camera const &cam) = 0;
  virtual void update() = 0;

  // modeling matrix
  glm::dmat4 const &getModelMat() const { return modelMat_; };
  GLint repetitions = 1;
  void setModelMat(glm::dmat4 const &aMat) { modelMat_ = aMat; }

protected:
  Mesh *mesh_ = nullptr; // surface mesh
  glm::dmat4 modelMat_;  // modeling matrix
  glm::dmat4 auxMat_;
  double angle_ = 0, angle2_ = 0;
  Texture texture_, texture1_; // w, h, id
  // transfers modelViewMat to the GPU
  void uploadMvM(glm::dmat4 const &modelViewMat) const;
};
