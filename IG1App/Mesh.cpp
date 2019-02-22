#include "Mesh.h"

using namespace glm;

//-------------------------------------------------------------------------

Mesh ::~Mesh(void) 
{
  delete[] vertices;  vertices = nullptr;
  delete[] colors;    colors = nullptr;
}
//-------------------------------------------------------------------------

void Mesh::render()
{
  if (vertices != nullptr) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, vertices);  // number of coordinates per vertex, type of each coordinate, stride, pointer 
    if (colors != nullptr) {
      glEnableClientState(GL_COLOR_ARRAY);
      glColorPointer(4, GL_DOUBLE, 0, colors);   // number of coordinates per color, type of each coordinate, stride, pointer 
    }
	
    glDrawArrays(primitive, 0, numVertices);   // primitive graphic, first index and number of elements to be rendered

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
  }
}
//-------------------------------------------------------------------------

Mesh * Mesh::createRGBAxes(GLdouble l)
{
  Mesh* m = new Mesh();
  m->primitive = GL_LINES;
  m->numVertices = 6;

  m->vertices = new dvec3[m->numVertices];
  // X axis vertices
  m->vertices[0] = dvec3(0.0, 0.0, 0.0);   
  m->vertices[1] = dvec3(l, 0.0, 0);
  // Y axis vertices
  m->vertices[2] = dvec3(0, 0.0, 0.0);
  m->vertices[3] = dvec3(0.0, l, 0.0); 
  // Z axis vertices
  m->vertices[4] = dvec3(0.0, 0.0, 0.0);
  m->vertices[5] = dvec3(0.0, 0.0, l);

  m->colors = new dvec4[m->numVertices];
  // X axis color: red  ( Alpha = 1 : fully opaque)
  m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
  m->colors[1] = dvec4(1.0, 0.0, 0.0, 1.0);
  // Y axis color: green
  m->colors[2] = dvec4(0.0, 1.0, 0.0, 1.0);
  m->colors[3] = dvec4(0.0, 1.0, 0.0, 1.0);
  // Z axis color: blue
  m->colors[4] = dvec4(0.0, 0.0, 1.0, 1.0);
  m->colors[5] = dvec4(0.0, 0.0, 1.0, 1.0);
 
  return m; 
}
//-------------------------------------------------------------------------
Mesh * Mesh::generaPoliespiral(dvec2 verIni, GLdouble angIni, GLdouble
	incrAng, GLdouble ladoIni, GLdouble incrLado, GLuint numVert){
	Mesh *  poliespiral = new Mesh();
	poliespiral->primitive = GL_LINE_STRIP;
	poliespiral->numVertices = numVert;
	poliespiral->vertices = new dvec3[poliespiral->numVertices];
	double x, y; double longitud = ladoIni, angulo = angIni;
	x = verIni.x;
	y = verIni.y;
	for (int i =0 ; i < poliespiral->numVertices ;i++) {
		poliespiral->vertices[i] = dvec3(x, y, 0.0);
		x += longitud * cos(radians(angulo)); // cos(radians(90))
		y += longitud * sin(radians(angulo));
		longitud += incrLado;
		angulo += incrAng;
	}
	return poliespiral;
}
//-------------------------------------------------------------------------
Mesh * Mesh::generaDragon(GLuint numVert)
{
	Mesh * dragon = new Mesh();
	dragon->primitive = GL_POINTS;
	dragon->numVertices = numVert;
	dragon->vertices = new dvec3[dragon->numVertices];
	double x = 0, y = 0; double auxX = x, auxY = y;
	double PR1 = 0.787473; double PR2 = 0.212527;
	for (int i = 0; i < dragon->numVertices; i++) {
		dragon->vertices[i] = dvec3(x, y, 0.0);
		double azar = rand() / double(RAND_MAX);
		auxX = x; auxY = y;
		if (azar < PR1) {
			x = 0.824074 * auxX + 0.281482 * auxY - 0.882290;
			y = -0.212346 * auxX + 0.864198 * auxY - 0.110607;
		
		} // T1
		else {
			x = 0.088272 * auxX + 0.520988 * auxY + 0.785360;
			y = -0.463889 *auxX - 0.377778 * auxY + 8.095795;
		} // T2
		
	}
	return dragon;
}

Mesh * Mesh::generaTriangulo(GLdouble r)
{
	Mesh* triangulo = new Mesh();
	triangulo->primitive = GL_TRIANGLES;
	triangulo->numVertices = 3;
	triangulo->vertices = new dvec3[triangulo->numVertices];
	double incrAng = 360 / 4;
	for (int i = 0; i < triangulo->numVertices; i++) {
		double x = 0 + r * cos(90 + incrAng * i);
		double y = 0 + r * sin(90 + incrAng * i);
		triangulo->vertices[i] = dvec3(x, y, 0.0);
	}
	return triangulo;
}

Mesh * Mesh::generaTrianguloRGB(GLdouble r)
{
	Mesh * m = generaTriangulo(r);
	 // crear el array de colores
	m->colors = new dvec4[m->numVertices];
	m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
	m->colors[1] = dvec4(0.0, 1.0, 0.0, 1.0);
	m->colors[2] = dvec4(0.0, 0.0, 1.0, 1.0);
	return m;
}

