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
  glEnable(GL_LIGHTING);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_NORMALIZE);

  GLfloat difusa[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat ambiente[] = { 0.2, 0.2, 0.2, 1.0 };
  GLfloat especular[] = { 0.5, 0.5, 0.5, 1.0};
  GLfloat dir[] = { -1.0, -1.0, 0.0, 1.0 };
  glLightfv(GL_LIGHT1, GL_POSITION, dir);
  glLightfv(GL_LIGHT1, GL_AMBIENT, ambiente);
  glLightfv(GL_LIGHT1, GL_DIFFUSE, difusa);
  glLightfv(GL_LIGHT1, GL_SPECULAR, especular);

  //Call scene2D as init Scene
  //aspaNoria(12);
  //practica2();
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
void Scene::moveUp(bool up)
{
	//MOVE DRONE ARRIBA Y ABAJO
	Drone* drone = (Drone*) grObjects.at(1);
	drone->move(up);
}
void Scene::moveRight(bool right)
{
	//MOVE DRONE ARRIBA Y ABAJO
	Drone* drone = (Drone*)grObjects.at(1);
	drone->moveRight(right);
}
void Scene::practica2()
{
	//clear Scene
	grObjects.clear();
	//Ejes
	grObjects.push_back(new EjesRGB(400.0));
	//ROTOR
	//grObjects.push_back(new Rotor(100.0, 100.0, 50.0, dvec3(1.0, 0.0, 0.0), 200.0 + 5.0));
	//CHASIS
	//grObjects.push_back(new Chasis(100.0, 25.0));
	//DRONE
	grObjects.push_back(new Drone(new Chasis(50.0, 5.0, 200.0+5.0), new Rotor(5.0, 5.0, 2.0,dvec3(0.0,0.0,0.0)), 200.0+5.0) );
	//ESFERA
	grObjects.push_back(new Esfera(200.0, 80, 30));
}
void Scene::practica2_14() {
	//clear Scene
	grObjects.clear();
	//Ejes
	grObjects.push_back(new EjesRGB(400.0));
	/*//ROTOR
	//grObjects.push_back(new Rotor(100.0, 100.0, 50.0, dvec3(1.0,0.0,0.0)));
	//CHASIS
	//grObjects.push_back(new Chasis(100.0, 25.0));
	//DRONE
	Chasis* c0 = new Chasis(100.0, 10.0, 0.0);
	grObjects.push_back(new Drone(c0, new Rotor(10.0, 10.0, 4.0, dvec3(0.0, 0.0, 0.0)), 0.0));
	Chasis* c1 = new Chasis(15.0, 2.0, 0.0);
	Rotor* r = new Rotor(3.0, 3.0, 1.0, dvec3(0.0, 0.0, 0.0));
	dvec3 t1 = c0->getLeftBottomCorner();
	//rotor height
	GLdouble offset = 5.0;
	t1[1] += 4.0+2.0+offset;
	c1->setModelMat(translate(dmat4(1),t1));
	grObjects.push_back(new Drone(c1, r, 0.0));
	Chasis* c2 = new Chasis(15.0, 2.0, 0.0);
	dvec3 t2 = c0->getLeftTopCorner();
	t2[1] += 4.0+2.0 + offset;
	c2->setModelMat(translate(dmat4(1), t2));
	grObjects.push_back(new Drone(c2, r, 0.0));
	Chasis* c3 = new Chasis(15.0, 2.0, 0.0);
	dvec3 t3 = c0->getRightTopCorner();
	t3[1] += 4.0+2.0 + offset;
	c3->setModelMat(translate(dmat4(1), t3));
	grObjects.push_back(new Drone(c3, r, 0.0));
	Chasis* c4 = new Chasis(15.0, 2.0, 0.0);
	dvec3 t4 = c0->getRightBottomCorner();
	t4[1] += 4.0+2.0 + offset;
	c4->setModelMat(translate(dmat4(1), t4));
	grObjects.push_back(new Drone(c4, r, 0.0));*/
	grObjects.push_back(new SuperDrone(new Chasis(100.0, 10.0, 0.0), new Chasis(15.0, 2.0, 0.0), new Rotor(10.0, 10.0, 4.0, dvec3(0.0, 0.0, 0.0)), new Rotor(3.0, 3.0, 1.0, dvec3(0.0, 0.0, 0.0))));
	

	//ESFERA
	//grObjects.push_back(new Esfera(200.0, 80, 30));
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
void Scene::practica2_20()
{
	grObjects.clear();
	//Ejes
	grObjects.push_back(new EjesRGB(400.0));
	//Esfera
	grObjects.push_back(new Esfera(200.0, 80, 30));
}
//-------------------------------------------------------------------------

/*Scene::~Scene()
{ // free memory and resources   
  
  for (Entity* el: grObjects)
  {
	  delete el;  el = nullptr;
  }
}*/
//-------------------------------------------------------------------------

/*void Scene::render(Camera const& cam)
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
}*/
//-------------------------------------------------------------------------

