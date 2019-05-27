#pragma once
#include "Entity.h"
class Piramide final : public Entity {
  double side_, height_, currentHeight_, angle_;
  bool movingUp_;

public:
  Piramide(GLdouble length, GLdouble height);
  ~Piramide();
  void render(Camera const &camera) override;
  void update() override;
};
