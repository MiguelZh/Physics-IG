#include "IndexMesh.h"

IndexMesh::IndexMesh() { primitive = GL_TRIANGLES; }

IndexMesh::~IndexMesh() { delete[] indexes_; }

void IndexMesh::render() const {
  if (vertices != nullptr) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0,
                    vertices);  // Number of coordinates per vertex, type of
                                // each coordinate, stride, pointer
    if (colors != nullptr) {
      glEnableClientState(GL_COLOR_ARRAY);
      glColorPointer(4, GL_DOUBLE, 0,
                     colors);  // Number of coordinates per color, type of each
                               // coordinate, stride, pointer
    }
    if (textures != nullptr) {
      glEnableClientState(GL_TEXTURE_COORD_ARRAY);
      glTexCoordPointer(2, GL_DOUBLE, 0, textures);
    }
    if (normals != nullptr) {
      glEnableClientState(GL_NORMAL_ARRAY);
      glNormalPointer(GL_DOUBLE, 0, normals);
    }
    // OpenGL commands to send the arrays' data to the GPU (Mesh)
    // The commands for the new index array:
    glEnableClientState(GL_INDEX_ARRAY);
    glIndexPointer(GL_UNSIGNED_INT, 0, indexes_);
    // Command to render the sent indexed mesh
    glDrawElements(primitive, indexCount_, GL_UNSIGNED_INT, indexes_);
    // OpenGL commands to disable the data sent to the GPU (Mesh)
    glDisableClientState(GL_INDEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
  }
}

IndexMesh *IndexMesh::generateGrid(const GLdouble side, const GLuint numDiv) {
  const auto m = new IndexMesh();
  m->primitive = GL_TRIANGLES;
  const auto incr = side / numDiv;  // Increment for each coordinate
  const auto numFc = numDiv + 1;    // Number of vertexes for rows and columns
  // Generate vertexes
  m->numVertices = numFc * numFc;  // Number of vertexes
  m->vertices = new glm::dvec3[m->numVertices];

  for (GLuint f = 0; f < numFc; f++) {
    for (GLuint c = 0; c < numFc; c++) {
      m->vertices[f * numFc + c] =
          glm::dvec3((-side / 2) + c * incr, 0, (-side / 2) + f * incr);
    }
  }
  m->indexCount_ = numDiv * numDiv * 6;  // Number of indexes
  m->indexes_ = new GLuint[m->indexCount_];

  GLuint i = 0;  // Index array
  for (GLuint h = 0; h < numDiv; h++) {
    for (GLuint k = 0; k < numDiv; k++) {
      const auto iv = h * numFc + k;
      m->indexes_[i++] = iv;
      m->indexes_[i++] = iv + numFc;
      m->indexes_[i++] = iv + 1;
      m->indexes_[i++] = iv + 1;
      m->indexes_[i++] = iv + numFc;
      m->indexes_[i++] = iv + numFc + 1;
    }
  }
  return m;
}
IndexMesh *IndexMesh::generateGridTex(const GLdouble side,
                                      const GLuint numDiv) {
  const auto m = generateGrid(side, numDiv);
  const auto numFc = numDiv + 1;  // Number of vertexes for rows and columns
  m->textures = new glm::dvec2[m->numVertices];

  for (GLuint f = 0; f < numFc; f++) {
    for (GLuint c = 0; c < numFc; c++) {
      m->textures[f * numFc + c] =
          glm::dvec2(1 + c * 1.0 / numDiv, 1 - f * 1.0 / numDiv);
    }
  }

  return m;
}

IndexMesh *IndexMesh::generateCurvedTerrain(const GLdouble side,
                                            const GLuint numDiv) {
  const auto m = generateGridTex(side, numDiv);
  const auto curvature = 0.5;
  m->normals = new glm::dvec3[m->numVertices];
  for (GLuint j = 0; j < m->numVertices; j++) {
    // Modify the y ordinate from each vertex with the equation
    m->vertices[j].y =
        side * curvature / 2 -
        curvature / side * (m->vertices[j].x * m->vertices[j].x) -
        curvature / side * (m->vertices[j].z * m->vertices[j].z);
    m->normals[j] =
        normalize(glm::dvec3(2 * curvature / side * m->vertices[j].x, 1.0,
                             2 * curvature / side * m->vertices[j].z));
  }
  return m;
}
