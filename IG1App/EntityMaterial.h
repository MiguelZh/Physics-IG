#pragma once
#include "Entity.h"
#include "Material.h"
#include "SpotLight.h"

class IndexMesh;

class EntityMaterial : public Entity {
public:
  EntityMaterial();
  virtual ~EntityMaterial();
  void setTexture(Texture *text);
  void setMaterial(Material *material);
  virtual void render(Camera const &cam) = 0;
  virtual void update() = 0;

protected:
  IndexMesh *indexMesh_ = nullptr;
  Texture *textureMatTexture_ = nullptr;
  Material *material_ = nullptr;
};
