#include "IndexMesh.h"

IndexMesh::IndexMesh() : Mesh() { primitive = GL_TRIANGLES; }

IndexMesh::~IndexMesh() { delete[] indices_; }

void IndexMesh::render() {
  // comandos OpenGL para enviar los datos de los arrays a la GPU (Mesh)
  // Los comandos para la nueva tabla de �ndices:
  glEnableClientState(GL_INDEX_ARRAY);
  glIndexPointer(GL_UNSIGNED_INT, 0, indices_);
  // Comando para renderizar la malla indexada enviada
  glDrawElements(primitive, numIndices, GL_UNSIGNED_INT, indices_);
  // comandos OpenGL para deshabilitar los datos enviados a la GPU (Mesh)
  // El comando para la nueva tabla de �ndices:
  glDisableClientState(GL_INDEX_ARRAY);
}

IndexMesh* IndexMesh::generateGridTex(
    GLdouble lado,
    GLuint numDiv) {  // Grid cuadrado de lado*lado, centrado en el plano Y=0,
  // dividido en numDiv*numDiv celdas (cada celda son 2 tri�ngulos)
  IndexMesh* m = new IndexMesh();
  GLdouble incr = lado / numDiv;  // incremento para la coordenada x, y la c. z
  GLuint numFC = numDiv + 1;      // n�mero de v�rtices por filas y columnas
  // generar v�rtices
  m->numVertices = numFC * numFC;  // n�mero de v�rtices
  m->vertices = new glm::dvec3[m->numVertices];
  // ->
  // ->
  // generar �ndices
  m->numIndices = numDiv * numDiv * 6;  // n�mero de �ndices
  m->indices_ = new GLuint[m->numIndices];
  // ->
  return m;
}
