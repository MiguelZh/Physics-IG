#include "Mesh.h"

using namespace glm;

// ReSharper disable StringLiteralTypo
// ReSharper disable IdentifierTypo

Mesh::~Mesh() {
  delete[] vertices;
  vertices = nullptr;
  delete[] colors;
  colors = nullptr;
}

void Mesh::render() const {
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
      glDisableClientState(GL_NORMAL_ARRAY);
    }

    glDrawArrays(primitive, 0,
                 numVertices);  // primitive graphic, first index and number of
                                // elements to be rendered

    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
  }
}

Mesh* Mesh::createRGBAxes(const GLdouble l) {
  const auto m = new Mesh();
  m->primitive = GL_LINES;
  m->numVertices = 6;

  m->vertices = new dvec3[m->numVertices];
  // X axis vertices
  m->vertices[0] = dvec3(0.0, 0.0, 0.0);
  m->vertices[1] = dvec3(l, 0.0, 0);
  // Y axis vertices
  m->vertices[2] = dvec3(0, 0.0, 0.0);
  m->vertices[3] = dvec3(0.0, l, 0.0);
  // Z axis vertices
  m->vertices[4] = dvec3(0.0, 0.0, 0.0);
  m->vertices[5] = dvec3(0.0, 0.0, l);

  m->colors = new dvec4[m->numVertices];
  // X axis color: red  ( Alpha = 1 : fully opaque)
  m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
  m->colors[1] = dvec4(1.0, 0.0, 0.0, 1.0);
  // Y axis color: green
  m->colors[2] = dvec4(0.0, 1.0, 0.0, 1.0);
  m->colors[3] = dvec4(0.0, 1.0, 0.0, 1.0);
  // Z axis color: blue
  m->colors[4] = dvec4(0.0, 0.0, 1.0, 1.0);
  m->colors[5] = dvec4(0.0, 0.0, 1.0, 1.0);

  return m;
}

Mesh* Mesh::generaPoliespiral(const dvec2 verIni, const GLdouble angIni,
                              const GLdouble incrAng, const GLdouble ladoIni,
                              const GLdouble incrLado, const GLuint numVert) {
  const auto poliespiral = new Mesh();
  poliespiral->primitive = GL_LINE_STRIP;
  poliespiral->numVertices = numVert;
  poliespiral->vertices = new dvec3[poliespiral->numVertices];
  auto length = ladoIni, angle = angIni;
  auto x = verIni.x;
  auto y = verIni.y;
  for (GLuint i = 0; i < poliespiral->numVertices; i++) {
    poliespiral->vertices[i] = dvec3(x, y, 0.0);
    x += length * cos(radians(angle));  // cos(radians(90))
    y += length * sin(radians(angle));
    length += incrLado;
    angle += incrAng;
  }
  return poliespiral;
}
//-------------------------------------------------------------------------
Mesh* Mesh::generaDragon(const GLuint numVert) {
  const auto dragon = new Mesh();
  dragon->primitive = GL_POINTS;
  dragon->numVertices = numVert;
  dragon->vertices = new dvec3[dragon->numVertices];
  double x = 0, y = 0;
  const auto pr1 = 0.787473;
  for (GLuint i = 0; i < dragon->numVertices; i++) {
    dragon->vertices[i] = dvec3(x, y, 0.0);
    const auto auxX = x;
    const auto auxY = y;
    if (rand() / double(RAND_MAX) < pr1) {
      x = 0.824074 * auxX + 0.281482 * auxY - 0.882290;
      y = -0.212346 * auxX + 0.864198 * auxY - 0.110607;
    } else {
      x = 0.088272 * auxX + 0.520988 * auxY + 0.785360;
      y = -0.463889 * auxX - 0.377778 * auxY + 8.095795;
    }  // T2
  }
  return dragon;
}

Mesh* Mesh::generaTriangulo(const GLdouble r) {
  const auto triangulo = new Mesh();
  triangulo->primitive = GL_TRIANGLES;
  triangulo->numVertices = 3;
  triangulo->vertices = new dvec3[triangulo->numVertices];
  const auto incrAng = 360.0 / 4.0;
  for (GLuint i = 0; i < triangulo->numVertices; i++) {
    const auto x = 0 + r * cos(90 + incrAng * i);
    const auto y = 0 + r * sin(90 + incrAng * i);
    triangulo->vertices[i] = dvec3(x, y, 0.0);
  }
  return triangulo;
}

