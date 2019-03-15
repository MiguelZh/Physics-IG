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
	texture.load("..\\Bmps\\baldosaC.bmp"); // cargamos la imagen
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
	setModelMat(dmat4(1));
	dmat4 rotate1 = translate(getModelMat(), dvec3(30, 100, 20));
	rotate1 = rotate(rotate1, radians(angulo += 5.), dvec3(0, 1, 0));
	rotate1 = rotate(rotate1, radians(angulo += 5.), dvec3(0, 0, 1));
	setModelMat(rotate1);
}

CuboTex::CuboTex(GLdouble l)
{
	mesh = Mesh::generaCajaTexCor(l);
	texture.load("..\\Bmps\\baldosaF.bmp"); // cargamos la imagen
	texture1.load("..\\Bmps\\container.bmp"); // cargamos segunda imagen
}

CuboTex::~CuboTex()
{
	delete mesh; mesh = nullptr;
}

void CuboTex::render(Camera const & cam)
{
	if (mesh != nullptr) {
		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);
		texture.bind();
		uploadMvM(cam.getViewMat());
		glLineWidth(2);
		mesh->render();
		texture.unbind();

		glCullFace(GL_BACK);
		texture1.bind();
		mesh->render();
		texture1.unbind();
		glDisable(GL_CULL_FACE);
	}
}

void CuboTex::update()
{
}

Cristalera::Cristalera(GLdouble l)
{
	mesh = Mesh::generaCajaTexCor(l);
	texture.load("..\\Bmps\\cristalTri.bmp",150); // cargamos la imagen
}

Cristalera::~Cristalera()
{
	delete mesh; mesh = nullptr;
}

void Cristalera::render(Camera const & cam)
{
	if (mesh != nullptr) {

		uploadMvM(cam.getViewMat());
		glPolygonMode(GL_NONE, GL_LINE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDepthMask(GL_FALSE);
		glLineWidth(1);
		texture.bind();
		mesh->render();
		texture.unbind();
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
	}
}

void Cristalera::update()
{
}

Foto::Foto(GLdouble w, GLdouble h, GLuint rw, GLuint rh)
{
	mesh = Mesh::generaRectanguloTexCor(w, h, rw, rh);
}

Foto::~Foto()
{
	delete mesh; mesh = nullptr;
}

void Foto::render(Camera const & cam)
{
	if (mesh != nullptr) {
		texture.loadColorBuffer();

		uploadMvM(cam.getViewMat());
		glLineWidth(1);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		texture.bind();
		mesh->render();
		texture.unbind();
	}
}

void Foto::update()
{
}

Planta::Planta(GLdouble w, GLdouble h, GLuint rw, GLuint rh)
{
	mesh = Mesh::generaRectanguloTexCor(w, h, rw, rh);
	texture.load("..\\Bmps\\grass.bmp");
}

Planta::~Planta()
{
	delete mesh; mesh = nullptr;
}

void Planta::render(Camera const & cam)
{
	int angulo = 20;
	if (mesh != nullptr) {
		dmat4 originalMat = getModelMat();
		glDepthMask(GL_FALSE);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		dmat4 auxMat = originalMat;
		auxMat = rotate(auxMat, radians((180.0 / 20)), dvec3(0.0, 1.0, 0.0));
		setModelMat(auxMat);
		uploadMvM(cam.getViewMat());
		texture.bind();
		mesh->render();
		texture.unbind();
		setModelMat(originalMat);
		glLineWidth(1);
		glDepthMask(GL_TRUE);
	}
}

void Planta::update()
{
}

piramide::piramide(GLdouble l, GLdouble h)
{
	mesh = Mesh::bipiramideExam(l, h);
	lado = l;
	altura = h * 2;
	alturaActual = 0;
	subiendo = true;
	auxMat = translate(modelMat,dvec3(-l/2,0,-l/2));
	texture.load("..\\Bmps\\sierpinski.bmp",100);
}

piramide::~piramide()
{
	delete mesh; mesh = nullptr;
}

void piramide::render(Camera const & cam)
{
	modelMat = auxMat; //para que no se desplace 
	dmat4 aux = modelMat;
	aux = translate(modelMat, dvec3(lado, 0, 0));
	if (mesh != nullptr) {
		uploadMvM(cam.getViewMat());
		glLineWidth(2);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDepthMask(GL_FALSE);
		texture.bind();
		mesh->render();
		texture.unbind();
		modelMat = rotate(aux, radians(180.0), dvec3(0, 0, 1));
		uploadMvM(cam.getViewMat());
		mesh->render();
		aux = translate(modelMat, dvec3(-lado, 0, 0));
		modelMat = rotate(aux, radians(-180.0), dvec3(0, 0, 1));
		glDisable(GL_LINE);
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
	}
}

void piramide::update()
{
	angulo += 2;
	auxMat = rotate(auxMat, radians(5.), dvec3(1, 1, 0));
	if (alturaActual > altura || (alturaActual-0.5 < -1)) 
	{
		subiendo = !subiendo;
	}
	if (subiendo)
	{
		alturaActual += 0.5;
		auxMat = translate(auxMat, dvec3(0, 0.5, 0));
	}
	else if (!subiendo)
	{
		alturaActual -= 0.5;
		auxMat = translate(auxMat, dvec3(0, -0.5, 0));
	}

}
