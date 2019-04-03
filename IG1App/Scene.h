#pragma once
#include <vector>
#include "Camera.h"
#include "Entity.h"

//-------------------------------------------------------------------------

class Scene final {
  void clearObjects();

 public:
  Scene();
  ~Scene();
  static void init();

  void scene2D();
  void scene3D();
  void sceneExam();
  void sceneSphere();

  void render(Camera const& cam);
  void update();

 protected:
  std::vector<Entity*> grObjects_;  // Entities (graphics objects) of the scene
};
