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
  IndexMesh *indexMesh_{};
  Texture *textureMatTexture_{};
  Material *material_{};
};

class Sphere : public EntityMaterial {
 public:
  Sphere(GLdouble radius, const std::string &text);
  ~Sphere();
  void render(Camera const &camera) override;
  void update() override;

 protected:
  GLUquadricObj *qObj;
  GLdouble radius_;
};
class LightSphere final : public Sphere {
  GLdouble angle_ = 0;
  GLdouble rotationAngle_ = 0;
  GLdouble a_;
  GLdouble b_;
  GLdouble c_;

 public:
  SpotLight *spotLight_;
  LightSphere(GLdouble radius, const std::string &text, glm::dvec3 pos);
  ~LightSphere();
  SpotLight *getSpotLight() const;
  void render(Camera const &camera) override;
  void update() override;
};

class CurvedTerrain final : public EntityMaterial {
 public:
  CurvedTerrain(GLdouble side, GLuint numDiv, const std::string &text);
  ~CurvedTerrain();
  void render(Camera const &camera) override;
  void update() override;
};
