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

// Graphics objects of the scene
Scene scene;   
bool auto_update;
GLuint last_update_tick;

//Coordenadas del mouse y keyboard
glm::dvec2 mCoord;
int mBot = 0;

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

  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH /*| GLUT_STENCIL*/); // RGBA colors, double buffer, depth buffer and stencil buffer   
  
  int win = glutCreateWindow("Gabriele Calarota App");  // window's identifier

  //AutoUpdate initialization
  auto_update = true;
  last_update_tick = 0;
  
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
  //scene.aspaNoria(12);
  
  glutMainLoop(); 
    
  //cin.ignore(INT_MAX, '\n');  cin.get();  
  glutDestroyWindow(win);  // Destroy the context 
 
  return 0;
}

//-------------------------------------------------------------------------
void display()   // double buffering
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   
  
  scene.render(camera.getViewMat());
    
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

void update() {
	if (auto_update) {
		GLuint now = glutGet(GLUT_ELAPSED_TIME);
		scene.update(now - last_update_tick);
		last_update_tick = now;
		glutPostRedisplay();

	}
}
void mouse(int button, int state, int x, int y)
{
	//costante di estado GLUT_UP/GLUT_DOWN
	//stato passa da pulsato a rilasciato o viceversa 
	//prende le coordinate x,y della finestra
	mBot = button;
	mCoord = glm::dvec2(x, y);
	//y ha origine in alto a dinistra, mentre nel punto di vista sta in basso
	//y(viewport) = glutGet(GLUT_WINDOW_HEIGHT)-y;
}
void motion(int x, int y)
{
  //coordinate di dove viene rilasciato il mouse
	//GLUT_LEFT_BUTTON,GLUT_RIGHT_BUTTON
	//GLUT_UP/GLUT_DOWN costantes di estado
	glm::dvec2 mp = mCoord;
	mCoord = glm::dvec2(x, y);

	mp = (mCoord - mp);
	if (mBot == GLUT_LEFT_BUTTON) {
		camera.orbit(mp.x*0.05, mp.y);
	}
	else if (mBot == GLUT_RIGHT_BUTTON) {
		camera.moveUD(mp.y);
		camera.moveLR(-mp.x);
	}
	glutPostRedisplay();
}
void mouseWheel(int n, int d, int x, int y)
{
	int m = glutGetModifiers();
	if (m == 0) {
		if (d == 1) {
			camera.moveFB(5);
		}
		else
			camera.moveFB(-5);
	}
	else if (m == GLUT_ACTIVE_CTRL) {
		if (d == 1) camera.uploadScale(0.1);
		else camera.uploadScale(-0.1);
	}
	glutPostRedisplay();
}
//-------------------------------------------------------------------------

void key(unsigned char key, int x, int y)
{
  bool need_redisplay = true;

  switch (key) {
  case 27:  // Escape key 
    glutLeaveMainLoop();  // Freeglut's sentence for stopping glut's main loop 
    break;
  case '+': 
    camera.uploadScale(+0.01);   // zoom in  (increases the scale)
    break;
  case '-':
    camera.uploadScale(-0.01);   // zoom out (decreases the scale)
    break;
  case 'l':
	camera.set3D(); 
	break;
  case 'o':
	camera.set2D();
	break;
  case 'u':
	  scene.update();
	  break;
  case 'U':
	 auto_update = !(auto_update);
	 //When auto-update is back, will restart smoothly
	 if (auto_update) {
		 last_update_tick = glutGet(GLUT_ELAPSED_TIME);
	 }
	 break;
  case '3':
	  scene.scene3D();
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
	  scene.move(true);
	  need_redisplay = true;
    //camera.roll(1);    // rotate 1 on the Z axis
    break;
  case GLUT_KEY_DOWN:
	  scene.move(false);
	  need_redisplay = true;
    //camera.roll(-1);   // rotate -1 on the Z axis
    break;
  default:
    need_redisplay = false;
    break;
  }//switch

  if (need_redisplay)
    glutPostRedisplay();
}
//-------------------------------------------------------------------------

