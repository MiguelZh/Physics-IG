#include "Rectangulo.h"



Rectangulo::Rectangulo(const GLdouble width, const GLdouble height,
	const int ejeZ) {
	mesh_ = Mesh::generaRectanguloRGB(width, height, ejeZ);
}

Rectangulo::~Rectangulo() {
	delete mesh_;
	mesh_ = nullptr;
}

void Rectangulo::render(Camera const &cam) {
	if (mesh_ != nullptr) {
		glLineWidth(2);
		uploadMvM(cam.getViewMat());
		mesh_->render();
	}
}

void Rectangulo::update() {}
