#include "Scene.h"

#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

void Scene::init() {                 // OpenGL basic setting
  glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
  glEnable(GL_DEPTH_TEST);           // enable Depth test
  glEnable(GL_TEXTURE_2D);

  // lights
  // textures
  // meshes

  // Graphics objects (entities) of the scene

  cleangameObjects();
  grObjects.push_back(new RectangleTex(200, 200, 4, 4));
  grObjects.back()->setModelMat(
      rotate(grObjects.back()->getModelMat(), radians(90.), dvec3(1, 0, 0)));
  grObjects.back()->setModelMat(
      translate(grObjects.back()->getModelMat(), dvec3(-40, -45, -30)));
  grObjects.push_back(new Estrella3DTex(15., 4., 15.));
  grObjects.push_back(new CuboTex(30));
  grObjects.back()->setModelMat(
      translate(grObjects.back()->getModelMat(), dvec3(15, 30, 0)));
  grObjects.push_back(new Cristalera(200));
  grObjects.back()->setModelMat(
      translate(grObjects.back()->getModelMat(), dvec3(-40, 30, -45)));
  grObjects.push_back(new Foto(40, 40, 1, 1));
  // grObjects.back()->setModelMat(rotate(grObjects.back()->getModelMat(),
  // radians(90.), dvec3(1, 0, 0)));
  grObjects.back()->setModelMat(
      translate(grObjects.back()->getModelMat(), dvec3(60, 45, 20)));
  // grObjects.push_back(new Planta(80, 80, 1, 1));
}
void Scene::init2() {
  cleangameObjects();
  glm::dvec2 vector2d = dvec2(0.0, 0.0);
  grObjects.push_back(new Poliespiral(vector2d, 0, 45, 1, 1, 50));
  grObjects.push_back(new Dragon(3000));
  grObjects.push_back(new TrianguloAnimado(10));
  grObjects.push_back(new Rectangulo(200, 250, 0));
  grObjects.back()->setModelMat(
      rotate(grObjects.back()->getModelMat(), radians(130.), dvec3(1, 1, 0)));
}
void Scene::initExam() {
  glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
  glEnable(GL_DEPTH_TEST);           // enable Depth test
  glEnable(GL_TEXTURE_2D);

  grObjects.push_back(new EjesRGB(50));
  grObjects.push_back(new Piramide(20, 20));
  // grObjects.push_back(new Rectangulo(100, 100, -20)); // rect sin textura
  grObjects.push_back(new RectangleTex(150, 150, 10, 10));
  grObjects.back()->setModelMat(
      rotate(grObjects.back()->getModelMat(), radians(90.), dvec3(1, 0, 0)));
  grObjects.back()->setModelMat(
      translate(grObjects.back()->getModelMat(), dvec3(-80, -80, 20)));
}
void Scene::cleangameObjects() {
  // eliminar el objecto y hacer que apunte a null
  for (Entity* el : grObjects) {
    delete el;
    el = nullptr;
  }
  // elimina aquellos objetos con puntero null
  if (grObjects.size() != 0) {
    int size = grObjects.size();
    for (int i = 0; i < size; i++) {
      grObjects.pop_back();
    }
  }
}
//-------------------------------------------------------------------------

Scene::~Scene() {  // free memory and resources

  for (Entity* el : grObjects) {
    delete el;
    el = nullptr;
  }
}
//-------------------------------------------------------------------------

void Scene::render(Camera const& cam) {
  for (Entity* el : grObjects) {
    el->render(cam);
  }
}
void Scene::update() {
  for (Entity* el : grObjects) {
    el->update();
  }
}
//-------------------------------------------------------------------------
