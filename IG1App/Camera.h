//#pragma once
#pragma once
#include <GL/freeglut.h>
#include <glm.hpp>
#include "Viewport.h"
//-------------------------------------------------------------------------

class Camera final {
 public:
  explicit Camera(Viewport* avp);
  ~Camera() = default;
  Viewport* getVP() const { return vp_; }

  // view matrix (the inverse of modeling matrix)
  glm::dmat4 const& getViewMat() const { return viewMat_; }
  void uploadVM() const;  // transfers viewMat to the GPU

  // projection matrix
  glm::dmat4 const& getProjMat() const { return projMat_; }
  void uploadPM() const;  // transfers projMat to the GPU

  // set scene visible area size and transfers projMat to the GPU
  void uploadSize(GLdouble aw, GLdouble ah);

  // update scale factor and transfers projMat to GPU
  void uploadScale(GLdouble s);

  void set2D();  // eye(0,0,500), look(0,0,0), up(0, 1, 0)
  void set3D();  // eye(500,500,500), look(0,10,0), up(0, 1, 0)
  void setAxes();
  void setVM();
  void moveUD(GLdouble cs);
  void moveLR(GLdouble cs);
  void moveFB(GLdouble cs);
  void changePrj();
  glm::dvec3 getPos() const;
  glm::dvec3 getDir() const;
  void orbit(GLdouble incAng,
             GLdouble incY);  // modifies the camera's position

 protected:
  glm::dmat4 viewMat_;  // view matrix = inverse of modeling matrix

  glm::dmat4 projMat_;  // projection matrix

  GLdouble xRight_, xLeft_, yTop_, yBot_;  // size of scene visible area
  GLdouble nearVal_ = 1, farVal_ = 10000;  // view volume
  GLdouble factScale_ = 1;

  glm::dvec3 eye_, look_, up_;
  glm::dvec3 right_, upward_, front_;
  GLdouble ang_;
  GLdouble radio_ = 1000;
  bool orthogonal_ = true;

  Viewport* vp_;
};

//-------------------------------------------------------------------------
