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
	IndexMesh *indexMesh_;
  Texture *textureMatTexture_{};
  Material *material_;
};

class Sphere : public EntityMaterial {
public:
  Sphere(GLdouble radius, const std::string &text);
  ~Sphere();
  void render(Camera const &camera) override;
  void update() override;

protected:
	GLUquadricObj *qObj;
private:
  GLdouble radius_;
};
class LightSphere  : public Sphere {
private:
	GLUquadricObj *qObjSmall;
	GLdouble radius_;
	GLdouble ang = 0;
	GLuint B;
	GLuint A;
	GLuint C;
public:
  SpotLight *spotLight_;
  LightSphere(GLdouble radius, const std::string &text, glm::dvec3 pos);
  ~LightSphere();
  SpotLight *getSpotLight();
  void render(Camera const &camera) override;
  void update() override;
};
class CurvedTerrain final : public EntityMaterial {
private:
public:
  CurvedTerrain(GLdouble lado, GLuint numDiv, const std::string &text);
  ~CurvedTerrain();
  void render(Camera const &camera) override;
  void update() override;
};
