#include "Entity.h"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

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

Dragon::Dragon(const GLuint numVert) { mesh_ = Mesh::generaDragon(numVert); }

Dragon::~Dragon() {
  delete mesh_;
  mesh_ = nullptr;
}

void Dragon::render(Camera const& cam) {
  if (mesh_ != nullptr) {
    glColor3d(0.5, 0.0, 0.5);
    glPointSize(2);
    uploadMvM(cam.getViewMat());
    mesh_->render();
  }
}

void Dragon::update() {}

Triangle::Triangle(GLdouble numVert) {
  mesh_ = Mesh::generaTrianguloRGB(numVert);
}

Triangle::~Triangle() {
  delete mesh_;
  mesh_ = nullptr;
}

void Triangle::render(Camera const& cam) {
  if (mesh_ != nullptr) {
    glLineWidth(2);
    uploadMvM(cam.getViewMat());
    mesh_->render();
  }
}

void Triangle::update() {}

Rectangulo::Rectangulo(GLdouble w, GLdouble h, int ejeZ) {
  mesh_ = Mesh::generaRectanguloRGB(w, h, ejeZ);
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

TrianguloAnimado::TrianguloAnimado(GLdouble numVert) : Triangle(numVert) {}

TrianguloAnimado::~TrianguloAnimado() {
  delete mesh_;
  mesh_ = nullptr;
}

void TrianguloAnimado::update() {
  /*
      double anguloExt = 10;
      double anguloInt = -10.;
      double aumentoInt = 2, aumentoExt = 2;
      modelMat = translate(dmat4(1), dvec3(-5 * cos(radians(anguloExt)), -5
     *sin(radians(anguloExt)), 0)); modelMat += rotate(modelMat,
     radians(anguloInt), dvec3(0, 0, 1)); anguloExt += aumentoExt; anguloInt +=
     aumentoInt;
      */
  dmat4 aux;
  setModelMat(dmat4(1));
  aux = rotate(getModelMat(), angle_ += radians(10.), dvec3(0, 0, 1.0));
  setModelMat(dmat4(1));
  aux = translate(aux, dvec3(30 * cos(angle_), 30 * sin(angle_), 0));
  aux = rotate(aux, angle2_ -= radians(25.5), dvec3(0, 0, 1));
  setModelMat(aux);
}

Estrella3D::Estrella3D(GLdouble re, GLdouble np, GLdouble h) {
  mesh_ = Mesh::generaEstrella3D(re, np, h);
  dmat4 trans = translate(modelMat_, dvec3(30, 100, 20));
  setModelMat(trans);
}

Estrella3D::~Estrella3D() {
  delete mesh_;
  mesh_ = nullptr;
}

void Estrella3D::render(Camera const& cam) {
  if (mesh_ != nullptr) {
    // glColor3d(1, 0, 0);
    glPolygonMode(GL_POINT, GL_LINE);
    glLineWidth(2);
    uploadMvM(cam.getViewMat());
    mesh_->render();
    modelMat_ = rotate(modelMat_, radians(180.0), dvec3(0, 1, 0));
    uploadMvM(cam.getViewMat());
    mesh_->render();
    modelMat_ = rotate(modelMat_, radians(-180.0), dvec3(0, 1, 0));
  }
}

void Estrella3D::update() {
  setModelMat(dmat4(1));
  dmat4 rotate1 = translate(getModelMat(), dvec3(30, 100, 20));
  rotate1 = rotate(rotate1, radians(angle_ += 5.), dvec3(0, 1, 0));
  rotate1 = rotate(rotate1, radians(angle_ += 5.), dvec3(0, 0, 1));
  setModelMat(rotate1);
}

Caja::Caja(GLdouble l) {
  mesh_ = Mesh::generaContCubo(l);
  /// modelMat = rotate(getModelMat(), -270., dvec3(0, 1,1));
}

Caja::~Caja() {
  delete mesh_;
  mesh_ = nullptr;
}

void Caja::render(Camera const& cam) {
  if (mesh_ != nullptr) {
    // glColor3d(0, 1, 0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glLineWidth(2);
    uploadMvM(cam.getViewMat());
    mesh_->render();
  }
}

void Caja::update() {}

RectangleTex::RectangleTex(const GLdouble w, const GLdouble h, const GLuint rw,
                           const GLuint rh) {
  mesh_ = Mesh::generaRectanguloTexCor(w, h, rw, rh);  // con coord. de textura
  texture_.load("..\\Bmps\\baldosaC.bmp");             // cargamos la imagen
}

RectangleTex::~RectangleTex() {
  delete mesh_;
  mesh_ = nullptr;
}

void RectangleTex::render(Camera const& cam) {
  if (mesh_ != nullptr) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    texture_.bind();
    glColor3d(0.0, 0.0, 1.0);
    uploadMvM(cam.getViewMat());
    mesh_->render();
    texture_.unbind();
  }
}

void RectangleTex::update() {}

