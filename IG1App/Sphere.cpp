#include "Sphere.h"



Sphere::Sphere(const GLdouble radius, const std::string &text) {
	radius_ = radius;
	qObj_ = gluNewQuadric();
	texture_.load(text, 150);
	gluQuadricTexture(qObj_, GL_TRUE);
}

Sphere::~Sphere() { gluDeleteQuadric(qObj_); }

void Sphere::render(Camera const &camera) {
	material_->upload();
	glShadeModel(GL_SMOOTH);  // Gouraud Shading
	glEnable(GL_CULL_FACE);
	texture_.bind(GL_MODULATE);
	uploadMvM(camera.getViewMat());
	gluSphere(qObj_, radius_, 36, 36);
	texture_.unbind();

	glDisable(GL_CULL_FACE);
}

void Sphere::update() {}
