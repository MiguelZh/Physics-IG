#pragma once
#include "Mesh.h"
class IndexMesh : public Mesh {
  GLuint* indices_ = nullptr;
  GLuint numIndices = 0;

 public:
  IndexMesh();
  ~IndexMesh();
  virtual void render();
  static IndexMesh* generateGridTex(GLdouble lado, GLuint numDiv);
};
