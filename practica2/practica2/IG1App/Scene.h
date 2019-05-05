//#pragma once
#ifndef _H_Scene_H_
#define _H_Scene_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Camera.h"
#include "Entity.h"
//#include "Mesh.h"

#include <vector>

//-------------------------------------------------------------------------

class Scene	
{ 
public:
    Scene() { };
	~Scene();
    void init(); 

	void move(bool up);
	void practica2();
	void scene3D();
	void aspaNoria(int);
    void render(Camera const& cam);
	void render(glm::dmat4 const&);
	void update();		  //update objects of the scene
	void update(GLuint);  //autoupdate objects of the scene by parameter GLuint
protected:

	  std::vector<Entity*> grObjects;  // Entities (graphics objects) of the scene
	  void scene2D();
};

//-------------------------------------------------------------------------

#endif //_H_Scene_H_

