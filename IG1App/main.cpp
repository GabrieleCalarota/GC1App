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
GLdouble CLIENT_WIDTH = 800, CLIENT_HEIGHT = 600;
Viewport viewPort1(800, 600); 
Viewport viewPort2(800, 600);

// Camera position, view volume and projection
Camera camera1(&viewPort1);
Camera camera2(&viewPort2);

// Graphics objects of the scene
Scene scene1 = Scene();
Scene scene2 ;
bool auto_update;
bool baldosas = false;
bool twoPorts = false;
bool coloDrone = false;
GLuint last_update_tick;

//Coordenadas del mouse y keyboard
glm::dvec2 mCoord;
int mBot = 0;

//GLfloat luz[] = {0, 0, 0, 1};

//----------- Callbacks ----------------------------------------------------

void display();
void embaldosar(int);
void twoPortsDisplay();
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
  
  int win = glutCreateWindow("Gabriele Calarota App - Scene 1");  // window's identifier

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
  camera1.set2D();
  camera2.set2D();
  scene1.init();
  scene1.practica2_18();
  //scene2.init();
  //scene2.practica2_14();

  //scene1.aspaNoria(12);
  
  glutMainLoop(); 
    
  glutDestroyWindow(win);  // Destroy the context 
 
  return 0;
}

//-------------------------------------------------------------------------
void display()   // double buffering
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   
  
  if (baldosas) // Se muestran 4 puertos de vista
	  embaldosar(2);
  else {
	  twoPortsDisplay();
  }
    
  glutSwapBuffers();  
}
//-------------------------------------------------------------------------

void embaldosar(int nCol) {
	GLdouble SVAratio = (camera1.xRight - camera1.xLeft) / (camera1.yTop - camera1.yBot);
	GLdouble w = (GLdouble)CLIENT_WIDTH / (GLdouble)nCol;
	GLdouble h = w / SVAratio;
	for (GLint c = 0; c < nCol; c++) {
		GLdouble currentH = 0;
		while ((currentH + h) <= CLIENT_HEIGHT) {
			Viewport* vp = new Viewport((GLint)w, (GLint)h);
			vp->uploadPos((GLint)(c*w), (GLint)currentH);
			vp->upload();
			camera1.setVP(vp);
			scene1.render(camera1.getViewMat());
			currentH += h;
		} // del while
	} // del for
}
//-------------------------------------------------------------------------

void twoPortsDisplay() {
	if (twoPorts) {
		GLdouble SVAratio1 = (camera1.xRight - camera1.xLeft) / (camera1.yTop - camera1.yBot);
		GLdouble SVAratio2 = (camera2.xRight - camera2.xLeft) / (camera2.yTop - camera2.yBot);
		GLdouble w = (GLdouble)glutGet(GLUT_WINDOW_WIDTH)/2;
		GLdouble h1 = (GLdouble)w / SVAratio1;
		GLdouble h2 = (GLdouble)w / SVAratio2;
		GLdouble h_pos = glutGet(GLUT_WINDOW_HEIGHT) / 2 - (CLIENT_HEIGHT / 2);
		viewPort1.uploadSize(w, h1);
		camera1.uploadSize(viewPort1.getW(), viewPort1.getH());
		scene1.render(camera1.getViewMat());
		viewPort2.uploadSize(w, h2);
		viewPort2.uploadPos(w, 0);
		camera2.uploadSize(viewPort2.getW(), viewPort2.getH());
		scene2.render(camera2.getViewMat());
	}
	else {
		resize(CLIENT_WIDTH, CLIENT_HEIGHT);
		scene1.render(camera1.getViewMat());
	}
}
//-------------------------------------------------------------------------


void resize(int newWidth, int newHeight)
{
	if (twoPorts) {
		GLdouble w = glutGet(GLUT_WINDOW_WIDTH) / 2;
		GLdouble SVAratio1 = (camera1.xRight - camera1.xLeft) / (camera1.yTop - camera1.yBot);
		GLdouble SVAratio2 = (camera2.xRight - camera2.xLeft) / (camera2.yTop - camera2.yBot);
		GLdouble h1 = (GLdouble)w / SVAratio1;
		GLdouble h2 = (GLdouble)w / SVAratio2;
		// Resize Viewport 
		viewPort1.uploadSize(w, h1);

		// Resize Scene Visible Area 
		camera1.uploadSize(viewPort1.getW(), viewPort1.getH());    // scale unchanged
		viewPort2.uploadSize(w, h2);

		// Resize Scene Visible Area 
		camera2.uploadSize(viewPort2.getW(), viewPort2.getH());
	}
	else {
		// Resize Viewport 
		viewPort1.uploadSize(newWidth, newHeight);

		// Resize Scene Visible Area 
		camera1.uploadSize(viewPort1.getW(), viewPort1.getH());    // scale unchanged
	}
}
//-------------------------------------------------------------------------

