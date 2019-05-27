#include "Piramide.h"

Piramide::Piramide(const GLdouble length, const GLdouble height) {
  mesh_ = Mesh::bipiramideExam(length, height);
  side_ = length;
  height_ = height * 2;
  currentHeight_ = 0;
  movingUp_ = true;
  angle_ = 0.0;
  auxMat_ = translate(modelMat_, dvec3(-length / 2, 0, -length / 2));
  texture_.load("..\\Bmps\\sierpinski.bmp", 100);
}

Piramide::~Piramide() {
  delete mesh_;
  mesh_ = nullptr;
}

void Piramide::render(Camera const &camera) {
  modelMat_ = auxMat_;
  auto aux = translate(modelMat_, dvec3(side_, 0, 0));
  if (mesh_ != nullptr) {
    uploadMvM(camera.getViewMat());
    glLineWidth(2);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_FALSE);
    texture_.bind();
    mesh_->render();
    texture_.unbind();
    modelMat_ = rotate(aux, radians(180.0), dvec3(0, 0, 1));
    uploadMvM(camera.getViewMat());
    mesh_->render();
    aux = translate(modelMat_, dvec3(-side_, 0, 0));
    modelMat_ = rotate(aux, radians(-180.0), dvec3(0, 0, 1));
    glDisable(GL_LINE);
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
  }
}

void Piramide::update() {
  angle_ += 2;
  auxMat_ = rotate(auxMat_, radians(5.), dvec3(1, 1, 0));
  if (currentHeight_ > height_ || (currentHeight_ - 0.5 < -1)) {
    movingUp_ = !movingUp_;
  }
  if (movingUp_) {
    currentHeight_ += 0.5;
    auxMat_ = translate(auxMat_, dvec3(0, 0.5, 0));
  } else if (!movingUp_) {
    currentHeight_ -= 0.5;
    auxMat_ = translate(auxMat_, dvec3(0, -0.5, 0));
  }
}
