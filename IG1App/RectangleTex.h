#pragma once
#include "Entity.h"
class RectangleTex final : public Entity {
public:
  RectangleTex(GLdouble width, GLdouble height, GLuint rowWidth,
               GLuint rowHeight);
  ~RectangleTex();
  void render(Camera const &camera) override;
  void update() override;
};
