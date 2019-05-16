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
}

LightSphere::~LightSphere() { delete spotLight_; }

SpotLight *LightSphere::getSpotLight() { return spotLight_; }

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
