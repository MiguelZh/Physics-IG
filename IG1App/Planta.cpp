#include "Planta.h"

Planta::Planta(const GLdouble width, const GLdouble height,
               const GLuint rowWidth, const GLuint rowHeight) {
  mesh_ = Mesh::generaRectanguloTexCor(width, height, rowWidth, rowHeight);
  texture_.load("..\\Bmps\\grass.bmp");
}

Planta::~Planta() {
  delete mesh_;
  mesh_ = nullptr;
}

void Planta::render(Camera const &camera) {
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
