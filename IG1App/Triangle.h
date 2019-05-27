#pragma once
#include "Entity.h"
class Triangle : public Entity {
public:
  Triangle(GLdouble vertices);
  ~Triangle();
  void render(Camera const &camera) override;
  void update() override;
};
