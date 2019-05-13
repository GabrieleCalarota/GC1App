//#pragma once
#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Camera.h"
#include "Entity.h"
#include "Light.h"

#include <vector>

//-------------------------------------------------------------------------

class Scene	: public CompoundEntity { 
public:
    Scene() { };
    void init(); 

	void moveUp(bool up);
	void moveRight(bool right);
	void practica2();
	void practica2_14();
	void scene3D();
	void aspaNoria(int);
	void practica2_18();
	void practica2_19();
	void practica2_20();
	void practica2_21();
	void practica2_22();
	void setLuzGlobal(GLfloat, GLfloat, GLfloat, GLfloat);
	void setColorDrone(bool);
	void render(glm::dmat4 const&);
	void setMaterial(char);
protected:
		
	  void scene2D();
	  DirLight *fixed;
	  SpotLight *minero;
	  bool apartado_18 = false;
	  bool apartado_19 = false;
	  bool apartado_20 = false;
	  bool apartado_21 = false;
	  bool apartado_22 = false;
};

//-------------------------------------------------------------------------

#endif //_H_Scene_H_

