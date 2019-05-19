#include "Entity.h"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

using namespace glm;

// ReSharper disable StringLiteralTypo
// ReSharper disable IdentifierTypo

void Entity::uploadMvM(dmat4 const& modelViewMat) const {
  auto aMat = modelViewMat * modelMat_;
  glMatrixMode(GL_MODELVIEW);
  glLoadMatrixd(value_ptr(aMat));
}

EjesRGB::EjesRGB(const GLdouble l) { mesh_ = Mesh::createRGBAxes(l); }

EjesRGB::~EjesRGB() {
  delete mesh_;
  mesh_ = nullptr;
};

void EjesRGB::render(Camera const& cam) {
  if (mesh_ != nullptr) {
    uploadMvM(cam.getViewMat());
    glLineWidth(2);
    mesh_->render();
    glLineWidth(1);
  }
}

void EjesRGB::update() {}

Poliespiral::Poliespiral(const dvec2 verIni, const GLdouble angIni,
                         const GLdouble incrAng, const GLdouble ladoIni,
                         const GLdouble incrLado, const GLuint numVert) {
  mesh_ = Mesh::generaPoliespiral(verIni, angIni, incrAng, ladoIni, incrLado,
                                  numVert);
}

Poliespiral::~Poliespiral() {
  delete mesh_;
  mesh_ = nullptr;
}

void Poliespiral::render(Camera const& cam) {
  if (mesh_ != nullptr) {
    glColor3d(0, 0, 1);
    uploadMvM(cam.getViewMat());
    glLineWidth(2);
    mesh_->render();
  }
}

void Poliespiral::update() {}

Dragon::Dragon(const GLuint vertices) { mesh_ = Mesh::generaDragon(vertices); }

Dragon::~Dragon() {
  delete mesh_;
  mesh_ = nullptr;
}

void Dragon::render(Camera const& camera) {
  if (mesh_ != nullptr) {
    glColor3d(0.5, 0.0, 0.5);
    glPointSize(2);
    uploadMvM(camera.getViewMat());
    mesh_->render();
  }
}

void Dragon::update() {}

Triangle::Triangle(const GLdouble vertices) {
  mesh_ = Mesh::generaTrianguloRGB(vertices);
}

Triangle::~Triangle() {
  delete mesh_;
  mesh_ = nullptr;
}

auto Triangle::render(Camera const& camera) -> void {
  if (mesh_ != nullptr) {
    glLineWidth(2);
    uploadMvM(camera.getViewMat());
    mesh_->render();
  }
}

void Triangle::update() {}

Rectangulo::Rectangulo(const GLdouble width, const GLdouble height,
                       const int ejeZ) {
  mesh_ = Mesh::generaRectanguloRGB(width, height, ejeZ);
}

Rectangulo::~Rectangulo() {
  delete mesh_;
  mesh_ = nullptr;
}

void Rectangulo::render(Camera const& cam) {
  if (mesh_ != nullptr) {
    glLineWidth(2);
    uploadMvM(cam.getViewMat());
    mesh_->render();
  }
}

void Rectangulo::update() {}

TrianguloAnimado::TrianguloAnimado(const GLdouble vertices)
    : Triangle(vertices) {}

TrianguloAnimado::~TrianguloAnimado() {
  delete mesh_;
  mesh_ = nullptr;
}

void TrianguloAnimado::update() {
  setModelMat(dmat4(1));
  auto aux = rotate(getModelMat(), angle_ += radians(10.), dvec3(0, 0, 1.0));
  setModelMat(dmat4(1));
  aux = translate(aux, dvec3(30 * cos(angle_), 30 * sin(angle_), 0));
  aux = rotate(aux, angle2_ -= radians(25.5), dvec3(0, 0, 1));
  setModelMat(aux);
}

Estrella3D::Estrella3D(const GLdouble re, const GLdouble np,
                       const GLdouble height) {
  mesh_ = Mesh::generaEstrella3D(re, np, height);
  const auto translated = translate(modelMat_, dvec3(30, 100, 20));
  setModelMat(translated);
}

Estrella3D::~Estrella3D() {
  delete mesh_;
  mesh_ = nullptr;
}