Mesh* Mesh::generaTrianguloRGB(const GLdouble r) {
  const auto m = generaTriangulo(r);
  m->colors = new dvec4[m->numVertices];
  m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
  m->colors[1] = dvec4(0.0, 1.0, 0.0, 1.0);
  m->colors[2] = dvec4(0.0, 0.0, 1.0, 1.0);
  return m;
}

Mesh* Mesh::generaRectangulo(const GLdouble w, const GLdouble h,
                             const double ejeZ) {
  const auto rectangulo = new Mesh();
  rectangulo->primitive = GL_TRIANGLE_STRIP;
  rectangulo->numVertices = 4;
  rectangulo->vertices = new dvec3[rectangulo->numVertices];
  rectangulo->vertices[0] = dvec3(ejeZ, ejeZ, ejeZ);
  rectangulo->vertices[1] = dvec3(w, ejeZ, ejeZ);
  rectangulo->vertices[2] = dvec3(ejeZ, ejeZ, h);
  rectangulo->vertices[3] = dvec3(w, ejeZ, h);
  return rectangulo;
}

Mesh* Mesh::generaRectanguloRGB(const GLdouble w, const GLdouble h,
                                const double ejeZ) {
  const auto rectangulo = generaRectangulo(w, h, ejeZ);
  rectangulo->colors = new dvec4[rectangulo->numVertices];
  rectangulo->colors[0] = dvec4(0.25, 0.0, ejeZ, 1.0);
  rectangulo->colors[1] = dvec4(0.0, 0.5, ejeZ, 1.0);
  rectangulo->colors[2] = dvec4(0.0, 0.0, 0.75, 1.0);
  rectangulo->colors[3] = dvec4(1.0, 0.0, ejeZ, 1.0);
  return rectangulo;
}

Mesh* Mesh::generaEstrella3D(const GLdouble re, const GLdouble np,
                             const GLdouble h) {
  const auto estrella3D = new Mesh();
  estrella3D->primitive = GL_TRIANGLE_FAN;
  estrella3D->numVertices = static_cast<GLuint>(floor(2 * np + 2));
  estrella3D->vertices = new dvec3[estrella3D->numVertices];
  estrella3D->colors = new dvec4[estrella3D->numVertices];
  const dvec3 vo = {0, 0, 0};
  const auto ri = re / 2;
  double x, y;
  const double angle = 0;
  const auto incrAng = 360 / np / 2;
  for (GLuint i = 0; i < estrella3D->numVertices; i++) {
    if (i == 0) {
      estrella3D->vertices[i] = vo;
    } else if (i % 2 == 0) {
      x = re * cos(radians(angle + incrAng * i));
      y = re * sin(radians(angle + incrAng * i));
      estrella3D->vertices[i] = dvec3(x, y, h);
      estrella3D->colors[i] = dvec4(0.5, 0., 0., 1.);
    } else {
      x = ri * cos(radians(angle + incrAng * i));
      y = ri * sin(radians(angle + incrAng * i));
      estrella3D->vertices[i] = dvec3(x, y, 2 * h / 3);
      estrella3D->colors[i] = dvec4(0., 0., 0.5, 1.);
    }
  }

  return estrella3D;
}

