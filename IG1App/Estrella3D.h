#pragma once
#include "Entity.h"
class Estrella3D : public Entity {
public:
  Estrella3D(GLdouble re, GLdouble np, GLdouble height);
  ~Estrella3D();
  void render(Camera const &camera) override;
  void update() override;
};