Mesh * Mesh::generaRectangulo(GLdouble w, GLdouble h,double ejeZ)
{
	Mesh * rectangulo = new Mesh();
	rectangulo->primitive = GL_TRIANGLE_STRIP;
	rectangulo->numVertices = 4;
	rectangulo->vertices = new dvec3[rectangulo->numVertices];
	rectangulo->vertices[0] = dvec3(ejeZ, ejeZ, ejeZ);
	rectangulo->vertices[1] = dvec3(w, ejeZ, ejeZ);
	rectangulo->vertices[2] = dvec3(ejeZ, ejeZ, h);
	rectangulo->vertices[3] = dvec3(w, ejeZ, h);
	return rectangulo;
}

Mesh * Mesh::generaRectanguloRGB(GLdouble w, GLdouble h, double ejeZ)
{
	Mesh * rectangulo = generaRectangulo(w, h,ejeZ);
	rectangulo->colors = new dvec4[rectangulo->numVertices];
	rectangulo->colors[0] = dvec4(0.25, 0.0, ejeZ, 1.0);
	rectangulo->colors[1] = dvec4(0.0, 0.5, ejeZ, 1.0);
	rectangulo->colors[2] = dvec4(0.0, 0.0, 0.75, 1.0);
	rectangulo->colors[3] = dvec4(1.0, 0.0, ejeZ, 1.0);
	return rectangulo;
}

Mesh * Mesh::generaEstrella3D(GLdouble re, GLdouble np, GLdouble h)
{
	Mesh* estrella3D = new Mesh();
	estrella3D->primitive = GL_TRIANGLE_FAN;
	estrella3D->numVertices = 2 * np + 2;
	estrella3D->vertices = new dvec3[estrella3D->numVertices];
	estrella3D->colors = new dvec4[estrella3D->numVertices];
	dvec3 vo = { 0,0,0 };
	double ri = re / 2;
	double x = 0, y = 0;
	double angulo = 0;
	double incrAng = 360 / np /2;
	for (int i = 0; i < estrella3D->numVertices; i++) {
		if (i == 0) {
			estrella3D->vertices[i] = vo;
		}
		else if(i%2 ==0){
			x = re * cos(radians(angulo+incrAng*i));
			y = re * sin(radians(angulo + incrAng * i));
			estrella3D->vertices[i] = dvec3(x, y, h);
			estrella3D->colors[i] = dvec4(0.5, 0., 0., 1.);
		}
		else {
			x = ri * cos(radians(angulo + incrAng * i));
			y = ri * sin(radians(angulo + incrAng * i));
			estrella3D->vertices[i] = dvec3(x, y, 2*h/3);
			estrella3D->colors[i] = dvec4(0., 0., 0.5, 1.);
		}
	}

	return estrella3D;
}

Mesh * Mesh::generaContCubo(GLdouble l)
{
	Mesh * cubo = new Mesh();
	cubo->primitive = GL_TRIANGLE_STRIP;
	cubo->numVertices = 10;
	cubo->vertices = new dvec3[cubo->numVertices];
	cubo->colors = new dvec4[cubo->numVertices];
	double puntocentro = 0;
	cubo->vertices[0] = dvec3(puntocentro,l,l);
	cubo->colors[0] = dvec4(0, 0.7, 0, 0);
	cubo->vertices[1] = dvec3(puntocentro, puntocentro,l);
	cubo->colors[1] = dvec4(0, 0.7, 0, 0);
	cubo->vertices[2] = dvec3(l,l,l);
	cubo->colors[2] = dvec4(0, 0.7, 0, 0);
	cubo->vertices[3] = dvec3(l, puntocentro,l);
	cubo->colors[3] = dvec4(0, 0.7, 0, 0);
	cubo->vertices[4] = dvec3(l,l, puntocentro);
	cubo->colors[4] = dvec4(0, 0., 0.7, 0);
	cubo->vertices[5] = dvec3(l, puntocentro, puntocentro);
	cubo->colors[5] = dvec4(0, 0., 0.7, 0);
	cubo->vertices[6] = dvec3(puntocentro,l, puntocentro);
	cubo->colors[6] = dvec4(0, 0., 0.7, 0);
	cubo->vertices[7] = dvec3(puntocentro, puntocentro, puntocentro);
	cubo->colors[7] = dvec4(0, 0., 0.7, 0);
	cubo->vertices[8] = dvec3(puntocentro,l,l);
	cubo->colors[8] = dvec4(0.7, 0., 0.7, 0);
	cubo->vertices[9] = dvec3(puntocentro, puntocentro,l);
	cubo->colors[9] = dvec4(0.7, 0., 0.7, 0);
	/*cubo->vertices[10] = dvec3(l,puntocentro,l);
	cubo->colors[10] = dvec4(0.7, 0., 0.5, 0);
	cubo->vertices[11] = dvec3(puntocentro, puntocentro, puntocentro);
	cubo->colors[11] = dvec4(0.5, 0., 0.5, 0);
	cubo->vertices[12] = dvec3(l, puntocentro, puntocentro);
	cubo->colors[12] = dvec4(0.5, 0., 0.5, 0);*/
	return cubo;
}

