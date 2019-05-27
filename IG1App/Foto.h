#pragma once
#include "Entity.h"
class Foto final : public Entity {
public:
  Foto(GLdouble width, GLdouble height, GLuint rowWidth, GLuint rowHeight);
  ~Foto();
  void render(Camera const &camera) override;
  void update() override;
};
