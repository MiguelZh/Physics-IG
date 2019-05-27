#pragma once
#include "Entity.h"
class Dragon final : public Entity {
public:
  Dragon(GLuint vertices);
  ~Dragon();
  void render(Camera const &camera) override;
  void update() override;
};