void Estrella3D::render(Camera const& camera) {
  if (mesh_ != nullptr) {
    glPolygonMode(GL_POINT, GL_LINE);
    glLineWidth(2);
    uploadMvM(camera.getViewMat());
    mesh_->render();
    modelMat_ = rotate(modelMat_, radians(180.0), dvec3(0, 1, 0));
    uploadMvM(camera.getViewMat());
    mesh_->render();
    modelMat_ = rotate(modelMat_, radians(-180.0), dvec3(0, 1, 0));
  }
}

void Estrella3D::update() {
  setModelMat(dmat4(1));
  auto rotate1 = translate(getModelMat(), dvec3(30, 100, 20));
  rotate1 = rotate(rotate1, radians(angle_ += 5.), dvec3(0, 1, 0));
  rotate1 = rotate(rotate1, radians(angle_ += 5.), dvec3(0, 0, 1));
  setModelMat(rotate1);
}

Caja::Caja(const GLdouble length) { mesh_ = Mesh::generaContCubo(length); }

Caja::~Caja() {
  delete mesh_;
  mesh_ = nullptr;
}

void Caja::render(Camera const& camera) {
  if (mesh_ != nullptr) {
    // glColor3d(0, 1, 0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glLineWidth(2);
    uploadMvM(camera.getViewMat());
    mesh_->render();
  }
}

void Caja::update() {}

RectangleTex::RectangleTex(const GLdouble width, const GLdouble height,
                           const GLuint rowWidth, const GLuint rowHeight) {
  mesh_ = Mesh::generaRectanguloTexCor(width, height, rowWidth, rowHeight);
  texture_.load("..\\Bmps\\baldosaC.bmp");
}

RectangleTex::~RectangleTex() {
  delete mesh_;
  mesh_ = nullptr;
}

void RectangleTex::render(Camera const& camera) {
  if (mesh_ != nullptr) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    texture_.bind();
    glColor3d(0.0, 0.0, 1.0);
    uploadMvM(camera.getViewMat());
    mesh_->render();
    texture_.unbind();
  }
}

void RectangleTex::update() {}

Estrella3DTex::Estrella3DTex(const GLdouble r, const GLdouble nL,
                             const GLdouble height) {
  mesh_ = Mesh::generaEstrellaTexCor(r, nL, height);
  texture_.load("..\\Bmps\\baldosaP.bmp");
}

Estrella3DTex::~Estrella3DTex() {
  delete mesh_;
  mesh_ = nullptr;
}

void Estrella3DTex::render(Camera const& camera) {
  if (mesh_ != nullptr) {
    texture_.bind();
    glLineWidth(2);
    uploadMvM(camera.getViewMat());
    mesh_->render();
    modelMat_ = rotate(modelMat_, radians(180.0), dvec3(0, 1, 0));
    uploadMvM(camera.getViewMat());
    mesh_->render();
    modelMat_ = rotate(modelMat_, radians(-180.0), dvec3(0, 1, 0));
    texture_.unbind();
  }
}

void Estrella3DTex::update() {
  setModelMat(dmat4(1));
  dmat4 rotate1 = translate(getModelMat(), dvec3(30, 100, 20));
  rotate1 = rotate(rotate1, radians(angle_ += 5.), dvec3(0, 1, 0));
  rotate1 = rotate(rotate1, radians(angle_ += 5.), dvec3(0, 0, 1));
  setModelMat(rotate1);
}

CuboTex::CuboTex(const GLdouble length) {
  mesh_ = Mesh::generaCajaTexCor(length);
  texture_.load("..\\Bmps\\baldosaF.bmp");
  texture1_.load("..\\Bmps\\container.bmp");
}

CuboTex::~CuboTex() {
  delete mesh_;
  mesh_ = nullptr;
}

void CuboTex::render(Camera const& camera) {
  if (mesh_ != nullptr) {
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    texture_.bind();
    uploadMvM(camera.getViewMat());
    glLineWidth(2);
    mesh_->render();
    texture_.unbind();

    glCullFace(GL_BACK);
    texture1_.bind();
    mesh_->render();
    texture1_.unbind();
    glDisable(GL_CULL_FACE);
  }
}

void CuboTex::update() {}

