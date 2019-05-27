#include "Estrella3D.h"

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

void Estrella3D::render(Camera const &camera) {
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
