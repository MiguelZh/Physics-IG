#include "EntityMaterial.h"
#include "IndexMesh.h"

EntityMaterial::EntityMaterial() = default;

EntityMaterial::~EntityMaterial() {
  delete indexMesh_;
  delete textureMatTexture_;
}

void EntityMaterial::setTexture(Texture *text) { textureMatTexture_ = text; }

void EntityMaterial::setMaterial(Material *material) { material_ = material; }






