#include "Camera.h"

#include <gtc/matrix_access.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
using namespace glm;

//-------------------------------------------------------------------------

void Camera::set2D() {
  eye = dvec3(0, 0, 500);
  look = dvec3(0, 0, 0);
  up = dvec3(0, 1, 0);
  ang =- 45;
  setVM();
}
//-------------------------------------------------------------------------

void Camera::set3D() {
  eye = dvec3(500, 500, 500);
  look = dvec3(0, 10, 0);
  up = dvec3(0, 1, 0);
  // viewMat = lookAt(eye, look, up);
  ang = -90;
  setVM();
}

void Camera::setAxes() {
  right = row(viewMat, 0);
  upward = row(viewMat, 1);
  front = -row(viewMat, 2);
}

void Camera::setVM() {
  viewMat = lookAt(eye, look, up);
  setAxes();
}

void Camera::moveUD(const GLdouble cs)  // Up / Down
{
  eye += upward * cs;
  look += upward * cs;
  setVM();
}

void Camera::moveLR(const GLdouble cs)  // Left / Right
{
  eye += right * cs;
  look += right * cs;
  setVM();
}

void Camera::moveFB(const GLdouble cs)  // Forward / Backward
{
  eye += front * cs;
  look += front * cs;
  setVM();
}

void Camera::changePrj() {
  orto = !orto;
  setVM();
  uploadScale(0.0);
}

void Camera::orbit(const GLdouble incAng, const GLdouble incY) {
  ang += incAng;
  eye.x = look.x + cos(radians(ang)) * radio;
  eye.z = look.z - sin(radians(ang)) * radio;
  eye.y += incY;
  setVM();
}
//-------------------------------------------------------------------------

void Camera::uploadVM() const {
  glMatrixMode(GL_MODELVIEW);
  glLoadMatrixd(value_ptr(viewMat));
}
//-------------------------------------------------------------------------

void Camera::pitch(const GLdouble a) {
  viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(1.0, 0, 0));
}
//-------------------------------------------------------------------------
void Camera::yaw(const GLdouble a) {
  viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(0, 1.0, 0));
}
//-------------------------------------------------------------------------
void Camera::roll(const GLdouble a) {
  viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(0, 0, 1.0));
}
//-------------------------------------------------------------------------

void Camera::uploadSize(const GLdouble aw, const GLdouble ah) {
  xRight = aw / 2.0;
  xLeft = -xRight;
  yTop = ah / 2.0;
  yBot = -yTop;
  if (orto)
    projMat = ortho(xLeft * factScale, xRight * factScale, yBot * factScale,
                    yTop * factScale, nearVal, farVal);
  else
    projMat = frustum(xLeft * factScale, xRight * factScale, yBot * factScale,
                      yTop * factScale, nearVal * 500, farVal);

  uploadPM();
}
//-------------------------------------------------------------------------

void Camera::uploadScale(const GLdouble s) {
  factScale -= s;
  if (factScale < 0) factScale = 0.01;
  if (orto)
    projMat = ortho(xLeft * factScale, xRight * factScale, yBot * factScale,
                    yTop * factScale, nearVal, farVal);
  else
    projMat = frustum(xLeft * factScale, xRight * factScale, yBot * factScale,
                      yTop * factScale, nearVal * 500, farVal);
  uploadPM();
}
//-------------------------------------------------------------------------

void Camera::uploadPM() const {
  glMatrixMode(GL_PROJECTION);
  glLoadMatrixd(value_ptr(projMat));
  glMatrixMode(GL_MODELVIEW);
}
//-------------------------------------------------------------------------
