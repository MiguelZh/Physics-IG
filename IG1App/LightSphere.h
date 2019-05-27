#pragma once
#include "Sphere.h"
class LightSphere final : public Sphere {
	GLdouble angle_ = 0;
	GLdouble rotationAngle_ = 0;
	GLdouble a_;
	GLdouble b_;
	GLdouble c_;
	GLboolean rotatingLeft_ = false;
	glm::dmat4 moonModelMat_;

public:
	SpotLight *spotLight_;
	LightSphere(GLdouble radius, const std::string &text, glm::dvec3 pos);
	~LightSphere();
	SpotLight *getSpotLight() const;
	void render(Camera const &camera) override;
	void update() override;
};