Mesh* Mesh::generaContCubo(const GLdouble l) {
  const auto cube = new Mesh();
  cube->primitive = GL_TRIANGLE_STRIP;
  cube->numVertices = 10;
  cube->vertices = new dvec3[cube->numVertices];
  cube->colors = new dvec4[cube->numVertices];
  const double center = 0;
  cube->vertices[0] = dvec3(center, l, l);
  cube->colors[0] = dvec4(0, 0.7, 0, 0);
  cube->vertices[1] = dvec3(center, center, l);
  cube->colors[1] = dvec4(0, 0.7, 0, 0);
  cube->vertices[2] = dvec3(l, l, l);
  cube->colors[2] = dvec4(0, 0.7, 0, 0);
  cube->vertices[3] = dvec3(l, center, l);
  cube->colors[3] = dvec4(0, 0.7, 0, 0);
  cube->vertices[4] = dvec3(l, l, center);
  cube->colors[4] = dvec4(0, 0., 0.7, 0);
  cube->vertices[5] = dvec3(l, center, center);
  cube->colors[5] = dvec4(0, 0., 0.7, 0);
  cube->vertices[6] = dvec3(center, l, center);
  cube->colors[6] = dvec4(0, 0., 0.7, 0);
  cube->vertices[7] = dvec3(center, center, center);
  cube->colors[7] = dvec4(0, 0., 0.7, 0);
  cube->vertices[8] = dvec3(center, l, l);
  cube->colors[8] = dvec4(0.7, 0., 0.7, 0);
  cube->vertices[9] = dvec3(center, center, l);
  cube->colors[9] = dvec4(0.7, 0., 0.7, 0);
  return cube;
}

Mesh* Mesh::generaRectanguloTexCor(const GLdouble w, const GLdouble h,
                                   const GLuint rw, const GLuint rh) {
  const auto rectangle = new Mesh();
  rectangle->primitive = GL_TRIANGLE_STRIP;
  rectangle->numVertices = 4;
  rectangle->vertices = new dvec3[rectangle->numVertices];
  rectangle->vertices[0] = dvec3(0.0, 0.0, 0.0);
  rectangle->vertices[1] = dvec3(0.0, h, 0.0);
  rectangle->vertices[2] = dvec3(w, 0.0, 0.0);
  rectangle->vertices[3] = dvec3(w, h, 0.0);

  rectangle->textures = new dvec2[rectangle->numVertices];
  rectangle->textures[0] = dvec2(0.0, 0.0);
  rectangle->textures[1] = dvec2(0.0, rh);
  rectangle->textures[2] = dvec2(rw, 0.0);
  rectangle->textures[3] = dvec2(rw, rh);
  return rectangle;
}

Mesh* Mesh::generaEstrellaTexCor(const GLdouble r, const GLdouble nL,
                                 const GLdouble h) {
  const auto estrella3D = new Mesh();
  estrella3D->primitive = GL_TRIANGLE_FAN;
  estrella3D->numVertices = static_cast<GLuint>(floor(2 * nL + 2));
  estrella3D->vertices = new dvec3[estrella3D->numVertices];
  estrella3D->colors = new dvec4[estrella3D->numVertices];
  estrella3D->textures = new dvec2[estrella3D->numVertices];
  const dvec3 vo = {0, 0, 0};
  const auto ri = r / 2.0;
  double x, y;
  const auto angle = 0.0;
  const auto incrAng = 360.0 / nL / 2.0;
  for (GLuint i = 0; i < estrella3D->numVertices; i++) {
    if (i == 0) {
      estrella3D->vertices[i] = vo;
      estrella3D->textures[i] = vo;
    } else if (i % 2 == 0) {
      x = r * cos(radians(angle + incrAng * i));
      y = r * sin(radians(angle + incrAng * i));
      estrella3D->vertices[i] = dvec3(x, y, h);
      estrella3D->colors[i] = dvec4(0.5, 0., 0., 1.);
      estrella3D->textures[i] = dvec2(x / (r * 2), y / (h * 2));
    } else {
      x = ri * cos(radians(angle + incrAng * i));
      y = ri * sin(radians(angle + incrAng * i));
      estrella3D->vertices[i] = dvec3(x, y, 2 * h / 3);
      estrella3D->colors[i] = dvec4(0., 0., 0.5, 1.);
      estrella3D->textures[i] = dvec2(x / (r * 2), y / (h * 2));
    }
  }
  return estrella3D;
}

