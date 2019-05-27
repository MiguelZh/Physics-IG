#include "Dragon.h"

Dragon::Dragon(const GLuint vertices) { mesh_ = Mesh::generaDragon(vertices); }

Dragon::~Dragon() {
  delete mesh_;
  mesh_ = nullptr;
}

void Dragon::render(Camera const &camera) {
  if (mesh_ != nullptr) {
    glColor3d(0.5, 0.0, 0.5);
    glPointSize(2);
    uploadMvM(camera.getViewMat());
    mesh_->render();
  }
}

void Dragon::update() {}
