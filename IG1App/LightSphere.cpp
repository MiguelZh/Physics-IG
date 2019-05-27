#include "LightSphere.h"



LightSphere::LightSphere(const GLdouble radius, const std::string &text,
	const glm::dvec3 pos)
	: Sphere(radius, text), a_(350.0), b_(radius_ * 2.0), c_(-15.0) {
	spotLight_ = new SpotLight();
	spotLight_->setPos(pos);
	spotLight_->setDir(glm::fvec3(100, 100, 0));
	spotLight_->uploadLI();
	spotLight_->enable();
	modelMat_ = translate(getModelMat(), pos);
}

LightSphere::~LightSphere() { delete spotLight_; }

SpotLight *LightSphere::getSpotLight() const { return spotLight_; }

void LightSphere::render(Camera const &camera) {
	auxMat_ = modelMat_;
	glEnable(GL_CULL_FACE);
	glShadeModel(GL_SMOOTH);  // Gouraud Shading

	// Draw the big sphere
	gluQuadricDrawStyle(qObj_, GLU_FILL);
	texture_.bind(GL_MODULATE);
	uploadMvM(camera.getViewMat());
	gluSphere(qObj_, radius_ * 1.5, 72, 72);
	texture_.unbind();

	// Render the small sphere
	modelMat_ = moonModelMat_;
	material_->upload();
	gluQuadricDrawStyle(qObj_, GLU_LINE);
	texture_.bind(GL_MODULATE);
	uploadMvM(camera.getViewMat());
	gluSphere(qObj_, radius_, 36, 36);
	texture_.unbind();

	spotLight_->upload(camera.getViewMat());

	glDisable(GL_CULL_FACE);

	modelMat_ = auxMat_;

	glDisable(GL_CULL_FACE);
}

void LightSphere::update() {
	angle_ += 2.5;
	if (angle_ >= 360.0) angle_ -= 360.0;

	const auto angle = glm::radians(angle_);
	const auto x1 = a_ * cos(angle);
	const auto y1 = b_ * sin(angle) * sin(angle) + 190.0;
	const auto z1 = c_ * sin(angle) * cos(angle);
	const auto position = glm::dvec3(x1, y1, z1);
	spotLight_->setPos(position);
	setModelMat(translate(glm::dmat4(1.0), position));

	// Process the logic for the small sphere
	if (rotationAngle_ > 90)
		rotatingLeft_ = true;
	else if (rotationAngle_ < -90)
		rotatingLeft_ = false;
	rotationAngle_ += rotatingLeft_ ? -3.2 : 3.2;

	const auto rotation = glm::radians(rotationAngle_);
	const auto x2 = radius_ * cos(rotation);
	const auto y2 = -radius_ * sin(rotation);
	const auto mul = 3.5;
	moonModelMat_ = translate(getModelMat(), glm::dvec3(x2 * mul, y2 * mul, 0.0));
}
