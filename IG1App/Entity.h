#pragma once
#include <GL/freeglut.h>
#include <glm.hpp>

#include "Camera.h"
#include "Mesh.h"
#include "Texture.h"

//-------------------------------------------------------------------------

class Entity {
 public:
  Entity() : modelMat_(1.0), auxMat_(1.0){};
  virtual ~Entity() = default;

  virtual void render(Camera const& cam) = 0;
  virtual void update() = 0;

  // modeling matrix
  glm::dmat4 const& getModelMat() const { return modelMat_; };
  GLint repetitions = 1;
  void setModelMat(glm::dmat4 const& aMat) { modelMat_ = aMat; }

 protected:
  Mesh* mesh_ = nullptr;  // surface mesh
  glm::dmat4 modelMat_;   // modeling matrix
  glm::dmat4 auxMat_;
  double angle_ = 0, angle2_ = 0;
  Texture texture_, texture1_;  // w, h, id
  // transfers modelViewMat to the GPU
  void uploadMvM(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------

class EjesRGB final : public Entity {
 public:
  EjesRGB(GLdouble l);
  ~EjesRGB();
  void render(Camera const& cam) override;
  void update() override;
};

//-------------------------------------------------------------------------

class Poliespiral final : public Entity {
 public:
  Poliespiral(glm::dvec2 verIni, GLdouble angIni, GLdouble incrAng,
              GLdouble ladoIni, GLdouble incrLado, GLuint numVert);
  ~Poliespiral();
  void render(Camera const& cam) override;
  void update() override;
};

class Dragon final : public Entity {
 public:
  Dragon(GLuint numVert);
  ~Dragon();
  void render(Camera const& cam) override;
  void update() override;
};

class Triangle : public Entity {
 public:
  Triangle(GLdouble numVert);
  ~Triangle();
  void render(Camera const& cam) override;
  void update() override;
};

class TrianguloAnimado final : public Triangle {
  glm::dmat4 aux_ = modelMat_;

 public:
  TrianguloAnimado(GLdouble numVert);
  ~TrianguloAnimado();
  void update() override;
};

class Rectangulo final : public Entity {
 public:
  Rectangulo(GLdouble w, GLdouble h, int ejeZ);
  ~Rectangulo();
  void render(Camera const& cam) override;
  void update() override;
};

class Estrella3D : public Entity {
 public:
  Estrella3D(GLdouble re, GLdouble np, GLdouble h);
  ~Estrella3D();
  void render(Camera const& cam) override;
  void update() override;
};

class Caja final : public Entity {
 public:
  Caja(GLdouble l);
  ~Caja();
  void render(Camera const& cam) override;
  void update() override;
};

class RectangleTex final : public Entity {
 public:
  RectangleTex(GLdouble w, GLdouble h, GLuint rw, GLuint rh);
  ~RectangleTex();
  void render(Camera const& cam) override;
  void update() override;
};

class Estrella3DTex final : public Entity {
 public:
  Estrella3DTex(GLdouble r, GLdouble nL, GLdouble h);
  ~Estrella3DTex();
  void render(Camera const& cam) override;
  void update() override;
};

class CuboTex final : public Entity {
 public:
  CuboTex(GLdouble l);
  ~CuboTex();
  void render(Camera const& cam) override;
  void update() override;
};

class Cristalera final : public Entity {
 public:
  Cristalera(GLdouble l);
  ~Cristalera();
  void render(Camera const& cam) override;
  void update() override;
};

class Foto final : public Entity {
 public:
  Foto(GLdouble w, GLdouble h, GLuint rw, GLuint rh);
  ~Foto();
  void render(Camera const& cam) override;
  void update() override;
};

class Planta final : public Entity {
 public:
  Planta(GLdouble w, GLdouble h, GLuint rw, GLuint rh);
  ~Planta();
  void render(Camera const& cam) override;
  void update() override;
};

class Piramide final : public Entity {
  double lado, altura, alturaActual, angulo;
  bool subiendo;

 public:
  Piramide(GLdouble l, GLdouble h);
  ~Piramide();
  void render(Camera const& cam) override;
  void update() override;
};
