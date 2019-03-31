#include <GL/glut.h>  // OpenGL Utility Toolkit
#include <Windows.h>
#include <gl/GL.h>   // OpenGL
#include <gl/GLU.h>  // OpenGL Utility Library

#include <GL/freeglut.h>  // Free OpenGL Utility Toolkit for creating windows, initializing OpenGL contexts, and handling input events
#include <GL/freeglut_ext.h>
#include <GL/freeglut_std.h>
#include <glm.hpp>  // OpenGL Mathematics. A C++ mathematics library for graphics programming

#include "Camera.h"
#include "Scene.h"
#include "Viewport.h"

#include <iostream>

using namespace std;

//---------- Global variables
//-------------------------------------------------------------

// Viewport position and size
Viewport viewPort(800, 600);

// Camera position, view volume and projection
Camera camera(&viewPort);

glm::dvec2 mCoord;  // coordenadas del ratón
int mBot;           // boton pulsado

// Graphics objects of the scene
Scene scene;

//----------- Callbacks ----------------------------------------------------

void display();
void resize(int newWidth, int newHeight);
void key(unsigned char key, int x, int y);
void specialKey(int key, int x, int y);
void update();
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void mouseWheel(int n, int d, int x, int y);

//-------------------------------------------------------------------------
GLuint lastUpdateTick;
bool stopAnim = false;

int main(int argc, char *argv[]) {
  cout << "Starting console..." << '\n';

  // Initialization
  glutInit(&argc, argv);

  glutInitContextVersion(3, 3);
  glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);  // GLUT_CORE_PROFILE
  glutInitContextFlags(GLUT_DEBUG);  // GLUT_FORWARD_COMPATIBLE
  glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

  glutInitWindowSize(800, 600);  // window size
  // glutInitWindowPosition (140, 140);

  glutInitDisplayMode(
      GLUT_RGBA | GLUT_DOUBLE |
      GLUT_DEPTH /*| GLUT_STENCIL*/);  // RGBA colors, double buffer, depth
                                       // buffer and stencil buffer

  const auto win = glutCreateWindow("IG1App");  // window's identifier

  // Callback registration
  glutReshapeFunc(resize);
  glutKeyboardFunc(key);
  glutSpecialFunc(specialKey);
  glutDisplayFunc(display);
  glutIdleFunc(update);
  glutMouseFunc(mouse);
  glutMotionFunc(motion);
  glutMouseWheelFunc(mouseWheel);

  cout << glGetString(GL_VERSION) << '\n';
  cout << glGetString(GL_VENDOR) << '\n';

  Scene::init();

  // after creating the context
  camera.set2D();
  scene.scene2D();
  glutMainLoop();

  // cin.ignore(INT_MAX, '\n');  cin.get();
  glutDestroyWindow(win);  // Destroy the context

  return 0;
}

void display()  // double buffering
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  scene.render(camera);

  glutSwapBuffers();
}

void resize(const int newWidth, const int newHeight) {
  // Resize Viewport
  viewPort.uploadSize(newWidth, newHeight);

  // Resize Scene Visible Area
  camera.uploadSize(viewPort.getW(), viewPort.getH());  // scale unchanged
}

void key(const unsigned char key, int x, int y) {
  auto needRedisplay = true;

  switch (key) {
    case 27:                // Escape key
      glutLeaveMainLoop();  // Freeglut's sentence for stopping glut's main loop
      break;
    case 50:
      scene.scene2D();
      break;
    case 51:
      scene.scene3D();
      break;
    case '+':
      camera.uploadScale(+0.02);  // zoom in  (increases the scale)
      break;
    case '-':
      camera.uploadScale(-0.02);  // zoom out (decreases the scale)
      break;
    case 'l':
      camera.set3D();
      break;
    case 'o':
      camera.set2D();
      break;
    case 'u':
      stopAnim = !stopAnim;
      break;
    case 'p':
      camera.changePrj();
      break;
    case 'f':
      // ReSharper disable once StringLiteralTypo
      Texture::save("../Bmps/screenshot.bmp");
      break;
    default:
      needRedisplay = false;
      break;
  }  // switch

  if (needRedisplay) glutPostRedisplay();
}

void specialKey(const int key, int x, int y) {
  auto needRedisplay = true;

  switch (key) {
    case GLUT_KEY_RIGHT:
      camera.moveLR(1.0);
      break;
    case GLUT_KEY_LEFT:
      camera.moveLR(-1.0);
      break;
    case GLUT_KEY_UP:
      camera.moveUD(1.0);
      break;
    case GLUT_KEY_DOWN:
      camera.moveUD(-1.0);
      break;
    default:
      needRedisplay = false;
      break;
  }  // switch

  if (needRedisplay) glutPostRedisplay();
}

void mouse(const int button, int state, const int x, const int y) {
  // button is the button from the mouse that has been clicked, it's either
  // GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON. state indicates whether or not the
  // button was pressed or left, it's either GLUT_UP or GLUT_DOWN.
  mBot = button;
  mCoord = glm::dvec2(x, glutGet(GLUT_WINDOW_HEIGHT) - y);
}

void motion(int x, int y) {
  if (mBot == GLUT_LEFT_BUTTON) {
    auto mp = mCoord;           // guardar la anterior posición en var. temp.
    mCoord = glm::dvec2(x, y);  // Guardamos la posición actual
    mp = (mCoord - mp);         // desplazamiento realizado
    camera.orbit(mp.x * 0.5, mp.y);  // sensitivity = 0.05
    glutPostRedisplay();
  } else if (mBot == GLUT_RIGHT_BUTTON) {
    auto mp = mCoord;           // guardar la anterior posición en var. temp.
    mCoord = glm::dvec2(x, y);  // Guardamos la posición actual
    mp = mCoord - mp;           // desplazamiento realizado
    camera.moveLR(-mp.x);
    camera.moveUD(mp.y);
    glutPostRedisplay();
  }
}

void mouseWheel(int n, const int d, int x, int y) {
  const auto m = glutGetModifiers();
  if (m == 0)  // ninguna está presionada
  {
    // direction es la dirección de la rueda (+1 / -1)
    if (d == 1)
      camera.moveUD(5);
    else
      camera.moveUD(-5);
    glutPostRedisplay();

  } else if (GLUT_ACTIVE_CTRL) {
    if (d == 1) {
      camera.moveFB(5);
    } else {
      camera.moveFB(-5);
    }
    glutPostRedisplay();
  }
}

void update() {
  if (!stopAnim) {
    const GLuint currentTime = glutGet(GLUT_ELAPSED_TIME);
    if (currentTime > lastUpdateTick + 50) {
      scene.update();
      lastUpdateTick = currentTime;
      glutPostRedisplay();
    }
  }
}
