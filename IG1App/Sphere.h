#pragma once
#include "EntityMaterial.h"
class Sphere : public EntityMaterial {
public:
	Sphere(GLdouble radius, const std::string &text);
	~Sphere();
	void render(Camera const &camera) override;
	void update() override;

protected:
	GLUquadricObj *qObj_;
	GLdouble radius_;
};
