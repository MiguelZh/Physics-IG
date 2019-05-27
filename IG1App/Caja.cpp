#include "Caja.h"

Caja::Caja(const GLdouble length) { mesh_ = Mesh::generaContCubo(length); }

Caja::~Caja() {
  delete mesh_;
  mesh_ = nullptr;
}

void Caja::render(Camera const &camera) {
  if (mesh_ != nullptr) {
    // glColor3d(0, 1, 0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glLineWidth(2);
    uploadMvM(camera.getViewMat());
    mesh_->render();
  }
}

void Caja::update() {}
