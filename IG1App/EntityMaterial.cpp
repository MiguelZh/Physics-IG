#include "EntityMaterial.h"

EntityMaterial::EntityMaterial() = default;
EntityMaterial::~EntityMaterial() = default;

void EntityMaterial::setTexture(Texture* text) { textureMatTexture_ = text; }

void EntityMaterial::setMaterial(Material* material) { material_ = material; }

Sphere::Sphere(const GLdouble radius, const std::string& text) {
  radius_ = radius;
  qObj = gluNewQuadric();
  texture_.load(text, 150);
  gluQuadricDrawStyle(qObj, GLU_FILL);
  gluQuadricNormals(qObj, GLU_SMOOTH);
  gluQuadricOrientation(qObj, GLU_OUTSIDE);
  gluQuadricTexture(qObj, GL_TRUE);
}

Sphere::~Sphere() { gluDeleteQuadric(qObj); }

void Sphere::render(Camera const& camera) {
  uploadMvM(camera.getViewMat());
  glEnable(GL_CULL_FACE);
  texture_.bind();
  gluSphere(qObj, radius_, 36, 36);
  Texture::unbind();

  glDisable(GL_CULL_FACE);
}

void Sphere::update() {}
