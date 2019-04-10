#pragma once
#include "Entity.h"
#include "Material.h"
class EntityMaterial : public Entity {
 public:
  EntityMaterial();
  virtual ~EntityMaterial();
  void setTexture(Texture* text);
  void setMaterial(Material* material);

 protected:
  Texture* textureMatTexture_{};
  Material* material_;

};

class Sphere final : public EntityMaterial {
 public:
  Sphere(GLdouble radius, const std::string& text);
  ~Sphere();
  void render(Camera const& camera) override;
  void update() override;

 private:
  GLUquadricObj* qObj;
  GLdouble radius_;
};
