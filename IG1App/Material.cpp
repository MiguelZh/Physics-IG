#include "Material.h"

Material::Material() = default;

Material::~Material() = default;

void Material::upload() {
  glShadeModel(sh);
  glMaterialfv(face, GL_AMBIENT, glm::value_ptr(ambient));
}
void Material::setBlackPlastic() {
  ambient = {0, 0, 0, 0};
  diffuse = {0.01, 0.01, 0.01, 0};
  specular = {0.5, 0.5, 0.5, 0};
  expF = 32;
}

void Material::setBrass() {
  ambient = {0.329412, 0.223529, 0.027451, 0};
  diffuse = {0.780392, 0.568627, 0.113725, 0};
  specular = {0.992157, 0.941176, 0.807843, 0};
  expF = 27.8974;
}

void Material::setBronze() {
  ambient = {0.2125, 0.1275, 0.054, 0};
  diffuse = {0.714, 0.4284, 0.18144, 0};
  specular = {0.393548, 0.271906, 0.166721, 0};
  expF = 25.6;
}

void Material::setChrome() {
  ambient = {0.25, 0.25, 0.25, 0};
  diffuse = {0.4, 0.4, 0.4, 0};
  specular = {0.774597, 0.774597, 0.774597, 0};
  expF = 76.8;
}

void Material::setCopper() {
  ambient = {0.19125, 0.0735, 0.0225, 0};
  diffuse = {0.7038, 0.27048, 0.0828, 0};
  specular = {0.256777, 0.137622, 0.086014, 0};
  expF = 12.8;
}

void Material::setGold() {
  ambient = {0.24725, 0.1995, 0.0745, 0};
  diffuse = {0.75164, 0.60648, 0.22648, 0};
  specular = {0.628281, 0.555802, 0.086014, 0};
  expF = 51.2;
}

void Material::setPewter() {
  ambient = {0.10588, 0.058824, 0.113725, 0};
  diffuse = {0.427451, 0.470588, 0.541176, 0};
  specular = {0.3333, 0.3333, 0.521569, 0};
  expF = 9.84615;
}

void Material::setSilver() {
  ambient = {0.19225, 0.19225, 0.19225, 0};
  diffuse = {0.50754, 0.50754, 0.50754, 0};
  specular = {0.508273, 0.508273, 0.508273, 0};
  expF = 51.2;
}

void Material::setPolishedSilver() {
  ambient = {0.23125, 0.23125, 0.23125, 0};
  diffuse = {0.2775, 0.2775, 0.2775, 0};
  specular = {0.773911, 0.773911, 0.773911, 0};
  expF = 89.6;
}
