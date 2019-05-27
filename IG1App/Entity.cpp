#include "Entity.h"

// ReSharper disable StringLiteralTypo
// ReSharper disable IdentifierTypo

void Entity::uploadMvM(dmat4 const &modelViewMat) const {
  auto aMat = modelViewMat * modelMat_;
  glMatrixMode(GL_MODELVIEW);
  glLoadMatrixd(value_ptr(aMat));
}






