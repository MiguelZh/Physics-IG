#include "EntityMaterial.h"
#include "IndexMesh.h"
EntityMaterial::EntityMaterial() = default;
EntityMaterial::~EntityMaterial() = default;

void EntityMaterial::setTexture(Texture *text) { textureMatTexture_ = text; }

void EntityMaterial::setMaterial(Material *material) { material_ = material; }

Sphere::Sphere(const GLdouble radius, const std::string &text) {
  radius_ = radius;
  qObj = gluNewQuadric();
  texture_.load(text, 150);
  // gluQuadricNormals(qObj, GLU_SMOOTH);
  // gluQuadricOrientation(qObj, GLU_OUTSIDE);
  gluQuadricTexture(qObj, GL_TRUE);
}

Sphere::~Sphere() { gluDeleteQuadric(qObj); }

void Sphere::render(Camera const &camera) {
  material_->upload();
  glShadeModel(GL_SMOOTH); // Gouraud Shading
  glEnable(GL_CULL_FACE);
  texture_.bind(GL_MODULATE);
  uploadMvM(camera.getViewMat());
  gluSphere(qObj, radius_, 36, 36);
  texture_.unbind();

  glDisable(GL_CULL_FACE);
}

void Sphere::update() {}

LightSphere::LightSphere(GLdouble radius, const std::string &text,
                         glm::dvec3 pos)
    : Sphere(radius, text) {
  spotLight_ = new SpotLight();
  spotLight_->setPos(pos);
  spotLight_->setDir(glm::fvec3(100, 100, 0));
  spotLight_->uploadLI();
  spotLight_->enable();
  modelMat_ = glm::translate(getModelMat(), pos);
  B = radius_ * 2;
  A = 350;
  C = -1 * A;
}

LightSphere::~LightSphere() { delete spotLight_; }

SpotLight *LightSphere::getSpotLight() { return spotLight_; }

void LightSphere::render(Camera const &camera) {
  auxMat_ = modelMat_;
  glEnable(GL_CULL_FACE);
  // glShadeModel(GL_SMOOTH); // Gouraud Shading

  gluQuadricDrawStyle(qObj, GLU_FILL);
  texture_.bind(GL_MODULATE);
  uploadMvM(camera.getViewMat());
  gluSphere(qObj, radius_ * 1.5, 72, 72);
  texture_.unbind();

  setModelMat(
      glm::translate(getModelMat(), glm::dvec3(radius_*1.4, radius_*1.4, radius_*1.4)));

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
	setModelMat(glm::dmat4(1));
	auto aux = glm::rotate(getModelMat(), angle_ += glm::radians(10.), glm::dvec3(0, 0, 1.0));
	setModelMat(glm::dmat4(1));
	aux = glm::translate(aux, glm::dvec3(30 * cos(angle_), 30 * sin(angle_), 0));
	aux = rotate(aux, angle2_ -= glm::radians(25.5), glm::dvec3(0, 0, 1));
	setModelMat(aux);
}

CurvedTerrain::CurvedTerrain(GLdouble lado, GLuint numDiv,
                             const std::string &text) {
  indexMesh_ = IndexMesh::generateCurvedTerrain(lado, numDiv);
  texture_.load(text, 150);
}

CurvedTerrain::~CurvedTerrain() {
  delete indexMesh_;
  indexMesh_ = nullptr;
}

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
