#pragma once
#include "Entity.h"
class Caja final : public Entity {
public:
  Caja(GLdouble length);
  ~Caja();
  void render(Camera const &camera) override;
  void update() override;
};
