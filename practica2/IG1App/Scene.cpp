#include "Scene.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

void Scene::init()
{ // OpenGL basic setting
  glClearColor(1.0, 1.0, 1.0, 1.0);  // background color (alpha=1 -> opaque)
  glEnable(GL_DEPTH_TEST);  // enable Depth test 
  glEnable(GL_TEXTURE_2D);

  //Call scene2D as init Scene
  //aspaNoria(12);
  practica2();
}
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
void Scene::move(bool up)
{
	//MOVE DRONE ARRIBA Y ABAJO
	Drone* drone = (Drone*) grObjects.at(1);
	drone->move(up);
}
void Scene::practica2()
{
	//clear Scene
	grObjects.clear();
	//Ejes
	grObjects.push_back(new EjesRGB(400.0));
	//ROTOR
	//grObjects.push_back(new Rotor(100.0, 100.0, 50.0, dvec3(1.0,0.0,0.0)));
	//CHASIS
	//grObjects.push_back(new Chasis(100.0, 25.0));
	//DRONE
	grObjects.push_back(new Drone(new Chasis(50.0, 5.0, 200.0+5), new Rotor(5.0, 5.0, 2.0,dvec3(0.0,0.0,0.0)), 200.0+5 ) );
	//ESFERA
	grObjects.push_back(new Esfera(200.0, 200, 100));
}
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

Scene::~Scene()
{ // free memory and resources   
  
  for (Entity* el: grObjects)
  {
	  delete el;  el = nullptr;
  }
}
//-------------------------------------------------------------------------

void Scene::render(Camera const& cam)
{
	for (Entity* el: grObjects)
	{
		el->render(cam);
	}
}
//-------------------------------------------------------------------------

void Scene::render(glm::dmat4 const& modelMat)
{
	for (Entity* el : grObjects)
	{
		el->render(modelMat);
	}
}
//-------------------------------------------------------------------------
void Scene::update()
{
	for (Entity* el : grObjects)
	{
		el->update();
	}
}
//-------------------------------------------------------------------------

void Scene::update(GLuint delta)
{
	for (Entity* el : grObjects)
	{
		el->update(delta);
	}
}
//-------------------------------------------------------------------------

