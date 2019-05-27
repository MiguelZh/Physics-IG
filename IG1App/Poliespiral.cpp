#include "Poliespiral.h"

Poliespiral::Poliespiral(const glm::dvec2 verIni, const GLdouble angIni,
                         const GLdouble incrAng, const GLdouble ladoIni,
                         const GLdouble incrLado, const GLuint numVert) {
  mesh_ = Mesh::generaPoliespiral(verIni, angIni, incrAng, ladoIni, incrLado,
                                  numVert);
}

Poliespiral::~Poliespiral() {
  delete mesh_;
  mesh_ = nullptr;
}

void Poliespiral::render(Camera const &cam) {
  if (mesh_ != nullptr) {
    glColor3d(0, 0, 1);
    uploadMvM(cam.getViewMat());
    glLineWidth(2);
    mesh_->render();
  }
}

void Poliespiral::update() {}