Mesh* Mesh::generaCajaTexCor(const GLdouble l) {
  const auto cube = new Mesh();
  cube->primitive = GL_TRIANGLE_STRIP;
  cube->numVertices = 10;
  cube->vertices = new dvec3[cube->numVertices];
  cube->colors = new dvec4[cube->numVertices];
  cube->textures = new dvec2[cube->numVertices];

  const double center = 0;
  cube->vertices[0] = dvec3(center, l, l);
  cube->vertices[1] = dvec3(center, center, l);
  cube->vertices[2] = dvec3(l, l, l);
  cube->vertices[3] = dvec3(l, center, l);
  cube->vertices[4] = dvec3(l, l, center);
  cube->vertices[5] = dvec3(l, center, center);
  cube->vertices[6] = dvec3(center, l, center);
  cube->vertices[7] = dvec3(center, center, center);
  cube->vertices[8] = cube->vertices[0];
  cube->vertices[9] = cube->vertices[1];

  cube->textures[0] = dvec2(0, 1);
  cube->textures[1] = dvec2(0, 0);
  cube->textures[2] = dvec2(1, 1);
  cube->textures[3] = dvec2(1, 0);
  cube->textures[4] = dvec2(2, 1);
  cube->textures[5] = dvec2(2, 0);
  cube->textures[6] = dvec2(3, 1);
  cube->textures[7] = dvec2(3, 0);
  cube->textures[8] = dvec2(4, 1);
  cube->textures[9] = dvec2(4, 0);
  return cube;
}

Mesh* Mesh::bipiramideExam(const GLdouble l, const GLdouble h) {
  const auto halfL = l / 2.0;
  const auto m = new Mesh();
  m->primitive = GL_TRIANGLES;
  m->numVertices = 12;
  m->colors = new dvec4[m->numVertices];
  m->vertices = new dvec3[m->numVertices];
  m->textures = new dvec2[m->numVertices];
  // 1er
  m->vertices[0] = dvec3(0, 0, 0);
  m->vertices[1] = dvec3(l, 0, 0);
  m->vertices[2] = dvec3(halfL, h, halfL);  // center point of the pyramid
  // 2er
  m->vertices[3] = dvec3(0, 0, 0);
  m->vertices[4] = dvec3(0, 0, l);
  m->vertices[5] = dvec3(halfL, h, halfL);
  // 3er
  m->vertices[6] = dvec3(0, 0, l);
  m->vertices[7] = dvec3(l, 0, l);
  m->vertices[8] = dvec3(halfL, h, halfL);
  // 4er
  m->vertices[9] = dvec3(l, 0, l);
  m->vertices[10] = dvec3(l, 0, 0);
  m->vertices[11] = dvec3(halfL, h, halfL);

  // Textures
  const auto textL = halfL;
  const auto halfH = h / 2;
  m->textures[0] = dvec2(0, 0);
  m->textures[1] = dvec2(textL, 0);
  m->textures[2] = dvec2(halfL, halfH);
  m->textures[3] = dvec2(0, 0);
  m->textures[4] = dvec2(0, 0);
  m->textures[5] = dvec2(halfL, halfH);
  m->textures[6] = dvec2(textL, 0);
  m->textures[7] = dvec2(0, 0);
  m->textures[8] = dvec2(halfL, halfH);
  m->textures[9] = dvec2(textL, 0);
  m->textures[10] = dvec2(textL, 0);
  m->textures[11] = dvec2(halfL, halfH);

  // Random Colors
  m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
  m->colors[1] = dvec4(1.0, 0.0, 0.0, 1.0);
  m->colors[2] = dvec4(1.0, 0.0, 0.0, 1.0);
  m->colors[3] = dvec4(0.0, 1.0, 0.0, 1.0);
  m->colors[4] = dvec4(0.0, 1.0, 0.0, 1.0);
  m->colors[5] = dvec4(0.0, 1.0, 0.0, 1.0);
  m->colors[6] = dvec4(0.0, 0.0, 1.0, 1.0);
  m->colors[7] = dvec4(0.0, 0.0, 1.0, 1.0);
  m->colors[8] = dvec4(0.0, 0.0, 1.0, 1.0);
  m->colors[9] = dvec4(0.5, 0.5, 0.0, 1.0);
  m->colors[10] = dvec4(0.5, 0.5, 0.0, 1.0);
  m->colors[11] = dvec4(0.5, 0.5, 0.0, 1.0);
  return m;
}
