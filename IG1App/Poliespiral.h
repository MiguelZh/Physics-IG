#pragma once
#include "Entity.h"
class Poliespiral final : public Entity {
public:
  Poliespiral(glm::dvec2 verIni, GLdouble angIni, GLdouble incrAng,
              GLdouble ladoIni, GLdouble incrLado, GLuint numVert);
  ~Poliespiral();
  void render(Camera const &cam) override;
  void update() override;
};
