#include "Entity.h"
#include <queue>
#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

void Entity::uploadMvM(dmat4 const& modelViewMat) const
{ 
	dmat4 aMat = modelViewMat * modelMat;
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(aMat));
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

EjesRGB::EjesRGB(GLdouble l): Entity() 
{
  mesh = Mesh::createRGBAxes(l);
}
//-------------------------------------------------------------------------

EjesRGB::~EjesRGB() 
{ 
	delete mesh; mesh = nullptr; 
};
//-------------------------------------------------------------------------

void EjesRGB::render(Camera const& cam)
{
	if (mesh != nullptr) {
		uploadMvM(cam.getViewMat()); 
		glLineWidth(2);
		mesh->render();
		glLineWidth(1);
	}
}
void EjesRGB::update()
{
}
//-------------------------------------------------------------------------
Poliespiral::Poliespiral(dvec2 verIni, GLdouble angIni, GLdouble
	incrAng, GLdouble ladoIni, GLdouble incrLado, GLuint numVert) : Entity() {
	mesh = Mesh::generaPoliespiral(verIni, angIni, incrAng, ladoIni, incrLado, numVert);
}
Poliespiral::~Poliespiral(){
	delete mesh; mesh = nullptr;
}
void Poliespiral::render(Camera const& cam) {
	if (mesh != nullptr) {
		glColor3d(0, 0, 1);
		uploadMvM(cam.getViewMat());
		glLineWidth(2);
		mesh->render();
	
	}
}

void Poliespiral::update()
{
}

Dragon::Dragon(GLuint numVert) : Entity() {
	mesh = Mesh::generaDragon(numVert);
}

Dragon::~Dragon()
{
	delete mesh; mesh = nullptr;
}

void Dragon::render(Camera const & cam)
{
	if (mesh != nullptr) {
		glColor3d(0.5, 0.0, 0.5);
		glPointSize(2);
		uploadMvM(cam.getViewMat());
		mesh->render();
	}
}

void Dragon::update()
{
}

Triangle::Triangle(GLdouble numVert) : Entity()
{
	mesh = Mesh::generaTrianguloRGB(numVert);
}

Triangle::~Triangle()
{
	delete mesh; mesh = nullptr;
}

void Triangle::render(Camera const & cam)
{
	if (mesh != nullptr) {
		glLineWidth(2);
		uploadMvM(cam.getViewMat());
		mesh->render();
	}
}

void Triangle::update()
{

}

Rectangulo::Rectangulo(GLdouble w, GLdouble h,int ejeZ)
{
		mesh = Mesh::generaRectanguloRGB(w, h,ejeZ);
}

Rectangulo::~Rectangulo()
{
	delete mesh; mesh = nullptr;
}
void Rectangulo::render(Camera const & cam)
{
	if (mesh != nullptr) {
		glLineWidth(2);
		uploadMvM(cam.getViewMat());
		mesh->render();
	}
}

void Rectangulo::update()
{
}

TrianguloAnimado::TrianguloAnimado(GLdouble numVert) : Triangle(numVert)
{

}

TrianguloAnimado::~TrianguloAnimado()
{
	delete mesh; mesh = nullptr;
}

void TrianguloAnimado::update()
{/*
	double anguloExt = 10;
	double anguloInt = -10.;
	double aumentoInt = 2, aumentoExt = 2;
	modelMat = translate(dmat4(1), dvec3(-5 * cos(radians(anguloExt)), -5 *sin(radians(anguloExt)), 0));
	modelMat += rotate(modelMat, radians(anguloInt), dvec3(0, 0, 1));
	anguloExt += aumentoExt;
	anguloInt += aumentoInt;
	*/
	dmat4 aux;
	setModelMat(dmat4(1));
	aux = rotate(getModelMat(), angulo += radians(10.), dvec3(0, 0, 1.0));
	setModelMat(dmat4(1));
	aux = translate(aux, dvec3(30*cos(angulo), 30*sin(angulo), 0));
	aux = rotate(aux, angulo2 -= radians(25.5), dvec3(0, 0, 1));
	setModelMat(aux);
}

Estrella3D::Estrella3D(GLdouble re, GLdouble np, GLdouble h)
{
	mesh = Mesh::generaEstrella3D(re, np, h);
	dmat4 trans = translate(modelMat, dvec3(30, 100, 20));
	setModelMat(trans);
}

Estrella3D::~Estrella3D()
{
	delete mesh; mesh = nullptr;
}

void Estrella3D::render(Camera const & cam)
{
	if (mesh != nullptr) {
		//glColor3d(1, 0, 0);
		glPolygonMode(GL_POINT, GL_LINE);
		glLineWidth(2);
		uploadMvM(cam.getViewMat());
		mesh->render();
		modelMat= rotate(modelMat, radians(180.0), dvec3(0, 1, 0));
		uploadMvM(cam.getViewMat());
		mesh->render();
		modelMat = rotate(modelMat, radians(-180.0), dvec3(0, 1, 0));
	}
}

void Estrella3D::update()
{
	setModelMat(dmat4(1));
	dmat4 rotate1 = translate(getModelMat(), dvec3(30, 100, 20));
	rotate1 = rotate(rotate1, radians(angulo+=5.), dvec3(0, 1,0));
	rotate1 = rotate(rotate1, radians(angulo +=5.), dvec3(0, 0, 1));
	setModelMat(rotate1);
}

Caja::Caja(GLdouble l)
{
	mesh = Mesh::generaContCubo(l);
	///modelMat = rotate(getModelMat(), -270., dvec3(0, 1,1));
}

Caja::~Caja()
{
	delete mesh; mesh = nullptr;
}

void Caja::render(Camera const & cam)
{
	if (mesh != nullptr) {
		//glColor3d(0, 1, 0);
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		glLineWidth(2);
		uploadMvM(cam.getViewMat());
		mesh->render();
	}
}

void Caja::update()
{

}

RectangleTex::RectangleTex(GLdouble w, GLdouble h, GLuint rw, GLuint rh)
{
	mesh = Mesh::generaRectanguloTexCor(w,  h, rw,  rh); // con coord. de textura
	texture.load("..\\Bmps\\Zelda.bmp"); // cargamos la imagen
}

RectangleTex::~RectangleTex()
{
	delete mesh; mesh = nullptr;
}

void RectangleTex::render(Camera const & cam)
{
	if (mesh != nullptr) {
		texture.bind();
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth(2);
		uploadMvM(cam.getViewMat());
		mesh->render();
		texture.unbind();
	}
}

void RectangleTex::update()
{
}

Estrella3DTex::Estrella3DTex(GLdouble r, GLdouble nL, GLdouble h)
{
	mesh = Mesh::generaEstrellaTexCor(r, nL, h);
	texture.load("..\\Bmps\\baldosaP.bmp"); // cargamos la imagen
}

Estrella3DTex::~Estrella3DTex()
{
	delete mesh; mesh = nullptr;
}

void Estrella3DTex::render(Camera const & cam)
{
	if (mesh != nullptr) {
		texture.bind();
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glLineWidth(2);
		uploadMvM(cam.getViewMat());
		mesh->render();
		modelMat = rotate(modelMat, radians(180.0), dvec3(0, 1, 0));
		uploadMvM(cam.getViewMat());
		mesh->render();
		modelMat = rotate(modelMat, radians(-180.0), dvec3(0, 1, 0));
		texture.unbind();
	}
}

void Estrella3DTex::update()
{
}
