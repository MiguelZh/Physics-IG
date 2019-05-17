#include "IndexMesh.h"

IndexMesh::IndexMesh() : Mesh() { primitive = GL_TRIANGLES; }

IndexMesh::~IndexMesh() { delete[] indices_; }

void IndexMesh::render() {
	if (vertices != nullptr) {
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_DOUBLE, 0,
			vertices);  // number of coordinates per vertex, type of
						// each coordinate, stride, pointer
		if (colors != nullptr) {
			glEnableClientState(GL_COLOR_ARRAY);
			glColorPointer(4, GL_DOUBLE, 0,
				colors);  // number of coordinates per color, type of each
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
		// comandos OpenGL para enviar los datos de los arrays a la GPU (Mesh)
		// Los comandos para la nueva tabla de índices:
		glEnableClientState(GL_INDEX_ARRAY);
		glIndexPointer(GL_UNSIGNED_INT, 0, indices_);
		// Comando para renderizar la malla indexada enviada
		glDrawElements(primitive, numIndices, GL_UNSIGNED_INT, indices_);
		// comandos OpenGL para deshabilitar los datos enviados a la GPU (Mesh)
		// El comando para la nueva tabla de índices:
		glDisableClientState(GL_INDEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_NORMAL_ARRAY);

	}
}

IndexMesh *IndexMesh::generateGrid(GLdouble lado, GLuint numDiv) {
  IndexMesh *m = new IndexMesh();
  m->primitive = GL_TRIANGLES;
  GLdouble incr = lado / numDiv; // incremento para la coordenada x, y la c. z
  GLuint numFC = numDiv + 1;     // número de vértices por filas y columnas
  // generar vértices
  m->numVertices = numFC * numFC; // número de vértices
  m->vertices = new glm::dvec3[m->numVertices];

  for (int f = 0; f < numFC; f++) {
    for (int c = 0; c < numFC; c++) {
      m->vertices[f * numFC + c] =
          glm::dvec3((-lado / 2) + c * incr, 0, (-lado / 2) + f * incr);
    }
  }
  m->numIndices = numDiv * numDiv * 6; // número de índices
  m->indices_ = new GLuint[m->numIndices];

  GLuint i = 0; // array de índices
  for (int h = 0; h < numDiv; h++) {
    for (int k = 0; k < numDiv; k++) {
      GLuint iv = h * numFC + k;
      m->indices_[i++] = iv;
      m->indices_[i++] = iv + numFC;
      m->indices_[i++] = iv + 1;
      m->indices_[i++] = iv + 1;
      m->indices_[i++] = iv + numFC;
      m->indices_[i++] = iv + numFC + 1;
    }
  }
  return m;
}
IndexMesh *IndexMesh::generateGridTex(GLdouble lado, GLuint numDiv) {
  IndexMesh *m = generateGrid(lado, numDiv);
  GLuint numFC = numDiv + 1; // número de vértices por filas y columnas
  // generar coordenadas de textura
  m->textures = new glm::dvec2[m->numVertices];

  for (int f = 0; f < numFC; f++) {
    for (int c = 0; c < numFC; c++) {
      m->textures[f * numFC + c] = glm::dvec2(1 + c * 1.0 / numDiv,
                                              1 - f * 1.0 / numDiv);
    }
  }

  return m;
}

IndexMesh *IndexMesh::generateCurvedTerrain(GLdouble lado, GLuint numDiv) {
  IndexMesh *m = generateGridTex(lado, numDiv);
  GLdouble curvatura = 0.5;
  m->normals = new glm::dvec3[m->numVertices];
  for (int j = 0; j < m->numVertices; j++) {
    // modificar la coordenada Y de los vértices con la ecuación
    m->vertices[j] = glm::dvec3(
        m->vertices[j].x,
        lado * curvatura / 2 -
            curvatura / lado * (m->vertices[j].x * m->vertices[j].x) -
            curvatura / lado * (m->vertices[j].z * m->vertices[j].z),
        m->vertices[j].z);
    m->normals[j] =
        glm::normalize(glm::dvec3(2 * curvatura / lado * m->vertices[j].x, 1.,
                                  2 * curvatura / lado * m->vertices[j].z));
  }
  return m;
}
