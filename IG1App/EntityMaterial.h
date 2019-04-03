#pragma once
#include "Entity.h"
class EntityMaterial : public Entity {
 public:
  EntityMaterial();
  virtual ~EntityMaterial();
  void setTexture(Texture* text);

 private:
  Texture* texture;
};

class Sphere final : public EntityMaterial {
 public:
  Sphere();
  ~Sphere();
  void render(Camera const& camera) override;
  void update() override;

 private:
};
