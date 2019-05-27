#include "Cristalera.h"

Cristalera::Cristalera(const GLdouble length) {
  mesh_ = Mesh::generaCajaTexCor(length);
  texture_.load("..\\Bmps\\cristalTri.bmp", 150);
}

Cristalera::~Cristalera() {
  delete mesh_;
  mesh_ = nullptr;
}

void Cristalera::render(Camera const &cam) {
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
