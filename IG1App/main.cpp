//#include <Windows.h>
//#include <gl/GL.h>    // OpenGL
//#include <gl/GLU.h>   // OpenGL Utility Library
//#include <GL/glut.h>  // OpenGL Utility Toolkit

#include <GL/freeglut.h>  // Free OpenGL Utility Toolkit for creating windows, initializing OpenGL contexts, and handling input events
#include <glm.hpp>  // OpenGL Mathematics. A C++ mathematics library for graphics programming 

#include "Viewport.h"
#include "Camera.h"
#include "Scene.h"

#include <iostream>

using namespace std;

//---------- Global variables -------------------------------------------------------------

// Viewport position and size
Viewport viewPort(800, 600);   

// Camera position, view volume and projection
Camera camera(&viewPort);    

glm::dvec2 mCoord; // coordenadas del ratón
int mBot; // boton pulsado

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
void mouseWheel(int n, int d,int x, int y);

//-------------------------------------------------------------------------
GLuint last_update_tick; bool stopAnim = false;
bool init1 = true;
int main(int argc, char *argv[])
{
  cout << "Starting console..." << '\n';

  // Initialization
  glutInit(&argc, argv);
  glutInitContextVersion(3, 3);
  glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);  // GLUT_CORE_PROFILE
  glutInitContextFlags(GLUT_DEBUG);   // GLUT_FORWARD_COMPATIBLE
  glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS); 
  
  glutInitWindowSize(800, 600);   // window size
  //glutInitWindowPosition (140, 140);

  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH /*| GLUT_STENCIL*/); // RGBA colors, double buffer, depth buffer and stencil buffer   
  
  int win = glutCreateWindow("IG1App");  // window's identifier
  
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

  // after creating the context
  camera.set2D(); 
  scene.init();   
  //scene.initExam();
  glutMainLoop(); 
    
  //cin.ignore(INT_MAX, '\n');  cin.get();  
  glutDestroyWindow(win);  // Destroy the context 
 
  return 0;
}
void mouse(int button, int state, int x, int y) {
	// state indica si el botón se ha presionado o soltado:
	//state = GLUT_UP / GLUT_DOWN;
	// button es el botón que se ha presionado o soltado:
	//button = GLUT_LEFT / GLUT_RIGHT_BUTTON;
	// (x, y) es la posición del ratón en la ventana,
	// siendo (0,0) la esquina (left, top)
	mCoord = glm::dvec2(x, glutGet(GLUT_WINDOW_HEIGHT) - y); // Guardamos las coordenadas del mouse 
	mBot = button; // Guardamos el botón del mouse en una var. global

	
}
void motion(int x, int y) {
	if (mBot == GLUT_LEFT_BUTTON) {
		glm::dvec2 mp = mCoord; // guardar la anterior posición en var. temp.
		mCoord = glm::dvec2(x, y); // Guardamos la posición actual
		mp = (mCoord - mp); // desplazamiento realizado
		camera.orbit(mp.x , mp.y); // sensitivity = 0.05
		glutPostRedisplay();
	}
	else if (mBot == GLUT_RIGHT_BUTTON) {
		glm::dvec2 mp = mCoord; // guardar la anterior posición en var. temp.
		mCoord = glm::dvec2(x, y); // Guardamos la posición actual
		mp = (mCoord - mp); // desplazamiento realizado
		camera.moveLR(mp.x);
		camera.moveUD(mp.y);
		glutPostRedisplay();
	}
}
void mouseWheel(int n, int d, int x, int y) {
	int m = glutGetModifiers();
	if (m == 0) // ninguna está presionada
	{
		// direction es la dirección de la rueda (+1 / -1)
		if (d == 1) camera.moveUD(-10);
		else camera.moveUD(10);	
		glutPostRedisplay();

	}
	else if (GLUT_ACTIVE_CTRL) {
		if (d == 1) {
			camera.moveFB(30);
		}
		else { camera.moveFB(-30); }
		glutPostRedisplay();

	}
}
//-------------------------------------------------------------------------

void display()   // double buffering
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   
  
  scene.render(camera);   
    
  glutSwapBuffers();  
}
//-------------------------------------------------------------------------

void resize(int newWidth, int newHeight)
{
  // Resize Viewport 
  viewPort.uploadSize(newWidth, newHeight);  
  
  // Resize Scene Visible Area 
  camera.uploadSize(viewPort.getW(), viewPort.getH());    // scale unchanged
}
//-------------------------------------------------------------------------

void key(unsigned char key, int x, int y)
{
  bool need_redisplay = true;

  switch (key) {
  case 27:  // Escape key 
    glutLeaveMainLoop();  // Freeglut's sentence for stopping glut's main loop 
    break;
  case 51:
	  if (!init1) {
		  scene.init();
		  init1 = !init1;
	  }
	  break;
  case 50:
	  if (init1) {
		  scene.init2();
		  init1 = !init1;
	  }
	  break;
  case'u':
	  stopAnim = !stopAnim;
	  break;
  case 'f':
	  Texture::save("../Bmps/screenshot.bmp");
	  break;
  case '+': 
    camera.uploadScale(+0.02);   // zoom in  (increases the scale)
    break;
  case '-':
    camera.uploadScale(-0.02);   // zoom out (decreases the scale)
    break;
  case 'l':
	camera.set3D(); 
	break;
  case 'o':
	camera.set2D();
  case'p':
	  camera.changePrj();
	  break;
	break;
  default:
	need_redisplay = false;
    break;
  } //switch

  if (need_redisplay)
    glutPostRedisplay();
}
//-------------------------------------------------------------------------

void specialKey(int key, int x, int y)
{
  bool need_redisplay = true;

  switch (key) {
  case GLUT_KEY_RIGHT:
    camera.pitch(1);   // rotate 1 on the X axis
    break;
  case GLUT_KEY_LEFT:
    camera.yaw(1);     // rotate 1 on the Y axis 
    break;
  case GLUT_KEY_UP:
    camera.roll(1);    // rotate 1 on the Z axis
    break;
  case GLUT_KEY_DOWN:
    camera.roll(-1);   // rotate -1 on the Z axis
    break;
  default:
    need_redisplay = false;
    break;
  }//switch

  if (need_redisplay)
    glutPostRedisplay();
}
//-------------------------------------------------------------------------
void update() {
	if (!stopAnim) {
		GLuint current_time = glutGet(GLUT_ELAPSED_TIME);
		if (current_time > last_update_tick + 50) {
			scene.update();
			last_update_tick = current_time;
			glutPostRedisplay();
		}
	}
}

