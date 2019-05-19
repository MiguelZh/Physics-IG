#include "Material.h"

Material::Material() = default;

Material::~Material() = default;

void Material::upload() {
  glShadeModel(sh);
  glMaterialfv(face, GL_AMBIENT, glm::value_ptr(ambient));
}

void Material::setBlackPlastic() {
  ambient = {0.0f, 0.0f, 0.0f, 0.0f};
  diffuse = {0.01f, 0.01f, 0.01f, 0.0f};
  specular = {0.5f, 0.5f, 0.5f, 0.0f};
  expF = 32.0f;
}

void Material::setBrass() {
  ambient = {0.329412f, 0.223529f, 0.027451f, 0.0f};
  diffuse = {0.780392f, 0.568627f, 0.113725f, 0.0f};
  specular = {0.992157f, 0.941176f, 0.807843f, 0.0f};
  expF = 27.8974f;
}

void Material::setBronze() {
  ambient = {0.2125f, 0.1275f, 0.054f, 0.0f};
  diffuse = {0.714f, 0.4284f, 0.18144f, 0.0f};
  specular = {0.393548, 0.271906, 0.166721, 0.0f};
  expF = 25.6f;
}

void Material::setChrome() {
  ambient = {0.25f, 0.25f, 0.25f, 0.0f};
  diffuse = {0.4f, 0.4f, 0.4f, 0.0f};
  specular = {0.774597f, 0.774597f, 0.774597f, 0.0f};
  expF = 76.8f;
}

void Material::setCopper() {
  ambient = {0.19125f, 0.0735f, 0.0225f, 0.0f};
  diffuse = {0.7038f, 0.27048f, 0.0828f, 0.0f};
  specular = {0.256777f, 0.137622f, 0.086014, 0.0f};
  expF = 12.8f;
}

void Material::setGold() {
  ambient = {0.24725f, 0.1995f, 0.0745f, 0.0f};
  diffuse = {0.75164f, 0.60648f, 0.22648f, 0.0f};
  specular = {0.628281f, 0.555802f, 0.086014f, 0.0f};
  expF = 51.2f;
}

void Material::setPewter() {
  ambient = {0.10588f, 0.058824f, 0.113725f, 0.0f};
  diffuse = {0.427451f, 0.470588f, 0.541176f, 0.0f};
  specular = {0.3333f, 0.3333f, 0.521569f, 0.0f};
  expF = 9.84615f;
}

void Material::setSilver() {
  ambient = {0.19225f, 0.19225f, 0.19225f, 0.0f};
  diffuse = {0.50754f, 0.50754f, 0.50754f, 0.0f};
  specular = {0.508273f, 0.508273f, 0.508273f, 0.0f};
  expF = 51.2f;
}

void Material::setPolishedSilver() {
  ambient = {0.23125f, 0.23125f, 0.23125f, 0.0f};
  diffuse = {0.2775f, 0.2775f, 0.2775f, 0.0f};
  specular = {0.773911f, 0.773911f, 0.773911f, 0.0f};
  expF = 89.6f;
}
