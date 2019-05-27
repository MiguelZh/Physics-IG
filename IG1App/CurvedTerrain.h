#pragma once
#include "EntityMaterial.h"
#include "IndexMesh.h"
class CurvedTerrain final : public EntityMaterial {
public:
  CurvedTerrain(GLdouble side, GLuint numDiv, const std::string &text);
  ~CurvedTerrain();
  void render(Camera const &camera) override;
  void update() override;
};
