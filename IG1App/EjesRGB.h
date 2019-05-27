#pragma once
#include "Entity.h"
class EjesRGB final : public Entity {
public:
	EjesRGB(GLdouble l);
	~EjesRGB();
	void render(Camera const& cam) override;
	void update() override;
};

