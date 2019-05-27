#pragma once
#include "Entity.h"
class CuboTex final : public Entity {
public:
  CuboTex(GLdouble length);
  ~CuboTex();
  void render(Camera const &camera) override;
  void update() override;
};
