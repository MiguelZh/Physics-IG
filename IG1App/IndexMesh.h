#pragma once
#include "Mesh.h"

class IndexMesh final : public Mesh {
  GLuint* indexes_ = nullptr;
  GLuint indexCount_ = 0;

 public:
  IndexMesh();
  ~IndexMesh();
  void render() const;
  static IndexMesh* generateGrid(GLdouble side, GLuint numDiv);
  static IndexMesh* generateGridTex(GLdouble side, GLuint numDiv);
  static IndexMesh* generateCurvedTerrain(GLdouble side, GLuint numDiv);
};
