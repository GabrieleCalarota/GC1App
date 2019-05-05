#include "Entity.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;
#define GLM_ENABLE_EXPERIMENTAL
#include <gtc/string_cast.hpp>
#include <iostream>

//-------------------------------------------------------------------------

void Entity::uploadMvM(dmat4 const& modelViewMat) const
{ 
	dmat4 aMat = modelViewMat * modelMat;
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixd(value_ptr(aMat));
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

EjesRGB::EjesRGB(GLdouble l): Entity() 
{
  mesh = Mesh::createRGBAxes(l);
}
//-------------------------------------------------------------------------

EjesRGB::~EjesRGB() 
{ 
	delete mesh; mesh = nullptr; 
};
//-------------------------------------------------------------------------

void EjesRGB::render(Camera const& cam)
{
	if (mesh != nullptr) {
		uploadMvM(cam.getViewMat()); 
		glLineWidth(2);
		mesh->render();
		glLineWidth(1);
	}
}
void EjesRGB::update()
{
}
void EjesRGB::update(GLuint)
{
}
void EjesRGB::render(glm::dmat4 const & modelViewMat)
{
	if (mesh != nullptr) {
		uploadMvM(modelViewMat);
		glLineWidth(2);
		mesh->render();
		glLineWidth(1);
	}
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

Poliespiral::Poliespiral(dvec2 verIni,
	GLdouble angIni,
	GLdouble incrAng,
	GLdouble ladoIni,
	GLdouble incrLado,
	GLuint numVert) : Entity()
{
	mesh = Mesh::generaPoliespiral(verIni, angIni, incrAng, ladoIni, incrLado, numVert);
	modelMat = translate(dmat4(1), glm::dvec3(0.0, 0.0, -200.0));
}
//-------------------------------------------------------------------------

Poliespiral::~Poliespiral()
{
	delete mesh; mesh = nullptr;
};
//-------------------------------------------------------------------------

void Poliespiral::render(Camera const& cam)
{
	if (mesh != nullptr) {
		uploadMvM(cam.getViewMat());
		glLineWidth(2);
		glColor3d(1.0, 0.0, 0.0);
		mesh->render();
	}
}
void Poliespiral::update(){}
//-------------------------------------------------------------------------

void Poliespiral::update(GLuint){}
void Poliespiral::render(glm::dmat4 const & modelViewMat)
{
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

Dragon::Dragon(GLuint numVert) : Entity()
{
	mesh = Mesh::generaDragon(numVert);
	modelMat = translate(dmat4(1), glm::dvec3(0.0, 0.0, -150.0));

}
//-------------------------------------------------------------------------

Dragon::~Dragon()
{
	delete mesh; mesh = nullptr;
};
//-------------------------------------------------------------------------

void Dragon::render(Camera const& cam)
{
	if (mesh != nullptr) {
		dmat4 matAux = cam.getViewMat();
		matAux = translate(matAux, glm::dvec3(-40.0, -170.0, 0.0));
		matAux = scale(matAux, glm::dvec3(40.0, 40.0, 0.0));
		uploadMvM(matAux);
		glColor3d(0.4, 0.5, 0.1);
		glPointSize(2);
		mesh->render();
	}
}
//-------------------------------------------------------------------------

void Dragon::update(){}
//-------------------------------------------------------------------------

void Dragon::update(GLuint){}
void Dragon::render(glm::dmat4 const & modelViewMat)
{
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

TrianguloRGB::TrianguloRGB(GLdouble r) : Entity()
{
	mesh = Mesh::generaTrianguloRGB(r, 0, 0);
	modelMat = translate(dmat4(1), glm::dvec3(0.0, 0.0, -100.0));
}
//-------------------------------------------------------------------------

TrianguloRGB::~TrianguloRGB()
{
	delete mesh; mesh = nullptr;
};
//-------------------------------------------------------------------------

void TrianguloRGB::render(Camera const& cam)
{
	if (mesh != nullptr) {
		uploadMvM(cam.getViewMat());
		glLineWidth(3);
		glColor3d(1.0, 0.0, 0.0);
		glPolygonMode(GL_BACK, GL_LINE);
		glPolygonMode(GL_BACK, GL_POINT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mesh->render();
	}
}
//-------------------------------------------------------------------------

void TrianguloRGB::update(){}
void TrianguloRGB::render(glm::dmat4 const & modelViewMat)
{
}
//-------------------------------------------------------------------------

RectanguloRGB::RectanguloRGB(GLdouble h, GLdouble w) : Entity()
{
	mesh = Mesh::generaRectanguloRGB(h, w);
	modelMat = translate(dmat4(1), glm::dvec3(0.0, 0.0, 50.0));
}
//-------------------------------------------------------------------------

RectanguloRGB::~RectanguloRGB()
{
	delete mesh; mesh = nullptr;
};
//-------------------------------------------------------------------------

void RectanguloRGB::render(Camera const& cam)
{
	if (mesh != nullptr) {
		dmat4 auxMat = modelMat;
		uploadMvM(cam.getViewMat());
		glLineWidth(2);
		glColor3d(0.0, 0.0, 0.0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//rotation
		dmat4 matRotated = rotate(modelMat, radians(-25.0), dvec3(0.0, 0.0, 1.0));
		modelMat = auxMat * matRotated;
		uploadMvM(cam.getViewMat()); // envía a la GPU cam.getViewMat() * modelMat * matP1
		glColor3d(0.0, 0.0, 1.0);
		mesh->render();
		modelMat = auxMat;
	}
}
//-------------------------------------------------------------------------

void RectanguloRGB::update(){}
//-------------------------------------------------------------------------

void RectanguloRGB::update(GLuint){}
void RectanguloRGB::render(glm::dmat4 const & modelViewMat)
{
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

Estrella3D::Estrella3D(GLdouble er, GLdouble np, GLdouble h) : Entity()
{
	mesh = Mesh::generaEstrellaTexCor(er, np, h);
	texture.load("../Bmps/baldosaP.bmp");
	modelMat = translate(dmat4(1), glm::dvec3(100.0, 150.0, 0.0));
}
//-------------------------------------------------------------------------

Estrella3D::~Estrella3D()
{
	delete mesh; mesh = nullptr;
};
//-------------------------------------------------------------------------

void Estrella3D::render(Camera const& cam)
{
	if (mesh != nullptr) {
		dmat4 auxMat = modelMat;
		//rotation over Y and Z
		dmat4 matAnima1 = rotate(dmat4(1), radians(incrAngY), dvec3(0.0, 1.0, 0.0));
		dmat4 matAnima2 = rotate(dmat4(1), radians(incrAngZ), dvec3(0.0, 0.0, 1.0));
		modelMat = auxMat * matAnima1 * matAnima2;
		uploadMvM(cam.getViewMat());
		texture.bind();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mesh->render();
		//rotation of 180 to render the symmetric
		dmat4 r2 = rotate(dmat4(1), radians(180.0), dvec3(0.0, 1.0,0.0));
		modelMat *= r2;
		uploadMvM(cam.getViewMat()); // envía a la GPU cam.etViewMat() * modelMat * matP1
		mesh->render();
		modelMat = auxMat;
		texture.unbind();
	}
}
//-------------------------------------------------------------------------

void Estrella3D::update()
{
	incrAngY++;
	incrAngZ++;
}
void Estrella3D::render(glm::dmat4 const & modelViewMat)
{
}
void Estrella3D::update(GLuint a)
{
	incrAngY+= a/10;
	incrAngZ+= a/10;
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

Caja::Caja()
{
}

Caja::Caja(GLdouble l) : Entity()
{
	mesh = Mesh::generaContCubo(l);
	//modelMat = translate(dmat4(1), glm::dvec3(200.0, 0.0, 0.0));
	//texture.load("../Bmps/container.bmp");
	//texture_intern.load("../Bmps/baldosaF.bmp");
}
//-------------------------------------------------------------------------

Caja::~Caja()
{
	delete mesh; mesh = nullptr;
};
//-------------------------------------------------------------------------

void Caja::render(Camera const& cam)
{
	if (mesh != nullptr) {
		uploadMvM(cam.getViewMat());
		//glColor3d(0.0, 0.0, 0.0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mesh->render();
	}
}
void Caja::render(glm::dmat4 const & modelViewMat)
{
}
void Caja::update(){}
//-------------------------------------------------------------------------

void Caja::update(GLuint){}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

TrianguloAnimado::TrianguloAnimado(GLdouble r) : Entity()
{
	mesh = Mesh::generaTrianguloRGB(r, 0, 0);
	raggio_int = r;
	modelMat = translate(dmat4(1), glm::dvec3(0.0, 0.0, 100.0));
}
//-------------------------------------------------------------------------

TrianguloAnimado::~TrianguloAnimado()
{
	delete mesh; mesh = nullptr;
};
//-------------------------------------------------------------------------

void TrianguloAnimado::render(Camera const& cam)
{
	if (mesh != nullptr) {
		dmat4 auxMat = modelMat;
		//rotation on its center and translation on a circle of radius r_ext
		dmat4 matTranslate = translate(auxMat, dvec3(new_x,new_y,0));
		dmat4 matRotated = rotate(modelMat, radians((double)incrAng), dvec3(0.0, 0.0, 1.0));
		modelMat = auxMat * matTranslate * matRotated;
		uploadMvM(cam.getViewMat());
		glLineWidth(3);
		glColor3d(1.0, 0.0, 0.0);
		glPolygonMode(GL_BACK, GL_LINE);
		glPolygonMode(GL_BACK, GL_POINT);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mesh->render();
		modelMat = auxMat;
	}
}
void TrianguloAnimado::render(glm::dmat4 const & modelViewMat)
{
}
//-------------------------------------------------------------------------

void TrianguloAnimado::update()
{		
	incrAng += 1;
	incrExtAng += 5;
	//translation above a circle of radius r_ext in C=(centre_x,centre_y)
	new_x = centre_x + r_ext * cos(radians(incrExtAng));
	new_y = centre_y + r_ext * sin(radians(incrExtAng));
}
void TrianguloAnimado::update(GLuint a)
{
	incrAng += a/10;
	incrExtAng += a / 10;
	//translation above a circle of radius r_ext in C=(centre_x,centre_y)
	new_x = centre_x + r_ext * cos(radians(incrExtAng));
	new_y = centre_y + r_ext * sin(radians(incrExtAng));
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

Suelo::Suelo(GLdouble h, GLdouble w, GLuint rh, GLuint rw) : Entity()
{
	mesh = Mesh::generaRectanguloTexCor(h, w, rh, rw);
	texture.load("../Bmps/baldosaC.bmp");
}
//-------------------------------------------------------------------------

Suelo::~Suelo()
{
	delete mesh; mesh = nullptr;
};
//-------------------------------------------------------------------------

void Suelo::render(Camera const& cam)
{
	if (mesh != nullptr) {
		texture.bind();
		uploadMvM(cam.getViewMat());
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mesh->render();
		texture.unbind();
	}
}
void Suelo::render(glm::dmat4 const & modelViewMat)
{
}
//-------------------------------------------------------------------------

void Suelo::update(){}
//-------------------------------------------------------------------------

void Suelo::update(GLuint){}
//-------------------------------------------------------------------------

Foto::Foto(GLdouble h, GLdouble w)
{
	mesh = Mesh::generaFoto(h, w);
	modelMat = translate(dmat4(1), dvec3(-2*w, h, h));
	texture.loadColorBuffer();
}
//-------------------------------------------------------------------------

Foto::~Foto()
{
	delete mesh; mesh = nullptr;
}
//-------------------------------------------------------------------------

void Foto::render(Camera const & cam)
{
	if (mesh != nullptr) {
		texture.bind();
		uploadMvM(cam.getViewMat());
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mesh->render();
		texture.unbind();
	}
}
void Foto::render(glm::dmat4 const & modelViewMat)
{
}
//-------------------------------------------------------------------------

void Foto::update(){}
//-------------------------------------------------------------------------

void Foto::update(GLuint){}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

Tablero::Tablero(GLdouble l, int sx, int number_of)
{
	mesh = Mesh::generaContCubo(l);
	lado = l;
	side = sx;
	n = number_of;
	//dmat4 auxMat = modelMat;
	double lado_caja = 100.0;
	//dmat4 t1 = translate(dmat4(1), glm::dvec3(lado*scalex / 2, (lado_caja - (lado*scaley)) / 2, side * lado_caja / 2));
	//modelMat = translate(dmat4(1), glm::dvec3(0.0, -lado*scaley/2, 0.0));
	//std::cout<<lado*scaley << to_string(modelMat) << std::endl;
}
//-------------------------------------------------------------------------
Tablero::~Tablero() {
	delete mesh; mesh = nullptr;
}
//-------------------------------------------------------------------------

void Tablero::render(Camera const & cam)
{
	if (mesh != nullptr) {
		for (int i = 0; i < 360; i= i+ (int) (360/n)) {
			dmat4 aux = modelMat;
			double lado_caja = 100.0;
			double r = lado * scalex;
			dmat4 t1 = translate(dmat4(1), glm::dvec3(r * cos(radians(incrAng+i)) / 2, /*(lado_caja - (lado*scaley)) / 2*/(r / 2)*sin(radians(incrAng+i)), side * lado_caja / 2));
			dmat4 rot = rotate(dmat4(1), radians(incrAng+i), dvec3(0.0, 0.0, 1.0));
			dmat4 s1 = scale(dmat4(1), glm::dvec3(scalex, scaley, scalez));
			modelMat = aux * t1 * rot*s1;
			uploadMvM(cam.getViewMat());
			glColor3d(0.0, 0.0, 0.0);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			mesh->render();
			modelMat = aux;
		}
	}
}
void Tablero::render(glm::dmat4 const & modelViewMat)
{
	if (mesh != nullptr) {
		for (int i = 0; i < 360; i = i + (int)(360 / n)) {
			dmat4 aux = modelMat;
			double lado_caja = 100.0;
			double r = lado * scalex;
			dmat4 t1 = translate(dmat4(1), glm::dvec3(r * cos(radians(incrAng + i)) / 2, /*(lado_caja - (lado*scaley)) / 2*/(r / 2)*sin(radians(incrAng + i)), side * lado_caja / 2));
			dmat4 rot = rotate(dmat4(1), radians(incrAng + i), dvec3(0.0, 0.0, 1.0));
			dmat4 s1 = scale(dmat4(1), glm::dvec3(scalex, scaley, scalez));
			modelMat = aux * t1 * rot*s1;
			uploadMvM(modelViewMat);
			glColor3d(0.0, 0.0, 0.0);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			mesh->render();
			modelMat = aux;
		}
	}
}
//-------------------------------------------------------------------------

void Tablero::update()
{
	incrAng += 5;
}
//-------------------------------------------------------------------------

void Tablero::update(GLuint)
{
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

CajaTex::CajaTex(GLdouble l, int number_of)
{
	mesh = Mesh::generaCajaTexCor(l);
	lado = l;
	double scalax = 3.0;
	double scalay = 0.3;
	double lado_tablero = 100;
	n = number_of;
	//modelMat = translate(dmat4(1), glm::dvec3(lado_tablero*scalax, -(l/2 - lado_tablero*scalay/2), 0.0));
	texture.load("../Bmps/container.bmp");
	//texture_intern.load("../Bmps/baldosaF.bmp");
}

CajaTex::~CajaTex()
{
	delete mesh; mesh = nullptr;
}

void CajaTex::render(Camera const & cam)
{
	if (mesh != nullptr) {
		for (int i = 0; i < 360; i = i + (int) (360/n)) {
			dmat4 auxMat = modelMat;
			double scalax = 3.0;
			double lado_tablero = 100;
			double r = lado_tablero * scalax;
			double scalay = 0.3;
			dmat4 t1 = translate(dmat4(1), glm::dvec3(r*cos(radians(incrAng+i)), r*sin(radians(incrAng+i)), 0.0));
			//dmat4 rot = rotate(dmat4(1), radians(incrAng), dvec3(0.0, 0.0, 1.0));
			modelMat = auxMat * t1;
			uploadMvM(cam.getViewMat());
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			//glEnable(GL_CULL_FACE);
			//glCullFace(GL_BACK);
			texture.bind(/*GL_ADD*/);
			mesh->render();
			//glDisable(GL_CULL_FACE);
			texture.unbind();


			/*glEnable(GL_CULL_FACE);
			glCullFace(GL_FRONT);
			texture_intern.bind(GL_REPLACE);
			mesh->render();
			glDisable(GL_CULL_FACE);
			texture_intern.unbind();*/
			modelMat = auxMat;
		}
	}
}

void CajaTex::render(glm::dmat4 const & modelViewMat)
{
	if (mesh != nullptr) {
		for (int i = 0; i < 360; i = i + (int)(360 / n)) {
			dmat4 auxMat = modelMat;
			double scalax = 3.0;
			double lado_tablero = 100;
			double r = lado_tablero * scalax;
			double scalay = 0.3;
			dmat4 t1 = translate(dmat4(1), glm::dvec3(r*cos(radians(incrAng + i)), r*sin(radians(incrAng + i)), 0.0));
			//dmat4 rot = rotate(dmat4(1), radians(incrAng), dvec3(0.0, 0.0, 1.0));
			modelMat = auxMat * t1;
			uploadMvM(modelViewMat);
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			//glEnable(GL_CULL_FACE);
			//glCullFace(GL_BACK);
			texture.bind(/*GL_ADD*/);
			mesh->render();
			//glDisable(GL_CULL_FACE);
			texture.unbind();


			/*glEnable(GL_CULL_FACE);
			glCullFace(GL_FRONT);
			texture_intern.bind(GL_REPLACE);
			mesh->render();
			glDisable(GL_CULL_FACE);
			texture_intern.unbind();*/
			modelMat = auxMat;
		}
	}
}

void CajaTex::update()
{
	incrAng += 5;
}

void CajaTex::update(GLuint)
{
}

Rotor::Rotor(GLdouble baseRad, GLdouble topRad, GLdouble h, dvec3 color, bool giro)
{
	q = gluNewQuadric();
	baseR = baseRad;
	topR = topRad;
	height = h;
	mesh = Mesh::generaRectanguloRotor(h, baseRad*2);
	horario = giro;
	color_out = color;
}

Rotor::~Rotor()
{
	gluDeleteQuadric(q);
}

GLdouble Rotor::getR()
{
	return baseR;
}

GLdouble Rotor::getH()
{
	return height;
}

void Rotor::render(Camera const & cam)
{
	uploadMvM(cam.getViewMat());
	glColor3f(color_out[0],color_out[1],color_out[2]);
	gluQuadricDrawStyle(q, GLU_FILL);
	gluCylinder(q, baseR, topR, height, 20, 10);
	dmat4 auxMat = modelMat;
	glColor3f(0.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	modelMat = rotate(modelMat, radians(incrAng), dvec3(0.0, 0.0, 1.0));
	uploadMvM(cam.getViewMat());
	mesh->render();
	modelMat = auxMat;
}

void Rotor::render(glm::dmat4 const & modelViewMat)
{
	uploadMvM(modelViewMat);
	glColor3f(color_out[0], color_out[1], color_out[2]);
	gluQuadricDrawStyle(q, GLU_FILL);
	gluCylinder(q, baseR, topR, height, 20, 10);
	dmat4 auxMat = modelMat;
	glColor3f(0.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	modelMat = rotate(modelMat, radians(incrAng), dvec3(0.0, 0.0, 1.0));
	uploadMvM(modelViewMat);
	mesh->render();
	modelMat = auxMat;
}

void Rotor::update()
{
	if (horario)
		incrAng++;
	else
		incrAng--;
}

void Rotor::update(bool b) {
	if (b)
		incrAng++;
	else
		incrAng--;
}

void Rotor::update(GLuint)
{
	update();
}

Chasis::Chasis(GLdouble l, GLdouble h, GLdouble R)
{
	lado = l;
	height = h;
	mesh = Mesh::generaContCubo(l);
	dmat4 t = translate(modelMat, dvec3(0.0,R,0.0));
	dmat4 s = scale(modelMat, dvec3(1.0, h / l, 1.0));
	modelMat = t * s;
}

Chasis::~Chasis()
{
	mesh = nullptr;
}

GLdouble Chasis::getLado()
{return lado;
}

GLdouble Chasis::getHeight()
{
	return height;
}

void Chasis::render(Camera const &cam)
{
	 if (mesh != nullptr) {
		uploadMvM(cam.getViewMat());
		//glColor3d(0.0, 1.0, 0.0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mesh->render();
	}

}

void Chasis::render(glm::dmat4 const& modelViewMat)
{
	if (mesh != nullptr) {
		uploadMvM(modelViewMat);
		//glColor3d(0.0, 0.0, 1.0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mesh->render();
	}
}

void Chasis::update()
{
}

void Chasis::update(GLuint)
{

}

Drone::Drone(Chasis* c1, Rotor* d, GLdouble R)
{
	chasis = c1;
	dmat4 t0 = translate(dmat4(1), dvec3(0.0, R, 0.0));
	dmat4 rot = rotate(dmat4(1), radians(90.0), dvec3(1.0, 0.0, 0.0));
	//fondo sx
	dmat4 t1 = translate(dmat4(1), dvec3(-c1->getLado()/2, c1->getHeight(),c1->getLado()/2));
	d1 = new Rotor(d->getR(), d->getR(), d->getH(), dvec3(0.0, 1.0, 0.0), true);
	d1->setModelMat(t0*t1*rot);
	//fondo dx
	dmat4 t2 = translate(dmat4(1), dvec3(-c1->getLado() / 2, c1->getHeight(), -c1->getLado() / 2));
	d2 = new Rotor(d->getR(), d->getR(), d->getH(), dvec3(0.0, 1.0, 0.0), false);
	d2->setModelMat(t0*t2*rot);
	//front sx
	dmat4 t3 = translate(dmat4(1), dvec3(c1->getLado() / 2, c1->getHeight(), c1->getLado() / 2));
	d3 = new Rotor(d->getR(), d->getR(), d->getH(), dvec3(1.0, 0.0, 0.0),false);
	d3->setModelMat(t0*t3*rot);
	//front dx
	dmat4 t4 = translate(dmat4(1), dvec3(c1->getLado() / 2, c1->getHeight(), -c1->getLado() / 2));
	d4 = new Rotor(d->getR(), d->getR(), d->getH(), dvec3(1.0, 0.0, 0.0), true);
	d4->setModelMat(t0*t4*rot);
}

Drone::~Drone()
{
}

void Drone::render(Camera const & cam)
{
	glColor3f(1.0, 0.0, 1.0);
	chasis->render(cam);
	d1->render(cam);
	d2->render(cam);
	d3->render(cam);
	d4->render(cam);
}

void Drone::render(glm::dmat4 const & modelViewMat)
{
	glColor3f(1.0, 0.0, 1.0);
	chasis->render(modelViewMat);
	glColor3f(0.0, 1.0, 0.0);
	d1->render(modelViewMat);
	glColor3f(0.0, 1.0, 0.0);
	d2->render(modelViewMat);
	glColor3f(1.0, 0.0, 0.0);
	d3->render(modelViewMat);
	glColor3f(1.0, 0.0, 0.0);
	d4->render(modelViewMat);
}

void Drone::update()
{
	d1->update();
	d2->update();
	d3->update();
	d4->update();
}

void Drone::update(GLuint u)
{
	d1->update(u);
	d2->update(u);
	d3->update(u);
	d4->update(u);
}

void Drone::move(bool)
{
	/*//chasis
	dmat4 auxMat = modelMat;
	dmat4 t1 = translate(dmat4(1), glm::dvec3(r*cos(radians(incrAng + i)), r*sin(radians(incrAng + i)), 0.0));
	dmat4 rot = rotate(dmat4(1), radians(incrAng), dvec3(0.0, 0.0, 1.0));
	//rotor*/
}

Esfera::Esfera(GLdouble r)
{
	radius = r;
	q = gluNewQuadric();
}

Esfera::Esfera(GLdouble r, int m, int n)
{
	radius = r;
	GLdouble x = 0;
	GLdouble y = -r;
	GLdouble incr = 180.0 / (m);
	GLdouble ang = -90.0;
	dvec3* perfil = new dvec3[m];
	for (int i = 0; i < m - 1; i++) {
		perfil[i] = dvec3(x, y, 0.0);
		ang = ang + incr;
		x = r * cos(radians(ang));
		y = r * sin(radians(ang));

	}
	perfil[m - 1] = dvec3(0, r, 0.0);
	this->mesh = new MBR(m, n, perfil);
}

Esfera::~Esfera()
{
	gluDeleteQuadric(q);
}



void Esfera::render(Camera const & cam)
{
	uploadMvM(cam.getViewMat());
	glPushMatrix();
	glColor3f(0.0, 0.0, 1.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	gluQuadricDrawStyle(q, GLU_LINE);
	gluSphere(q, radius, 50, 50);
	glPopMatrix();
}

void Esfera::render(glm::dmat4 const & modelViewMat)
{
	if (mesh != nullptr) {
		uploadMvM(modelViewMat);
		glColor3f(0.0, 0.0, 1.0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		mesh->render();
	}
	/*glPushMatrix();
	glColor3f(0.0, 0.0, 1.0);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	gluQuadricDrawStyle(q, GLU_LINE);
	gluSphere(q, radius, 50, 50);
	glPopMatrix();*/
}

void Esfera::update()
{
}

void Esfera::update(GLuint)
{
}
