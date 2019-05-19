#pragma once
#include "Mesh.h"

class IndexMesh final : public Mesh {
  GLuint* indexes_ = nullptr;
  GLuint indexCount_ = 0;

 public:
  IndexMesh();
  ~IndexMesh();
  void render();
  static IndexMesh* generateGrid(GLdouble lado, GLuint numDiv);
  static IndexMesh* generateGridTex(GLdouble lado, GLuint numDiv);
  static IndexMesh* generateCurvedTerrain(GLdouble lado, GLuint numDiv);
};
