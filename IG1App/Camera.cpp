#include "Camera.h"
#include <gtc/matrix_access.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
using namespace glm;

Camera::Camera(Viewport* avp)
    : viewMat_(1.0),
      projMat_(1.0),
      xRight_(avp->getW() / 2.0),
      xLeft_(-xRight_),
      yTop_(avp->getH() / 2.0),
      yBot_(-yTop_),
      eye_(),
      look_(),
      up_(),
      right_(),
      upward_(),
      front_(),
      ang_(),
      vp_(avp) {}

void Camera::set2D() {
  eye_ = dvec3(0, 0, 500);
  look_ = dvec3(0, 0, 0);
  up_ = dvec3(0, 1, 0);
  ang_ = -90;
  viewMat_ = lookAt(eye_, look_, up_);
}

void Camera::set3D() {
  eye_ = dvec3(500, 500, 500);
  look_ = dvec3(0, 10, 0);
  up_ = dvec3(0, 1, 0);
  // viewMat = lookAt(eye, look, up);
  ang_ = -90;
  viewMat_ = lookAt(eye_, look_, up_);
}

void Camera::uploadVM() const {
  glMatrixMode(GL_MODELVIEW);
  glLoadMatrixd(value_ptr(viewMat_));
}

void Camera::uploadSize(const GLdouble aw, const GLdouble ah) {
  xRight_ = aw / 2.0;
  xLeft_ = -xRight_;
  yTop_ = ah / 2.0;
  yBot_ = -yTop_;
  if (orthogonal_)
    projMat_ = ortho(xLeft_ * factScale_, xRight_ * factScale_,
                     yBot_ * factScale_, yTop_ * factScale_, nearVal_, farVal_);
  else
    projMat_ =
        frustum(xLeft_ * factScale_, xRight_ * factScale_, yBot_ * factScale_,
                yTop_ * factScale_, nearVal_ * 500, farVal_);

  uploadPM();
}

void Camera::uploadScale(const GLdouble s) {
  factScale_ -= s;
  if (factScale_ < 0) factScale_ = 0.01;
  if (orthogonal_)
    projMat_ = ortho(xLeft_ * factScale_, xRight_ * factScale_,
                     yBot_ * factScale_, yTop_ * factScale_, nearVal_, farVal_);
  else
    projMat_ =
        frustum(xLeft_ * factScale_, xRight_ * factScale_, yBot_ * factScale_,
                yTop_ * factScale_, nearVal_ * 500, farVal_);
  uploadPM();
}

void Camera::setAxes() {
  right_ = row(viewMat_, 0);
  upward_ = row(viewMat_, 1);
  front_ = -row(viewMat_, 2);
}

void Camera::setVM() {
  viewMat_ = lookAt(eye_, look_, up_);
  setAxes();
}

void Camera::moveUD(const GLdouble cs)  // Up / Down
{
  eye_ += upward_ * cs;
  look_ += upward_ * cs;
  setVM();
}

void Camera::moveLR(const GLdouble cs)  // Left / Right
{
  eye_ += right_ * cs;
  look_ += right_ * cs;
  setVM();
}

void Camera::moveFB(const GLdouble cs)  // Forward / Backward
{
  eye_ += front_ * cs;
  look_ += front_ * cs;
  setVM();
}

void Camera::changePrj() {
  orthogonal_ = !orthogonal_;
  setVM();
  uploadScale(0.0);
}

glm::dvec3 Camera::getPos() const {
    return eye_;
}

glm::dvec3 Camera::getDir() const {
    return front_;
}

void Camera::orbit(const GLdouble incAng, const GLdouble incY) {
  ang_ += incAng;
  eye_.x = look_.x + cos(radians(ang_)) * radio_;
  eye_.z = look_.z - sin(radians(ang_)) * radio_;
  eye_.y += incY;
  setVM();
}

void Camera::uploadPM() const {
  glMatrixMode(GL_PROJECTION);
  glLoadMatrixd(value_ptr(projMat_));
  glMatrixMode(GL_MODELVIEW);
}
