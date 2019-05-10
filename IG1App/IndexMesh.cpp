#include "IndexMesh.h"

IndexMesh::IndexMesh() : Mesh() { primitive = GL_TRIANGLES; }

IndexMesh::~IndexMesh() { delete[] indices_; }

void IndexMesh::render() {
  // comandos OpenGL para enviar los datos de los arrays a la GPU (Mesh)
  // Los comandos para la nueva tabla de índices:
  glEnableClientState(GL_INDEX_ARRAY);
  glIndexPointer(GL_UNSIGNED_INT, 0, indices_);
  // Comando para renderizar la malla indexada enviada
  glDrawElements(primitive, numIndices, GL_UNSIGNED_INT, indices_);
  // comandos OpenGL para deshabilitar los datos enviados a la GPU (Mesh)
  // El comando para la nueva tabla de índices:
  glDisableClientState(GL_INDEX_ARRAY);
}

IndexMesh* IndexMesh::generateGridTex(
    GLdouble lado,
    GLuint numDiv) {  // Grid cuadrado de lado*lado, centrado en el plano Y=0,
  // dividido en numDiv*numDiv celdas (cada celda son 2 triángulos)
  IndexMesh* m = new IndexMesh();
  GLdouble incr = lado / numDiv;  // incremento para la coordenada x, y la c. z
  GLuint numFC = numDiv + 1;      // número de vértices por filas y columnas
  // generar vértices
  m->numVertices = numFC * numFC;  // número de vértices
  m->vertices = new glm::dvec3[m->numVertices];
  // ->
  // ->
  // generar índices
  m->numIndices = numDiv * numDiv * 6;  // número de índices
  m->indices_ = new GLuint[m->numIndices];
  // ->
  return m;
}
