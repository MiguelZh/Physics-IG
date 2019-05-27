#include "Scene.h"
#include "DirLight.h"
#include "Material.h"
#include "PosLight.h"
#include "SpotLight.h"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "LightSphere.h"
#include "Sphere.h"
#include "Estrella3D.h"
#include "Estrella3DTex.h"
#include "RectangleTex.h"
#include "Rectangulo.h"
#include "CuboTex.h"
#include "TrianguloAnimado.h"
#include "Cristalera.h"
#include "Foto.h"
#include "Poliespiral.h"
#include "Dragon.h"
#include "EjesRGB.h"
#include "Piramide.h"
#include "CurvedTerrain.h"
using namespace glm;

Scene::Scene() = default;

Scene::~Scene() { clearObjects(); }

void Scene::init() {
  glClearColor(1.0, 1.0, 1.0, 1.0); // background color (alpha=1 -> opaque)
  glEnable(GL_DEPTH_TEST);          // enable Depth test
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_CULL_FACE);
}

void Scene::scene2D() {
  clearObjects();

  grObjects_.push_back(new Estrella3DTex(15., 4., 15.));
  grObjects_.push_back(new CuboTex(30));
  grObjects_.back()->setModelMat(
      translate(grObjects_.back()->getModelMat(), dvec3(15, 30, 0)));
  grObjects_.push_back(new Rectangulo(10, 10, -20)); // rect without texture
  grObjects_.back()->setModelMat(
      translate(grObjects_.back()->getModelMat(), dvec3(35, 55, 20)));
  grObjects_.push_back(new RectangleTex(200, 200, 4, 4));
  grObjects_.back()->setModelMat(
      rotate(grObjects_.back()->getModelMat(), radians(90.), dvec3(1, 0, 0)));
  grObjects_.back()->setModelMat(
      translate(grObjects_.back()->getModelMat(), dvec3(-40, -45, -30)));
  grObjects_.push_back(new Cristalera(200));
  grObjects_.back()->setModelMat(
      translate(grObjects_.back()->getModelMat(), dvec3(-40, 30, -45)));
  grObjects_.push_back(new Foto(40, 40, 1, 1));
  grObjects_.back()->setModelMat(
      translate(grObjects_.back()->getModelMat(), dvec3(60, 45, 20)));
}

void Scene::scene3D() {
  clearObjects();
  const auto vector2D = dvec2(0.0, 0.0);
  grObjects_.push_back(new Poliespiral(vector2D, 0, 45, 1, 1, 50));
  grObjects_.push_back(new Dragon(3000));
  grObjects_.push_back(new TrianguloAnimado(10));
  grObjects_.push_back(new Rectangulo(200, 250, 0));
  grObjects_.back()->setModelMat(
      rotate(grObjects_.back()->getModelMat(), radians(130.), dvec3(1, 1, 0)));
}

void Scene::sceneExam() {
  clearObjects();

  glClearColor(1.0, 1.0, 1.0, 1.0); // background color (alpha=1 -> opaque)
  glEnable(GL_DEPTH_TEST);          // enable Depth test
  glEnable(GL_TEXTURE_2D);

  grObjects_.push_back(new EjesRGB(50));
  grObjects_.push_back(new Piramide(20, 20));
  grObjects_.push_back(new RectangleTex(150, 150, 10, 10));
  grObjects_.back()->setModelMat(
      rotate(grObjects_.back()->getModelMat(), radians(90.), dvec3(1, 0, 0)));
  grObjects_.back()->setModelMat(
      translate(grObjects_.back()->getModelMat(), dvec3(-80, -80, 20)));
}

void Scene::sceneSphere() {
  clearObjects();
  glClearColor(0.0f, 0.0f, 0.2f, 1.0f);
  glEnable(GL_DEPTH_TEST); // enable Depth test
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_LIGHTING);
  glEnable(GL_NORMALIZE); // lights

  for (int i = 0; i < End; i++) {
    auto x = new Material();
    switch (i) {
    case Copper:
      x->setCopper();
      break;
    case Gold:
      x->setGold();
      break;
    case Bronze:
      x->setBronze();
      break;
    default:
      break;
    }
    materials_.push_back(x);
  }
  dirLight_ = new DirLight();
  dirLight_->setDir({0, 0.25, -10});
  dirLight_->uploadLI();
  dirLight_->enable();

  camLight_ = new SpotLight();
  //To inicialize a "light" write the following two lines 
  camLight_->uploadLI();
  camLight_->enable();
  grObjects_.push_back(new EjesRGB(150));

  lightSphere_ = new LightSphere(30, "../Bmps/papelE.bmp", dvec3(0, 150, 0));
  lightSphere_->setMaterial(materials_[Gold]);
  grObjects_.push_back(lightSphere_);

  // materials are needed if you want to see the light
  auto earth = new Sphere(70, "../Bmps/earth.bmp");
  earth->setMaterial(materials_[Bronze]);
  grObjects_.push_back(earth);
  grObjects_.back()->setModelMat(
      translate(grObjects_.back()->getModelMat(), dvec3(0, 0, 0)));

  auto terrain = new CurvedTerrain(600, 15, "../Bmps/terreno.bmp");
  terrain->setMaterial(materials_[Gold]);
  grObjects_.push_back(terrain);
  grObjects_.back()->setModelMat(
      translate(grObjects_.back()->getModelMat(), dvec3(0, -50, 0)));
}

void Scene::toggleCamLight() const {
  if (camLight_->getEnabled()) {
    camLight_->disable();
  } else {
    camLight_->enable();
  }
  camLight_->setEnabled(!camLight_->getEnabled());
}

void Scene::toggleSphereLight() const {
  if (lightSphere_->spotLight_->getEnabled()) {
    lightSphere_->spotLight_->disable();
  } else {
    lightSphere_->spotLight_->enable();
  }
  lightSphere_->spotLight_->setEnabled(!lightSphere_->spotLight_->getEnabled());
}

void Scene::toggleDirLight() const {
  if (dirLight_->getEnabled()) {
    dirLight_->disable();
  } else {
    dirLight_->enable();
  }
  dirLight_->setEnabled(!dirLight_->getEnabled());
}

void Scene::render(Camera const &cam) {
  dirLight_->upload(cam.getViewMat());
  camLight_->setPos(cam.getPos());
  camLight_->setDir(cam.getDir());
  camLight_->upload(cam.getViewMat());

  for (auto el : grObjects_) {
    el->render(cam);
  }
}
void Scene::update() {
  for (auto el : grObjects_) {
    el->update();
  }
}

void Scene::clearObjects() {
  for (auto el : grObjects_)
    delete el;
  grObjects_.clear();
}