Cristalera::Cristalera(const GLdouble length) {
  mesh_ = Mesh::generaCajaTexCor(length);
  texture_.load("..\\Bmps\\cristalTri.bmp", 150);
}

Cristalera::~Cristalera() {
  delete mesh_;
  mesh_ = nullptr;
}

void Cristalera::render(Camera const& cam) {
  if (mesh_ != nullptr) {
    uploadMvM(cam.getViewMat());
    glPolygonMode(GL_NONE, GL_LINE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_FALSE);
    glLineWidth(1);
    texture_.bind();
    mesh_->render();
    texture_.unbind();
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
  }
}

void Cristalera::update() {}

Foto::Foto(const GLdouble width, const GLdouble height, const GLuint rowWidth,
           const GLuint rowHeight) {
  mesh_ = Mesh::generaRectanguloTexCor(width, height, rowWidth, rowHeight);
}

Foto::~Foto() {
  delete mesh_;
  mesh_ = nullptr;
}

auto Foto::render(Camera const& camera) -> void {
  if (mesh_ != nullptr) {
    texture_.loadColorBuffer();

    uploadMvM(camera.getViewMat());
    glLineWidth(1);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    texture_.bind();
    mesh_->render();
    texture_.unbind();
  }
}

void Foto::update() {}

Planta::Planta(const GLdouble width, const GLdouble height,
               const GLuint rowWidth, const GLuint rowHeight) {
  mesh_ = Mesh::generaRectanguloTexCor(width, height, rowWidth, rowHeight);
  texture_.load("..\\Bmps\\grass.bmp");
}

Planta::~Planta() {
  delete mesh_;
  mesh_ = nullptr;
}

void Planta::render(Camera const& camera) {
  if (mesh_ != nullptr) {
    const auto originalMat = getModelMat();
    glDepthMask(GL_FALSE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    auto auxMat = originalMat;
    auxMat = rotate(auxMat, radians((180.0 / 20)), dvec3(0.0, 1.0, 0.0));
    setModelMat(auxMat);
    uploadMvM(camera.getViewMat());
    texture_.bind();
    mesh_->render();
    texture_.unbind();
    setModelMat(originalMat);
    glLineWidth(1);
    glDepthMask(GL_TRUE);
  }
}

void Planta::update() {}

Piramide::Piramide(const GLdouble length, const GLdouble height) {
  mesh_ = Mesh::bipiramideExam(length, height);
  side_ = length;
  height_ = height * 2;
  currentHeight_ = 0;
  movingUp_ = true;
  angle_ = 0.0;
  auxMat_ = translate(modelMat_, dvec3(-length / 2, 0, -length / 2));
  texture_.load("..\\Bmps\\sierpinski.bmp", 100);
}

Piramide::~Piramide() {
  delete mesh_;
  mesh_ = nullptr;
}

void Piramide::render(Camera const& camera) {
  modelMat_ = auxMat_;
  auto aux = translate(modelMat_, dvec3(side_, 0, 0));
  if (mesh_ != nullptr) {
    uploadMvM(camera.getViewMat());
    glLineWidth(2);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_FALSE);
    texture_.bind();
    mesh_->render();
    texture_.unbind();
    modelMat_ = rotate(aux, radians(180.0), dvec3(0, 0, 1));
    uploadMvM(camera.getViewMat());
    mesh_->render();
    aux = translate(modelMat_, dvec3(-side_, 0, 0));
    modelMat_ = rotate(aux, radians(-180.0), dvec3(0, 0, 1));
    glDisable(GL_LINE);
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
  }
}

void Piramide::update() {
  angle_ += 2;
  auxMat_ = rotate(auxMat_, radians(5.), dvec3(1, 1, 0));
  if (currentHeight_ > height_ || (currentHeight_ - 0.5 < -1)) {
    movingUp_ = !movingUp_;
  }
  if (movingUp_) {
    currentHeight_ += 0.5;
    auxMat_ = translate(auxMat_, dvec3(0, 0.5, 0));
  } else if (!movingUp_) {
    currentHeight_ -= 0.5;
    auxMat_ = translate(auxMat_, dvec3(0, -0.5, 0));
  }
}
