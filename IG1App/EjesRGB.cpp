#include "EjesRGB.h"


EjesRGB::EjesRGB(const GLdouble l) { mesh_ = Mesh::createRGBAxes(l); }

EjesRGB::~EjesRGB() {
	delete mesh_;
	mesh_ = nullptr;
};

void EjesRGB::render(Camera const& cam) {
	if (mesh_ != nullptr) {
		uploadMvM(cam.getViewMat());
		glLineWidth(2);
		mesh_->render();
		glLineWidth(1);
	}
}

void EjesRGB::update() {}
