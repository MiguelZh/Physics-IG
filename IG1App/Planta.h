#pragma once
#include "Entity.h"
class Planta final : public Entity {
public:
  Planta(GLdouble width, GLdouble height, GLuint rowWidth, GLuint rowHeight);
  ~Planta();
  void render(Camera const &camera) override;
  void update() override;
};
