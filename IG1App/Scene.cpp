#include "Scene.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

void Scene::init()
{ // OpenGL basic setting
  glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
  glEnable(GL_DEPTH_TEST);  // enable Depth test 
  glEnable(GL_TEXTURE_2D);
     
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
  grObjects.push_back(new Caja(50.));
  grObjects.push_back(new RectangleTex(100, 100, 1, 1));*/
  grObjects.push_back(new Estrella3DTex(35., 4., 35.));
  grObjects.push_back(new CuboTex(40));


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

