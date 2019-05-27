#include "TrianguloAnimado.h"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

using namespace glm;

TrianguloAnimado::TrianguloAnimado(const GLdouble vertices)
    : Triangle(vertices) {}

TrianguloAnimado::~TrianguloAnimado() {
  delete mesh_;
  mesh_ = nullptr;
}

void TrianguloAnimado::update() {
  setModelMat(dmat4(1));
  auto aux = rotate(getModelMat(), angle_ += radians(10.), dvec3(0, 0, 1.0));
  setModelMat(dmat4(1));
  aux = translate(aux, dvec3(30 * cos(angle_), 30 * sin(angle_), 0));
  aux = rotate(aux, angle2_ -= radians(25.5), dvec3(0, 0, 1));
  setModelMat(aux);
}
