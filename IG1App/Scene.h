#pragma once
#include <vector>
#include "Camera.h"
#include "Entity.h"

//-------------------------------------------------------------------------

class Scene {
 public:
  Scene(){};
  ~Scene();
  void init();
  void init2();
  void initExam();
  void cleangameObjects();
  void render(Camera const& cam);
  void update();

 protected:
  std::vector<Entity*> grObjects;  // Entities (graphics objects) of the scene
};
