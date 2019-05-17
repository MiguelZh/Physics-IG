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
	qObjSmall = gluNewQuadric();
  spotLight_ = new SpotLight();
  spotLight_->setPos(pos);
  spotLight_->setDir(glm::fvec3(100, 100, 0));
  spotLight_->uploadLI();
  spotLight_->enable();
  modelMat_ = glm::translate(getModelMat(), pos);
}

LightSphere::~LightSphere() { delete spotLight_; }

SpotLight *LightSphere::getSpotLight() { return spotLight_; }

void LightSphere::render(Camera const & camera)
{
	glEnable(GL_CULL_FACE);
	glShadeModel(GL_SMOOTH); // Gouraud Shading
	GLuint B = radius_ * 2;
	GLuint A = 350;
	GLuint C = -1* A;
	spotLight_->upload(camera.getViewMat());
	//Sphere::render(camera);

	auxMat_ = modelMat_;
	spotLight_->setPos( glm::dvec3(A *cos(ang), B *sin(ang) *sin(ang), C *sin(ang)* cos(ang)));
	modelMat_ = glm::translate(getModelMat(), glm::dvec3(A *cos(ang), B *sin(ang) *sin(ang), C *sin(ang)* cos(ang)));

	//small
	material_->upload();
	gluQuadricDrawStyle(qObjSmall, GLU_LINE);
	gluQuadricTexture(qObjSmall, GLU_TRUE);
	gluQuadricNormals(qObjSmall, GLU_SMOOTH);
	gluQuadricOrientation(qObjSmall,GLU_OUTSIDE);

	texture_.bind(GL_MODULATE);
	uploadMvM(camera.getViewMat());
	gluSphere(qObjSmall, radius_, 36, 36);
	texture_.unbind();


/*	modelMat_ = auxMat_ + glm::translate(glm::dmat4(1), glm::dvec3(radius_, radius_, radius_));
	modelMat_ = glm::translate(getModelMat(), glm::dvec3(A *cos(ang), B *sin(ang) *sin(ang), C *sin(ang)* cos(ang)));
	//big
	material_->upload();
	gluQuadricDrawStyle(qObj, GLU_FILL);
	gluQuadricTexture(qObj, GLU_TRUE);
	gluQuadricNormals(qObj, GLU_SMOOTH);
	gluQuadricOrientation(qObj,GLU_OUTSIDE);

	texture_.bind(GL_MODULATE);	
	uploadMvM(camera.getViewMat());
	gluSphere(qObj, radius_*2, 36, 36);
	texture_.unbind();*/

	glDisable(GL_CULL_FACE);

}

void LightSphere::update()
{
	ang += 5;
	if (ang >= 360) ang = 0;
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

