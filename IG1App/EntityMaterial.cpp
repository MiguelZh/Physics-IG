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

LightSphere::LightSphere(GLdouble radius,const glm::dvec3 pos) : Sphere(radius,""){
    spotLight_ = new SpotLight();
    spotLight_->setDir(glm::fvec3(0, -1, 0));
    spotLight_->setPos(pos);
    spotLight_->setAngle(180.);
    spotLight_->uploadLI();
    spotLight_->enable();
}

LightSphere::~LightSphere() {
    delete spotLight_;
}

