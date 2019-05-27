#include "RectangleTex.h"

RectangleTex::RectangleTex(const GLdouble width, const GLdouble height,
                           const GLuint rowWidth, const GLuint rowHeight) {
  mesh_ = Mesh::generaRectanguloTexCor(width, height, rowWidth, rowHeight);
  texture_.load("..\\Bmps\\baldosaC.bmp");
}

RectangleTex::~RectangleTex() {
  delete mesh_;
  mesh_ = nullptr;
}

void RectangleTex::render(Camera const &camera) {
  if (mesh_ != nullptr) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    texture_.bind();
    glColor3d(0.0, 0.0, 1.0);
    uploadMvM(camera.getViewMat());
    mesh_->render();
    texture_.unbind();
  }
}

void RectangleTex::update() {}
