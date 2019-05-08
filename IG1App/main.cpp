// #include <GL/glut.h>  // OpenGL Utility Toolkit
// #include <Windows.h>
// #include <gl/GL.h>   // OpenGL
// #include <gl/GLU.h>  // OpenGL Utility Library

#include <GL/freeglut.h>  // Free OpenGL Utility Toolkit for creating windows, initializing OpenGL contexts, and handling input events

#include <glm.hpp>  // OpenGL Mathematics. A C++ mathematics library for graphics programming
#include <iostream>

#include "Camera.h"
#include "Scene.h"
#include "Viewport.h"

using namespace std;

// ---------- Global variables

// Viewport position and size
Viewport viewPort(800, 600);

// Camera position, view volume and projection
Camera camera(&viewPort);

glm::dvec2 mCoordinates;  // Mouse coordinates
int mButton;              // Clicked button

// Graphics objects of the scene
Scene scene;

void display();
void resize(int newWidth, int newHeight);
void key(unsigned char key, int x, int y);
void specialKey(int key, int x, int y);
void update();
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void mouseWheel(int n, int direction, int x, int y);

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
  scene.sceneSphere();
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
    case 52:
      scene.sceneSphere();
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
    case 'v':
      scene.toggleCamLight();
      break;
    case 'b':
      scene.toggleSphereLight();
      break;
    case 'c':
      scene.toggleDirLight();
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
  mButton = button;
  mCoordinates = glm::dvec2(x, glutGet(GLUT_WINDOW_HEIGHT) - y);
}

void motion(const int x, const int y) {
  if (mButton == GLUT_LEFT_BUTTON) {
    auto mp =
        mCoordinates;  // Save the previous position in a temporary variable
    mCoordinates = glm::dvec2(x, y);  // Save the current position
    mp = mCoordinates - mp;           // Make a movement
    camera.orbit(-mp.x * 0.1, mp.y);
    glutPostRedisplay();
  } else if (mButton == GLUT_RIGHT_BUTTON) {
    auto mp =
        mCoordinates;  // Save the previous position in a temporary variable
    mCoordinates = glm::dvec2(x, y);  // Save the current position
    mp = mCoordinates - mp;           // Make a movement
    camera.moveLR(-mp.x);
    camera.moveUD(mp.y);
    glutPostRedisplay();
  }
}

void mouseWheel(int n, const int direction, int x, int y) {
  const auto m = glutGetModifiers();
  if (m == 0)  // No key is pressed
  {
    camera.moveUD(direction == 1 ? 5 : -5);
    glutPostRedisplay();
  } else if (GLUT_ACTIVE_CTRL) {
    camera.moveFB(direction == 1 ? 5 : -5);
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
