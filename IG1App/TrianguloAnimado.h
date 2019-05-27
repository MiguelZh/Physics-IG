#pragma once
#include "Triangle.h"
class TrianguloAnimado final : public Triangle {
public:
  TrianguloAnimado(GLdouble vertices);
  ~TrianguloAnimado();
  void update() override;
};