Estrella3DTex::Estrella3DTex(const GLdouble r, const GLdouble nL,
                             const GLdouble h) {
  mesh_ = Mesh::generaEstrellaTexCor(r, nL, h);
  texture_.load("..\\Bmps\\baldosaP.bmp");  // cargamos la imagen
}

Estrella3DTex::~Estrella3DTex() {
  delete mesh_;
  mesh_ = nullptr;
}

void Estrella3DTex::render(Camera const& cam) {
  if (mesh_ != nullptr) {
    texture_.bind();
    glLineWidth(2);
    uploadMvM(cam.getViewMat());
    mesh_->render();
    modelMat_ = rotate(modelMat_, radians(180.0), dvec3(0, 1, 0));
    uploadMvM(cam.getViewMat());
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

CuboTex::CuboTex(GLdouble l) {
  mesh_ = Mesh::generaCajaTexCor(l);
  texture_.load("..\\Bmps\\baldosaF.bmp");    // cargamos la imagen
  texture1_.load("..\\Bmps\\container.bmp");  // cargamos segunda imagen
}

CuboTex::~CuboTex() {
  delete mesh_;
  mesh_ = nullptr;
}

void CuboTex::render(Camera const& cam) {
  if (mesh_ != nullptr) {
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    texture_.bind();
    uploadMvM(cam.getViewMat());
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

Cristalera::Cristalera(GLdouble l) {
  mesh_ = Mesh::generaCajaTexCor(l);
  texture_.load("..\\Bmps\\cristalTri.bmp", 150);  // cargamos la imagen
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

Foto::Foto(GLdouble w, GLdouble h, GLuint rw, GLuint rh) {
  mesh_ = Mesh::generaRectanguloTexCor(w, h, rw, rh);
}

Foto::~Foto() {
  delete mesh_;
  mesh_ = nullptr;
}

void Foto::render(Camera const& cam) {
  if (mesh_ != nullptr) {
    texture_.loadColorBuffer();

    uploadMvM(cam.getViewMat());
    glLineWidth(1);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    texture_.bind();
    mesh_->render();
    texture_.unbind();
  }
}

void Foto::update() {}

Planta::Planta(GLdouble w, GLdouble h, GLuint rw, GLuint rh) {
  mesh_ = Mesh::generaRectanguloTexCor(w, h, rw, rh);
  texture_.load("..\\Bmps\\grass.bmp");
}

Planta::~Planta() {
  delete mesh_;
  mesh_ = nullptr;
}

void Planta::render(Camera const& cam) {
  if (mesh_ != nullptr) {
    const auto originalMat = getModelMat();
    glDepthMask(GL_FALSE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    auto auxMat = originalMat;
    auxMat = rotate(auxMat, radians((180.0 / 20)), dvec3(0.0, 1.0, 0.0));
    setModelMat(auxMat);
    uploadMvM(cam.getViewMat());
    texture_.bind();
    mesh_->render();
    texture_.unbind();
    setModelMat(originalMat);
    glLineWidth(1);
    glDepthMask(GL_TRUE);
  }
}

void Planta::update() {}

Piramide::Piramide(GLdouble l, GLdouble h) {
  mesh_ = Mesh::bipiramideExam(l, h);
  lado = l;
  altura = h * 2;
  alturaActual = 0;
  subiendo = true;
  auxMat_ = translate(modelMat_, dvec3(-l / 2, 0, -l / 2));
  texture_.load("..\\Bmps\\sierpinski.bmp", 100);
}

Piramide::~Piramide() {
  delete mesh_;
  mesh_ = nullptr;
}

void Piramide::render(Camera const& cam) {
  modelMat_ = auxMat_;  // para que no se desplace
  dmat4 aux = modelMat_;
  aux = translate(modelMat_, dvec3(lado, 0, 0));
  if (mesh_ != nullptr) {
    uploadMvM(cam.getViewMat());
    glLineWidth(2);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_FALSE);
    texture_.bind();
    mesh_->render();
    texture_.unbind();
    modelMat_ = rotate(aux, radians(180.0), dvec3(0, 0, 1));
    uploadMvM(cam.getViewMat());
    mesh_->render();
    aux = translate(modelMat_, dvec3(-lado, 0, 0));
    modelMat_ = rotate(aux, radians(-180.0), dvec3(0, 0, 1));
    glDisable(GL_LINE);
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
  }
}

void Piramide::update() {
  angulo += 2;
  auxMat_ = rotate(auxMat_, radians(5.), dvec3(1, 1, 0));
  if (alturaActual > altura || (alturaActual - 0.5 < -1)) {
    subiendo = !subiendo;
  }
  if (subiendo) {
    alturaActual += 0.5;
    auxMat_ = translate(auxMat_, dvec3(0, 0.5, 0));
  } else if (!subiendo) {
    alturaActual -= 0.5;
    auxMat_ = translate(auxMat_, dvec3(0, -0.5, 0));
  }
}
