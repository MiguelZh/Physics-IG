#include "Scene.h"

#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

using namespace glm;

Scene::Scene() = default;

Scene::~Scene() { clearObjects(); }

void Scene::init() {
  glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
  glEnable(GL_DEPTH_TEST);           // enable Depth test
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_CULL_FACE);
}

void Scene::scene2D() {
  clearObjects();

  grObjects_.push_back(new Estrella3DTex(15., 4., 15.));
  grObjects_.push_back(new CuboTex(30));
  grObjects_.back()->setModelMat(
      translate(grObjects_.back()->getModelMat(), dvec3(15, 30, 0)));
  grObjects_.push_back(new Rectangulo(10, 10, -20));  // rect without texture
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
  glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
  glEnable(GL_DEPTH_TEST);           // enable Depth test
  glEnable(GL_TEXTURE_2D);

  grObjects_.push_back(new EjesRGB(50));
  grObjects_.push_back(new Piramide(20, 20));
  // grObjects.push_back(new Rectangulo(100, 100, -20)); // rect without texture
  grObjects_.push_back(new RectangleTex(150, 150, 10, 10));
  grObjects_.back()->setModelMat(
      rotate(grObjects_.back()->getModelMat(), radians(90.), dvec3(1, 0, 0)));
  grObjects_.back()->setModelMat(
      translate(grObjects_.back()->getModelMat(), dvec3(-80, -80, 20)));
}

void Scene::sceneSphere() {
  glEnable(GL_DEPTH_TEST);  // enable Depth test
  glEnable(GL_TEXTURE_2D);
}

void Scene::render(Camera const &cam) {
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
  for (auto el : grObjects_) delete el;
  grObjects_.clear();
}
