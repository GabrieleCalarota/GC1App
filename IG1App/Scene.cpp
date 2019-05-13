#include "Scene.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>
#include "Light.h"

using namespace glm;

//-------------------------------------------------------------------------


void Scene::init()
{ // OpenGL basic setting
  glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
  glEnable(GL_DEPTH_TEST);  // enable Depth test 
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_LIGHTING);
  glEnable(GL_NORMALIZE);
  

  GLfloat ambientColor[] = { 0.5, 0.5,0.5, 1.0 }; 
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
  
  fixed = new DirLight();
  fixed->setPosDir(fvec3(1, 1, 0));
  fixed->setAmb(fvec4(0.2, 0.2, 0.2,1.0));
  fixed->setSpec(fvec4(0.5, 0.5, 0.5,1.0));
  fixed->setDiff(fvec4(1.0, 1.0, 1.0,1.0));

  minero = new SpotLight(fvec3(0,0,-1));
  minero->setAmb(fvec4(0, 0, 0, 1));
  minero->setDiff(fvec4(0.4, 0.8, 0.0, 1.0));
  minero->setSpec(fvec4(0.5, 0.5, 0.5, 1.0));
  minero->setSpot(fvec3(0, 0, -1), 10.0, 0);

}
//-------------------------------------------------------------------------

void Scene::scene2D()
{
	//clear Scene
	grObjects.clear();
	//Polispirale
	grObjects.push_back(new Poliespiral(dvec2(0, 0), 0, 45, 1, 1, 50));
	// Drago
	grObjects.push_back(new Dragon(3000));
	//TrianguloRGB
	grObjects.push_back(new TrianguloAnimado(100.0));
	//RectanguloRGB
	grObjects.push_back(new RectanguloRGB(50.0,200.0));

}
//-------------------------------------------------------------------------

void Scene::moveUp(bool up)
{
	//MOVE DRONE ARRIBA Y ABAJO
	Drone* drone = (Drone*) grObjects.at(1);
	drone->move(up);
}
//-------------------------------------------------------------------------

void Scene::moveRight(bool right)
{
	//MOVE DRONE ARRIBA Y ABAJO
	Drone* drone = (Drone*)grObjects.at(1);
	drone->moveRight(right);
}
//-------------------------------------------------------------------------

void Scene::practica2()
{
	//clear Scene
	grObjects.clear();
	//Ejes
	grObjects.push_back(new EjesRGB(400.0));
	//DRONE
	grObjects.push_back(new Drone(new Chasis(50.0, 5.0, 200.0+5.0), new Rotor(5.0, 5.0, 2.0,dvec3(0.0,0.0,0.0)), 200.0+5.0) );
	//ESFERA
	grObjects.push_back(new Esfera(200.0, 80, 30));
}
//-------------------------------------------------------------------------

void Scene::practica2_14() {
	//clear Scene
	grObjects.clear();
	//Ejes
	grObjects.push_back(new EjesRGB(400.0));
	grObjects.push_back(new SuperDrone(new Chasis(100.0, 10.0, 0.0), new Chasis(15.0, 2.0, 0.0), new Rotor(10.0, 10.0, 4.0, dvec3(0.0, 0.0, 0.0)), new Rotor(3.0, 3.0, 1.0, dvec3(0.0, 0.0, 0.0))));
}
//-------------------------------------------------------------------------

void Scene::scene3D()
{
	//clear Scene
	grObjects.clear();
	//EstrellaRGB
	grObjects.push_back(new Estrella3D(50.0, 10.0, 100.0));
	//contCubo
	//grObjects.push_back(new Caja(100.0,1,1));
	//Suelo
	grObjects.push_back(new Suelo(500, 500, 4,4));
	//Foto
	grObjects.push_back(new Foto(70, 100));

}
//-------------------------------------------------------------------------

void Scene::aspaNoria(int n)
{
	//clear Scene
	grObjects.clear();
	//Ejes
	grObjects.push_back(new EjesRGB(400.0));
	//canjilon
	grObjects.push_back(new CajaTex(100.0,n));
	//tablero1
	grObjects.push_back(new Tablero(100.0, -1,n));
	//tablero2
	grObjects.push_back(new Tablero(100.0,1,n));
}
//-------------------------------------------------------------------------

