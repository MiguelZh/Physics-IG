#include "CuboTex.h"

CuboTex::CuboTex(const GLdouble length) {
  mesh_ = Mesh::generaCajaTexCor(length);
  texture_.load("..\\Bmps\\baldosaF.bmp");
  texture1_.load("..\\Bmps\\container.bmp");
}

CuboTex::~CuboTex() {
  delete mesh_;
  mesh_ = nullptr;
}

void CuboTex::render(Camera const &camera) {
  if (mesh_ != nullptr) {
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    texture_.bind();
    uploadMvM(camera.getViewMat());
    glLineWidth(2);
    mesh_->render();
    texture_.unbind();

    glCullFace(GL_BACK);
    texture1_.bind();
    mesh_->render();
    texture1_.unbind();
    glDisable(GL_CULL_FACE);
  }
}

void CuboTex::update() {}
