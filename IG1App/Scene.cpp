#include "Scene.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

void Scene::init()
{ // OpenGL basic setting
  glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
  glEnable(GL_DEPTH_TEST);  // enable Depth test 
     
  // lights
  // textures  
  // meshes

  // Graphics objects (entities) of the scene
  /*grObjects.push_back(new EjesRGB(200.0)); 
  glm::dvec2 vector2d =dvec2(0.0, 0.0);
  grObjects.push_back(new Poliespiral(vector2d, 0, 45, 1, 1, 50));
  grObjects.push_back(new Dragon(3000));
  grObjects.push_back(new TrianguloAnimado(10));
  grObjects.push_back(new Rectangulo(200, 250,0));
  grObjects.push_back(new Rectangulo(50, 50,2));
  grObjects.push_back(new Estrella3D(35.,7., 35.));
  grObjects.push_back(new Caja(50.));*/


}
//-------------------------------------------------------------------------

Scene::~Scene()
{ // free memory and resources   
  
  for (Entity* el: grObjects)
  {
	  delete el;  el = nullptr;
  }
}
//-------------------------------------------------------------------------

void Scene::render(Camera const& cam)
{
	for (Entity* el: grObjects)
	{
		el->render(cam);
	}
}
void Scene::update()
{
	for (Entity* el : grObjects)
	{
		el->update();
	}
}
//-------------------------------------------------------------------------

