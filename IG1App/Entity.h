//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Camera.h"
#include "Mesh.h"
#include"Texture.h"

//-------------------------------------------------------------------------

class Entity 
{
public:
	Entity() : modelMat(1.0) { }; 
	virtual ~Entity() { };

	virtual void render(Camera const& cam) = 0;
	virtual void update() = 0;

	// modeling matrix
	glm::dmat4 const& getModelMat() const { return modelMat; };
	GLint repetitions = 1;
	void setModelMat(glm::dmat4 const& aMat) { modelMat = aMat; }
  
protected:

	Mesh* mesh = nullptr;   // surface mesh
	glm::dmat4 modelMat;    // modeling matrix
	glm::dmat4 auxMat;
	double angulo = 0, angulo2 = 0;
	Texture texture, texture1; // w, h, id 
	// transfers modelViewMat to the GPU
	virtual void uploadMvM(glm::dmat4 const& modelViewMat) const;
};

//-------------------------------------------------------------------------

class EjesRGB : public Entity 
{
public:
	EjesRGB(GLdouble l);
	~EjesRGB();
	virtual void render(Camera const& cam); 
	void update();
};

//-------------------------------------------------------------------------

class Poliespiral : public Entity {
public:
	Poliespiral(glm::dvec2 verIni, GLdouble angIni, GLdouble
		incrAng, GLdouble ladoIni, GLdouble incrLado, GLuint numVert);
	~Poliespiral();
	virtual void render(Camera const& cam);
	void update();
};
//-------------------------------------------------------------------------
class Dragon : public Entity {
public:
	Dragon(GLuint numVert);
	~Dragon();
	virtual void render(Camera const& cam);
	void update();
};
//-------------------------------------------------------------------------
class Triangle : public Entity {
public:
	Triangle(GLdouble numVert);
	~Triangle();
	virtual void render(Camera const& cam);
	void update();
};
class TrianguloAnimado : public Triangle {
private:
	glm::dmat4 aux = modelMat;
public:
	TrianguloAnimado(GLdouble numVert);
	~TrianguloAnimado();
	void update();
};
//-------------------------------------------------------------------------
class Rectangulo : public Entity {
public:
	Rectangulo(GLdouble w, GLdouble h,int ejeZ);
	~Rectangulo();
	virtual void render(Camera const& cam);
	void update();
};
class Estrella3D : public Entity {
public:
	Estrella3D(GLdouble re, GLdouble np, GLdouble h);
	~Estrella3D();
	virtual void render(Camera const& cam);
	void update();
};
class Caja : public Entity {
public:
	Caja(GLdouble l);
	~Caja();
	virtual void render(Camera const& cam);
	void update();
};
class RectangleTex : public Entity {
public:
	RectangleTex(GLdouble w, GLdouble h, GLuint rw, GLuint rh);
	~RectangleTex();
	virtual void render(Camera const& cam);
	void update();
};
class Estrella3DTex : public Entity {
public:
	Estrella3DTex(GLdouble r, GLdouble nL, GLdouble h);
	~Estrella3DTex();
	virtual void render(Camera const& cam);
	void update();
};
class CuboTex : public Entity {
public:
	CuboTex(GLdouble l);
	~CuboTex();
	virtual void render(Camera const& cam);
	void update();
};
class Cristalera : public Entity {
public:
	Cristalera(GLdouble l);
	~Cristalera();
	virtual void render(Camera const& cam);
	void update();
};
class Foto : public Entity {
public:
	Foto(GLdouble w, GLdouble h, GLuint rw, GLuint rh);
	~Foto();
	virtual void render(Camera const& cam);
	void update();
};
class Planta : public Entity {
public:
	Planta(GLdouble w, GLdouble h, GLuint rw, GLuint rh);
	~Planta();
	virtual void render(Camera const& cam);
	void update();
};
class piramide : public Entity {
private:
	double lado;
public:
	piramide(GLdouble l, GLdouble h);
	~piramide();
	virtual void render(Camera const& cam);
	void update();
};
#endif //_H_Entities_H_