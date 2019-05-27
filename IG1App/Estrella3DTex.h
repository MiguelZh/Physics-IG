#pragma once
#include "Entity.h"
class Estrella3DTex final : public Entity {
public:
  Estrella3DTex(GLdouble r, GLdouble nL, GLdouble height);
  ~Estrella3DTex();
  void render(Camera const &camera) override;
  void update() override;
};