void update() {
	if (auto_update) {
		GLuint now = glutGet(GLUT_ELAPSED_TIME);
		scene1.update(now - last_update_tick);
		scene2.update(now - last_update_tick);
		if (twoPorts) {
			scene2.update(now - last_update_tick);
		}
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
	//GLUT_UP/GLUT_DOWN costantes de estados
	glm::dvec2 mp = mCoord;
	mCoord = glm::dvec2(x, y);

	//std::cout << "motion "<< x << ", " << y << endl;
	Camera *tmp = &camera1;
	if (twoPorts) {
		if (x >= (glutGet(GLUT_WINDOW_WIDTH) / 2))
			tmp = &camera2;
	}

	mp = (mCoord - mp);
	if (mBot == GLUT_LEFT_BUTTON) {
		tmp->orbit(mp.x*0.05, mp.y);
	}
	else if (mBot == GLUT_RIGHT_BUTTON) {
		tmp->moveUD(mp.y);
		tmp->moveLR(-mp.x);
	}
	glutPostRedisplay();
}
void mouseWheel(int n, int d, int x, int y)
{
	int m = glutGetModifiers();
	Camera *tmp = &camera1;
	if (twoPorts) {
		if (x >= (glutGet(GLUT_WINDOW_WIDTH) / 2))
			tmp = &camera2;
	}
	if (m == 0) {
		if (d == 1) {
			tmp->moveFB(5);
		}
		else
			tmp->moveFB(-5);
	}
	else if (m == GLUT_ACTIVE_CTRL) {
		if (d == 1) tmp->uploadScale(0.1);
		else tmp->uploadScale(-0.1);
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
    camera1.uploadScale(+0.01);   // zoom in  (increases the scale)
    break;
  case '-':
    camera1.uploadScale(-0.01);   // zoom out (decreases the scale)
    break;
  case 'b':
	  coloDrone = !coloDrone;
	  scene1.setColorDrone(coloDrone);
	  break;
  case 'c':
	  scene1.setMaterial('c');
	  break;
  case 'l':
	  camera1.set3D();
	  break;
  case 'g':
	  scene1.setMaterial('g');
	  break;
  case 'h':
	  baldosas = !baldosas;
	  if (!baldosas) {
		  resize(CLIENT_WIDTH, CLIENT_HEIGHT);
	  }
	  break;
  case 'j':
	  twoPorts = !twoPorts;
	  if (twoPorts) {
		  glutSetWindowTitle("Gabriele Calarota App - Scene 2");
	  }
	  else {
		  glutSetWindowTitle("Gabriele Calarota App - Scene 1");
	  }
	  break;
  case 'k':
	  if (twoPorts) {
		  camera2.yaw(1);
	  }
	  break;
  case 'm':
	  scene1.setLuzGlobal(0.5, 0.5, 0.5, 1);
	  break;
  case 'n':
	  scene1.setLuzGlobal(0, 0, 0, 1);
	  break;
  case 'o':
	camera1.set2D();
	break;
  case 's':
	  scene1.setMaterial('s');
	  break;
  case 'u':
	  scene1.update();
	  if (twoPorts)
		scene2.update();
	  break;
  case 'U':
	 auto_update = !(auto_update);
	 //When auto-update is back, will restart smoothly
	 if (auto_update) {
		 last_update_tick = glutGet(GLUT_ELAPSED_TIME);
	 }
	 break;
  case '3':
	  scene1.scene3D();
	  //scene2.scene3D();
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
    //camera.pitch(1);   // rotate 1 on the X axis
	  scene1.moveRight(true);
	  //scene2.moveRight(true);
    break;
  case GLUT_KEY_LEFT:
    //camera.yaw(1);     // rotate 1 on the Y axis 
	  scene1.moveRight(false);
	  //scene2.moveRight(false);
	  break;
  case GLUT_KEY_UP:
	  scene1.moveUp(true);
	  //scene2.moveUp(true);
	  need_redisplay = true;
    //camera.roll(1);    // rotate 1 on the Z axis
    break;
  case GLUT_KEY_DOWN:
	  scene1.moveUp(false);
	  //scene2.moveUp(false);
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

