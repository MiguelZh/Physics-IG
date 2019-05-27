#include "Estrella3DTex.h"

Estrella3DTex::Estrella3DTex(const GLdouble r, const GLdouble nL,
                             const GLdouble height) {
  mesh_ = Mesh::generaEstrellaTexCor(r, nL, height);
  texture_.load("..\\Bmps\\baldosaP.bmp");
}

Estrella3DTex::~Estrella3DTex() {
  delete mesh_;
  mesh_ = nullptr;
}

void Estrella3DTex::render(Camera const &camera) {
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
