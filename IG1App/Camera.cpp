#include "Camera.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_access.hpp>
using namespace glm;

//-------------------------------------------------------------------------

void Camera::set2D() 
{
	 eye= dvec3(0, 0, 500);
	 look= dvec3(0, 0, 0);
	 up= dvec3(0, 1, 0);
	 ang - 45;
	 setVM();
}
//-------------------------------------------------------------------------

void Camera::set3D() 
{
	 eye= dvec3(500, 500, 500);
	 look= dvec3(0, 10, 0);
	 up= dvec3(0, 1, 0);
	 //viewMat = lookAt(eye, look, up);
	 ang = -90;
	 setVM();
}
void Camera::setAxes()
{
	right = row(viewMat, 0);
	upward = row(viewMat, 1);
	front = -row(viewMat, 2);
}
void Camera::setVM()
{
	viewMat = lookAt(eye, look, up); 
	setAxes();
}
void Camera::moveUD(GLdouble cs) // Up / Down
{
	eye += upward * cs;
	look += upward * cs;
	setVM();
}
void Camera::moveLR(GLdouble cs) // Left / Right
{
	eye += right * cs;
	look += right * cs;
	setVM();
}
void Camera::moveFB(GLdouble cs) // Forward / Backward
{
	eye += front * cs;
	look += front * cs;
	setVM();
}
void Camera::changePrj()
{
	orto = !orto;
	if (orto) { moveFB(20); }
	if (!orto) { moveFB(20); moveUD(20); }
}
void Camera::orbit(GLdouble incAng, GLdouble incY)
{
	ang += incAng;
	eye.x = look.x + cos(radians(ang)) * radio;
	eye.z = look.z - sin(radians(ang)) * radio;
	eye.y += incY;
	setVM();
}
//-------------------------------------------------------------------------

void Camera::uploadVM() const
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(viewMat));
}
//-------------------------------------------------------------------------

void Camera::pitch(GLdouble a) 
{  
	viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(1.0, 0, 0));
}
//-------------------------------------------------------------------------
void Camera::yaw(GLdouble a)
{
	viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(0, 1.0, 0));
}
//-------------------------------------------------------------------------
void Camera::roll(GLdouble a)
{
	viewMat = rotate(viewMat, glm::radians(-a), glm::dvec3(0, 0, 1.0));
}
//-------------------------------------------------------------------------

void Camera::uploadSize(GLdouble aw, GLdouble ah)
{
	xRight = aw / 2.0;
	xLeft = -xRight;
	yTop = ah / 2.0;
	yBot = -yTop;
	projMat = ortho(xLeft*factScale, xRight*factScale, yBot*factScale, yTop*factScale, nearVal, farVal);

	uploadPM();
}
//-------------------------------------------------------------------------

void Camera::uploadScale(GLdouble s)
{
	factScale -= s;
	if (factScale < 0) factScale = 0.01;
	projMat = ortho(xLeft*factScale, xRight*factScale, yBot*factScale, yTop*factScale, nearVal, farVal);

	uploadPM();
}
//-------------------------------------------------------------------------

void Camera::uploadPM() const
{
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(value_ptr(projMat));
	glMatrixMode(GL_MODELVIEW);
}
//-------------------------------------------------------------------------


