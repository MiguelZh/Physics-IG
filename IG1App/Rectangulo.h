#pragma once
#include "Entity.h"
class Rectangulo final : public Entity {
public:
	Rectangulo(GLdouble width, GLdouble height, int ejeZ);
	~Rectangulo();
	void render(Camera const &cam) override;
	void update() override;
};

