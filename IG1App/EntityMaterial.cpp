#include "EntityMaterial.h"
#include "IndexMesh.h"

EntityMaterial::EntityMaterial() = default;

EntityMaterial::~EntityMaterial() {
  delete indexMesh_;
  delete textureMatTexture_;
  delete material_;
}

void EntityMaterial::setTexture(Texture *text) { textureMatTexture_ = text; }

void EntityMaterial::setMaterial(Material *material) { material_ = material; }

Sphere::Sphere(const GLdouble radius, const std::string &text) {
  radius_ = radius;
  qObj = gluNewQuadric();
  texture_.load(text, 150);
  gluQuadricTexture(qObj, GL_TRUE);
}

Sphere::~Sphere() { gluDeleteQuadric(qObj); }

void Sphere::render(Camera const &camera) {
  material_->upload();
  glShadeModel(GL_SMOOTH);  // Gouraud Shading
  glEnable(GL_CULL_FACE);
  texture_.bind(GL_MODULATE);
  uploadMvM(camera.getViewMat());
  gluSphere(qObj, radius_, 36, 36);
  texture_.unbind();

  glDisable(GL_CULL_FACE);
}

void Sphere::update() {}

LightSphere::LightSphere(const GLdouble radius, const std::string &text,
                         const glm::dvec3 pos)
    : Sphere(radius, text),
      a_(350),
      b_(static_cast<GLuint>(radius_ * 2)),
      c_(-15) {
  spotLight_ = new SpotLight();
  spotLight_->setPos(pos);
  spotLight_->setDir(glm::fvec3(100, 100, 0));
  spotLight_->uploadLI();
  spotLight_->enable();
  modelMat_ = translate(getModelMat(), pos);
}

LightSphere::~LightSphere() { delete spotLight_; }

SpotLight *LightSphere::getSpotLight() const { return spotLight_; }

void LightSphere::render(Camera const &camera) {
  auxMat_ = modelMat_;
  glEnable(GL_CULL_FACE);
  glShadeModel(GL_SMOOTH);  // Gouraud Shading

  gluQuadricDrawStyle(qObj, GLU_FILL);
  texture_.bind(GL_MODULATE);
  uploadMvM(camera.getViewMat());
  gluSphere(qObj, radius_ * 1.5, 72, 72);
  texture_.unbind();

  if (rotationAngle_ > 90) {
    rotationAngle_ -= 0.05;
  } else
    rotationAngle_ += 0.05;
  setModelMat(glm::translate(
      getModelMat(), glm::dvec3(radius_ * 1.4, radius_ * 1.4, radius_ * 1.4)));
  setModelMat(glm::translate(getModelMat(),
                             glm::dvec3(radius_ * 0.8 * 2 * cos(rotationAngle_),
                                        -radius_ * sin(rotationAngle_), 0)));

  material_->upload();
  gluQuadricDrawStyle(qObj, GLU_LINE);
  texture_.bind(GL_MODULATE);
  uploadMvM(camera.getViewMat());
  gluSphere(qObj, radius_, 36, 36);
  texture_.unbind();

  spotLight_->upload(camera.getViewMat());

  glDisable(GL_CULL_FACE);

  modelMat_ = auxMat_;

  glDisable(GL_CULL_FACE);
}

void LightSphere::update() {
  angle_ += 0.05;
  if (angle_ >= 360.0) angle_ -= 360.0;

  const auto x = a_ * cos(angle_);
  const auto y = b_ * sin(angle_) * sin(angle_) + 150.0;
  const auto z = -350.0 * sin(angle_) * cos(angle_);
  const auto position = glm::dvec3(x, y, z);
  spotLight_->setPos(position);
  setModelMat(translate(glm::dmat4(1.0), position));
}

CurvedTerrain::CurvedTerrain(const GLdouble side, const GLuint numDiv,
                             const std::string &text) {
  indexMesh_ = IndexMesh::generateCurvedTerrain(side, numDiv);
  texture_.load(text, 150);
}

CurvedTerrain::~CurvedTerrain() = default;

void CurvedTerrain::render(Camera const &camera) {
  if (indexMesh_ != nullptr) {
    // glEnable(GL_CULL_FACE);
    uploadMvM(camera.getViewMat());
    material_->upload();
    texture_.bind(GL_MODULATE);
    indexMesh_->render();
    texture_.unbind();
    // glDisable(GL_CULL_FACE);
  }
}

void CurvedTerrain::update() {}