void Scene::practica2_18()
{
	apartado_18 = true;
	practica2_19();
	apartado_19 = false;
}
//-------------------------------------------------------------------------

void Scene::practica2_19()
{
	glEnable(GL_COLOR_MATERIAL);
	apartado_19 = true;
	minero->disable();
	grObjects.clear();
	//Ejes
	grObjects.push_back(new EjesRGB(400.0));
	//Esfera
	Esfera *e = new Esfera(200.0, 50, 50);
	grObjects.push_back(e);
	e->setMaterial(nullptr);
}
//-------------------------------------------------------------------------

void Scene::practica2_20()
{
	apartado_20 = true;
	glDisable(GL_COLOR_MATERIAL);
	minero->disable();
	grObjects.clear();
	//Ejes
	grObjects.push_back(new EjesRGB(400.0));
	//Esfera
	grObjects.push_back(new Esfera(200.0, 80, 30));
}
//-------------------------------------------------------------------------

void Scene::practica2_21()
{
	apartado_21 = true;
	glDisable(GL_COLOR_MATERIAL);
	grObjects.clear();
	//Ejes
	grObjects.push_back(new EjesRGB(400.0));
	//Esfera
	grObjects.push_back(new Esfera(200.0, 80, 30));
}
//-------------------------------------------------------------------------

void Scene::practica2_22()
{
	grObjects.clear();
	apartado_22 = true;
	//Ejes
	grObjects.push_back(new EjesRGB(400.0));
	//Dron
	grObjects.push_back(new Drone(new Chasis(50.0, 5.0, 200.0 + 5.0), new Rotor(5.0, 5.0, 2.0, dvec3(0.0, 0.0, 0.0)), 200.0 + 5.0));
	//Esfera
	grObjects.push_back(new Esfera(200.0, 50, 50));
	setLuzGlobal(0.0, 0.0, 0.0, 1.0);
}
//-------------------------------------------------------------------------

void Scene::setLuzGlobal(GLfloat a, GLfloat b, GLfloat c , GLfloat d)
{
	GLfloat ambient[] = { a,b,c,d };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
	if (a == 0.0){
		if (apartado_19) {
			return;
		}
		if (fixed != nullptr)
			fixed->disable();
		if ( apartado_18 || apartado_20 || apartado_21) {
			return;
		}
		if (minero != nullptr)
			minero->disable();
	}
	else {
		if (apartado_19) {
			return;
		}
		if (fixed != nullptr)
			fixed->enable();
		if (apartado_18 || apartado_20 || apartado_21) {
			return;
		}
		if (minero != nullptr)
			minero->enable();
	}
}
//-------------------------------------------------------------------------

void Scene::setColorDrone(bool a)
{
	if (apartado_22) {
		if (a) {
			glEnable(GL_COLOR_MATERIAL);
			glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
			//((Esfera*)grObjects.at(1))->setMaterial(nullptr);
			if (fixed != nullptr)
				fixed->enable();
			//glEnable(GL_COLOR_MATERIAL);
			//GLfloat ambient[] = { 0.5,0.5,0.5,1 };
			//glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
		}
		else {
			glDisable(GL_COLOR_MATERIAL);
			Material *m = new Material();
			m->setGold();
			m->upload();
			((Esfera*)grObjects.at(1))->setMaterial(m);
			/*if (fixed != nullptr) {
				fixed->disable();
			}*/
		}
	}
}
//-------------------------------------------------------------------------

void Scene::render(glm::dmat4 const& modelMat)
{
	if (fixed != nullptr)
		fixed->upload(modelMat);
	if (minero != nullptr)
		minero->upload(dmat4(1.0));
	CompoundEntity::render(modelMat);
}
//-------------------------------------------------------------------------

void Scene::setMaterial(char c)
{
	Material *m = new Material();
	switch (c) {
	case 'g':
		m->setGold();
		break;
	case 'c':
		m->setCopper();
		break;
	case 's':
		m->setSilver();
		break;
	}
	m->upload();
	for (Entity* el : grObjects) {
		((Esfera*)el)->setMaterial(m);
	}
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

