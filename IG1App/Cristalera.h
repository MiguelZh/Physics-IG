#pragma once
#include "Entity.h"
class Cristalera final : public Entity {
public:
	Cristalera(GLdouble length);
	~Cristalera();
	void render(Camera const &cam) override;
	void update() override;
};

