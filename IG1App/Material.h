#pragma once
#include <GL/freeglut.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
class Material
{
public:
    glm::fvec4 ambient, diffuse, specular;
    GLfloat expF;
    GLuint face = GL_FRONT_AND_BACK;
    GLuint sh = GL_SMOOTH;

    Material();
    virtual ~Material();

    virtual void upload();

    void setBlackPlastic();
    void setBrass();
    void setBronze();
    void setChrome();
    void setCopper();
    void setGold();
    void setPewter();
    void setSilver();
    void setPolishedSilver();
};

