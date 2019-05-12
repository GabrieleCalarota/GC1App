//#pragma once
#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Camera.h"
#include "Entity.h"
#include "CompoundEntity.h"
#include "Light.h"

#include <vector>

//-------------------------------------------------------------------------

class Scene	: public CompoundEntity { 
public:
    Scene() { };
	//~Scene();
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
	//virtual void render(Camera const& cam) ;
	void render(glm::dmat4 const&);
	//void update();		  //update objects of the scene
	//void update(GLuint);  //autoupdate objects of the scene by parameter GLuint
protected:
		
	  //std::vector<Entity*> grObjects;  // Entities (graphics objects) of the scene
	  void scene2D();
	  DirLight *fixed;
	  SpotLight *minero;
	  bool apaga_todo = false;
	  //GLfloat ambient[];
	  //GLfloat diffuse[];
	  //GLfloat especular[];
};

//-------------------------------------------------------------------------

#endif //_H_Scene_H_

