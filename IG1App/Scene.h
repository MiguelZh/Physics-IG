#pragma once
#include <vector>
#include "Camera.h"
#include "Entity.h"
#include "EntityMaterial.h"

class DirLight;
class SpotLight;
class PosLight;
class LightSphere;

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

  void toggleCamLight() const;
  void toggleSphereLight() const;
  void toggleDirLight() const;

  void render(Camera const& cam);
  void update();

 protected:
  std::vector<Entity*> grObjects_;  // Entities (graphics objects) of the scene
  std::vector<Material*> materials_;
  enum NumMat
  {
	  Copper,
	  Gold,
	  Bronze,
	  End
  };
  DirLight* dirLight_;
  SpotLight* camLight_;
  LightSphere * lightSphere_;
};
