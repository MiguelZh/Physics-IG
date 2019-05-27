#include "Triangle.h"

Triangle::Triangle(const GLdouble vertices) {
  mesh_ = Mesh::generaTrianguloRGB(vertices);
}

Triangle::~Triangle() {
  delete mesh_;
  mesh_ = nullptr;
}

auto Triangle::render(Camera const &camera) -> void {
  if (mesh_ != nullptr) {
    glLineWidth(2);
    uploadMvM(camera.getViewMat());
    mesh_->render();
  }
}

void Triangle::update() {}
