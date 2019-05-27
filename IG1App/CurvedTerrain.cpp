#include "CurvedTerrain.h"

CurvedTerrain::CurvedTerrain(const GLdouble side, const GLuint numDiv,
                             const std::string &text)
    : EntityMaterial() {
  indexMesh_ = IndexMesh::generateCurvedTerrain(side, numDiv);
  texture_.load(text, 150);
}

CurvedTerrain::~CurvedTerrain() = default;

void CurvedTerrain::render(Camera const &camera) {
  if (indexMesh_ != nullptr) {
    // glEnable(GL_CULL_FACE);
    uploadMvM(camera.getViewMat());
    material_->upload();
    texture_.bind(GL_MODULATE);
    indexMesh_->render();
    texture_.unbind();
    // glDisable(GL_CULL_FACE);
  }
}

void CurvedTerrain::update() {}
