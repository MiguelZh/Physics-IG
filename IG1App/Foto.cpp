#include "Foto.h"

Foto::Foto(const GLdouble width, const GLdouble height, const GLuint rowWidth,
           const GLuint rowHeight) {
  mesh_ = Mesh::generaRectanguloTexCor(width, height, rowWidth, rowHeight);
}

Foto::~Foto() {
  delete mesh_;
  mesh_ = nullptr;
}

auto Foto::render(Camera const &camera) -> void {
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
