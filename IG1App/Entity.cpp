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
	//q = gluNewQuadric();
	//baseR = baseRad;
	//topR = topRad;
	//height = h;
	//mesh = Mesh::generaRectanguloRotor(h, baseRad*2);
	grObjects.push_back(new Cilindro(baseRad, topRad, h, color));
	grObjects.push_back(new Rectangulo(h, baseRad * 2));
	horario = giro;
	//color_out = color;
}

Rotor::~Rotor()
{
	//gluDeleteQuadric(q);
	for (Entity* el : grObjects)
	{
		delete el;  el = nullptr;
	}
}

GLdouble Rotor::getR()
{
	return ((Cilindro*) getEntity(0))->getR();
}

GLdouble Rotor::getH()
{
	return ((Cilindro*) getEntity(0))->getH();
}

void Rotor::render(Camera const & cam)
{
	/*uploadMvM(cam.getViewMat());
	glColor3f(color_out[0],color_out[1],color_out[2]);
	gluQuadricDrawStyle(q, GLU_FILL);
	gluCylinder(q, baseR, topR, height, 20, 10);
	dmat4 auxMat = modelMat;
	glColor3f(0.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	modelMat = rotate(modelMat, radians(incrAng), dvec3(0.0, 0.0, 1.0));
	uploadMvM(cam.getViewMat());
	mesh->render();
	modelMat = auxMat;*/
}

/*void Rotor::render(glm::dmat4 const & modelViewMat)
{
	/*uploadMvM(modelViewMat);
	glColor3f(color_out[0], color_out[1], color_out[2]);
	gluQuadricDrawStyle(q, GLU_FILL);
	dmat4 auxMat = modelMat;
	glColor3f(0.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	modelMat = rotate(modelMat, radians(incrAng), dvec3(0.0, 0.0, 1.0));
	uploadMvM(modelViewMat);
	mesh->render();
	modelMat = auxMat;
}*/

void Rotor::update()
{
	if (horario)
		((Rectangulo*)getEntity(1))->incrementAng();
	else
		((Rectangulo*)getEntity(1))->decrementAng();
}

void Rotor::update(bool b) {
	if (b)
		((Rectangulo*)getEntity(1))->incrementAng();
	else
		((Rectangulo*)getEntity(1))->decrementAng();
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
	//dmat4 t = translate(modelMat, dvec3(0.0,R+10,0.0));
	//modelMat = t;
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
		dmat4 auxMat = modelMat;
		dmat4 s = scale(dmat4(1), dvec3(1.0, height / lado, 1.0));
		modelMat = auxMat * s;
		uploadMvM(modelViewMat);
		glColor3d(0.0, 0.0, 1.0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		mesh->render();
		modelMat = auxMat;
	}
}

void Chasis::update()
{
}

void Chasis::update(GLuint)
{

}

glm::dvec3 Chasis::getLeftTopCorner()
{
	dvec3 v = mesh->getVertices()[0];
	v[1] = v[1] * height / lado;
	return v;
}

glm::dvec3 Chasis::getLeftBottomCorner()
{
	dvec3 v = mesh->getVertices()[2];
	v[1] = v[1] * height / lado;
	return v;
}

glm::dvec3 Chasis::getRightTopCorner()
{
	dvec3 v = mesh->getVertices()[4];
	v[1] = v[1] * height / lado;
	return v;
}

glm::dvec3 Chasis::getRightBottomCorner()
{
	dvec3 v = mesh->getVertices()[6];
	v[1] = v[1] * height / lado;
	return v;
}


CompoundEntity::~CompoundEntity()
{
	for (Entity* it : grObjects) delete it;
}

Entity * CompoundEntity::getEntity(int i)
{
	return grObjects.at(i);
}

void CompoundEntity::render(glm::dmat4 const& modelViewMat)
{
	glMatrixMode(GL_MODELVIEW);
	glm::dmat4 aMat = modelViewMat * modelMat;
	glLoadMatrixd(glm::value_ptr(aMat));
	for (Entity* it : grObjects) {
		it->render(aMat);
	}
}

void CompoundEntity::render(Camera const & cam)
{
}

void CompoundEntity::update()
{
	for (Entity* it : grObjects) {
		it->update();
	}
}

void CompoundEntity::update(GLuint a)
{
	for (Entity* it : grObjects) {
		it->update(a);
	}
}

void CompoundEntity::setModelMat(glm::dmat4 aMat)
{
	modelMat = aMat;
}

glm::dmat4 CompoundEntity::getModelMat()
{
	return modelMat;
}

Drone::Drone(Chasis* chasis, Rotor* d, GLdouble R)
{
	grObjects.push_back(chasis);
	separation = R + 10;
	//dmat4 t0 = translate(dmat4(1), dvec3(0.0, separation, 0.0));
	//dmat4 rot = rotate(dmat4(1), radians(90.0), dvec3(1.0, 0.0, 0.0));
	//fondo sx
	//dmat4 t1 = translate(dmat4(1), dvec3(-c1->getLado()/2, c1->getHeight(),c1->getLado()/2));
	grObjects.push_back(new Rotor(d->getR(), d->getR(), d->getH(), dvec3(0.0, 1.0, 0.0), true));
	//d1->setModelMat(/*t1*rot*/);
	//fondo dx
	//dmat4 t2 = translate(dmat4(1), dvec3(-c1->getLado() / 2, c1->getHeight(), -c1->getLado() / 2));
	grObjects.push_back(new Rotor(d->getR(), d->getR(), d->getH(), dvec3(0.0, 1.0, 0.0), false));
	//d2->setModelMat(t2);
	//front sx
	//dmat4 t3 = translate(dmat4(1), dvec3(c1->getLado() / 2, c1->getHeight(), c1->getLado() / 2));
	grObjects.push_back(new Rotor(d->getR(), d->getR(), d->getH(), dvec3(1.0, 0.0, 0.0), true));
	//d3->setModelMat(t3);
	//front dx
	//dmat4 t4 = translate(dmat4(1), dvec3(c1->getLado() / 2, c1->getHeight(), -c1->getLado() / 2));
	grObjects.push_back(new Rotor(d->getR(), d->getR(), d->getH(), dvec3(1.0, 0.0, 0.0), false));
	//d4->setModelMat(t4);
	Rotor* d1 = (Rotor*)getEntity(1);
	Rotor* d2 = (Rotor*)getEntity(2);
	Rotor* d3 = (Rotor*)getEntity(3);
	Rotor* d4 = (Rotor*)getEntity(4);
	dmat4 auxMatChasis = chasis->getModelMat();
	dmat4 auxMatDrone1 = d1->getModelMat();
	dmat4 auxMatDrone2 = d2->getModelMat();
	dmat4 auxMatDrone3 = d3->getModelMat();
	dmat4 auxMatDrone4 = d4->getModelMat();
	//rotate drone
	//rotate chasis

	dmat4 r1 = rotate(dmat4(1), radians(incrAng), dvec3(cos(radians(radiant - 90.0)), 0.0, sin(radians(radiant - 90.0))));
	//rotate rotors

	//translate chasis
	dmat4 t1 = translate(dmat4(1), glm::dvec3(separation*sin(radians(incrAng))*cos(radians(radiant)),
		separation*cos(radians(incrAng)), separation*sin(radians(incrAng))*sin(radians(radiant))));
	
	chasis->setModelMat(auxMatChasis*t1*r1);
	//translate drone
	dmat4 rot = rotate(dmat4(1), radians(90.0), dvec3(1.0, 0.0, 0.0));

	dvec3 leftBottom = chasis->getLeftBottomCorner();
	leftBottom[1] += d1->getH() + 1.0;
	dmat4 t01 = translate(chasis->getModelMat(), leftBottom);
	d1->setModelMat(auxMatDrone1*t01*rot);
	dvec3 leftTop = chasis->getLeftTopCorner();
	leftTop[1] += d2->getH() + 1.0;
	dmat4 t02 = translate(chasis->getModelMat(), leftTop);
	d2->setModelMat(auxMatDrone2*t02*rot);
	dvec3 rightBottom = chasis->getRightBottomCorner();
	rightBottom[1] += d3->getH() + 1.0;
	dmat4 t03 = translate(chasis->getModelMat(), rightBottom);
	d3->setModelMat(auxMatDrone3*t03*rot);
	dvec3 rightTop = chasis->getRightTopCorner();
	rightTop[1] += d4->getH() + 1.0;
	dmat4 t04 = translate(chasis->getModelMat(), rightTop);
	d4->setModelMat(auxMatDrone4*t04*rot);
}


/*void Drone::render(Camera const & cam)
{
	/*glColor3f(1.0, 0.0, 1.0);
	chasis->render(cam);
	d1->render(cam);
	d2->render(cam);
	d3->render(cam);
	d4->render(cam);
}*/





/*void Drone::render(glm::dmat4 const & modelViewMat)
{
	dmat4 auxMatChasis = chasis->getModelMat();
	dmat4 auxMatDrone1 = d1->getModelMat();
	dmat4 auxMatDrone2 = d2->getModelMat();
	dmat4 auxMatDrone3 = d3->getModelMat();
	dmat4 auxMatDrone4 = d4->getModelMat();
	//rotate drone
	//rotate chasis

	dmat4 r1 = rotate(dmat4(1), radians(incrAng), dvec3(cos(radians(radiant-90.0)), 0.0, sin(radians(radiant-90.0))));
	//rotate rotors

	//translate chasis
	dmat4 t1 = translate(dmat4(1), glm::dvec3(separation*sin(radians(incrAng))*cos(radians(radiant)), 
		separation*cos(radians(incrAng)), separation*sin(radians(incrAng))*sin(radians(radiant))));
	//dmat4 r1 = rotate(dmat4(1), radians(incrAng), dvec3(1.0, 0.0, 1.0));
	chasis->setModelMat(auxMatChasis*t1*r1);
	//translate drone
	dmat4 rot = rotate(dmat4(1), radians(90.0), dvec3(1.0, 0.0, 0.0));

	dvec3 leftBottom = chasis->getLeftBottomCorner();
	leftBottom[1] += d1->getH()+1.0;
	dmat4 t01 = translate(chasis->getModelMat(), leftBottom);
	d1->setModelMat(auxMatDrone1*t01*rot);
	dvec3 leftTop = chasis->getLeftTopCorner();
	leftTop[1] += d2->getH() + 1.0;
	dmat4 t02 = translate(chasis->getModelMat(), leftTop);
	d2->setModelMat(auxMatDrone2*t02*rot);
	dvec3 rightBottom = chasis->getRightBottomCorner();
	rightBottom[1] += d3->getH() + 1.0;
	dmat4 t03 = translate(chasis->getModelMat(), rightBottom);
	d3->setModelMat(auxMatDrone3*t03*rot);
	dvec3 rightTop = chasis->getRightTopCorner();
	rightTop[1] += d4->getH() + 1.0;
	dmat4 t04 = translate(chasis->getModelMat(), rightTop);
	d4->setModelMat(auxMatDrone4*t04*rot);

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
	chasis->setModelMat(auxMatChasis);
	d1->setModelMat(auxMatDrone1);
	d2->setModelMat(auxMatDrone2);
	d3->setModelMat(auxMatDrone3);
	d4->setModelMat(auxMatDrone4);
}*/

void Drone::update()
{
	Chasis* chasis = (Chasis*)getEntity(0);
	Rotor* d1 = (Rotor*)getEntity(1);
	Rotor* d2 = (Rotor*)getEntity(2);
	Rotor* d3 = (Rotor*)getEntity(3);
	Rotor* d4 = (Rotor*)getEntity(4);
	d1->update();
	d2->update();
	d3->update();
	d4->update();
	
	dmat4 r1 = rotate(dmat4(1), radians(incrAng), dvec3(cos(radians(radiant - 90.0)), 0.0, sin(radians(radiant - 90.0))));
	//rotate rotors

	//translate chasis
	dmat4 t1 = translate(dmat4(1), glm::dvec3(separation*sin(radians(incrAng))*cos(radians(radiant)),
		separation*cos(radians(incrAng)), separation*sin(radians(incrAng))*sin(radians(radiant))));

	dmat4 auxMatChasis = dmat4(1);
	dmat4 auxMatDrone1 = dmat4(1);
	dmat4 auxMatDrone2 = dmat4(1);
	dmat4 auxMatDrone3 = dmat4(1);
	dmat4 auxMatDrone4 = dmat4(1);
	chasis->setModelMat(auxMatChasis*t1*r1);
	//translate drone
	dmat4 rot = rotate(dmat4(1), radians(90.0), dvec3(1.0, 0.0, 0.0));

	dvec3 leftBottom = chasis->getLeftBottomCorner();
	leftBottom[1] += d1->getH() + 1.0;
	dmat4 t01 = translate(chasis->getModelMat(), leftBottom);
	d1->setModelMat(auxMatDrone1*t01*rot);
	dvec3 leftTop = chasis->getLeftTopCorner();
	leftTop[1] += d2->getH() + 1.0;
	dmat4 t02 = translate(chasis->getModelMat(), leftTop);
	d2->setModelMat(auxMatDrone2*t02*rot);
	dvec3 rightBottom = chasis->getRightBottomCorner();
	rightBottom[1] += d3->getH() + 1.0;
	dmat4 t03 = translate(chasis->getModelMat(), rightBottom);
	d3->setModelMat(auxMatDrone3*t03*rot);
	dvec3 rightTop = chasis->getRightTopCorner();
	rightTop[1] += d4->getH() + 1.0;
	dmat4 t04 = translate(chasis->getModelMat(), rightTop);
	d4->setModelMat(auxMatDrone4*t04*rot);
}

void Drone::update(GLuint u)
{
	Chasis* chasis = (Chasis*)getEntity(0);
	Rotor* d1 = (Rotor*)getEntity(1);
	Rotor* d2 = (Rotor*)getEntity(2);
	Rotor* d3 = (Rotor*)getEntity(3);
	Rotor* d4 = (Rotor*)getEntity(4);
	d1->update(u);
	d2->update(u);
	d3->update(u);
	d4->update(u);

	dmat4 r1 = rotate(dmat4(1), radians(incrAng), dvec3(cos(radians(radiant - 90.0)), 0.0, sin(radians(radiant - 90.0))));
	//rotate rotors

	//translate chasis
	dmat4 t1 = translate(dmat4(1), glm::dvec3(separation*sin(radians(incrAng))*cos(radians(radiant)),
		separation*cos(radians(incrAng)), separation*sin(radians(incrAng))*sin(radians(radiant))));

	dmat4 auxMatChasis = dmat4(1);
	dmat4 auxMatDrone1 = dmat4(1);
	dmat4 auxMatDrone2 = dmat4(1);
	dmat4 auxMatDrone3 = dmat4(1);
	dmat4 auxMatDrone4 = dmat4(1);
	chasis->setModelMat(auxMatChasis*t1*r1);
	//translate drone
	dmat4 rot = rotate(dmat4(1), radians(90.0), dvec3(1.0, 0.0, 0.0));

	dvec3 leftBottom = chasis->getLeftBottomCorner();
	leftBottom[1] += d1->getH() + 1.0;
	dmat4 t01 = translate(chasis->getModelMat(), leftBottom);
	d1->setModelMat(auxMatDrone1*t01*rot);
	dvec3 leftTop = chasis->getLeftTopCorner();
	leftTop[1] += d2->getH() + 1.0;
	dmat4 t02 = translate(chasis->getModelMat(), leftTop);
	d2->setModelMat(auxMatDrone2*t02*rot);
	dvec3 rightBottom = chasis->getRightBottomCorner();
	rightBottom[1] += d3->getH() + 1.0;
	dmat4 t03 = translate(chasis->getModelMat(), rightBottom);
	d3->setModelMat(auxMatDrone3*t03*rot);
	dvec3 rightTop = chasis->getRightTopCorner();
	rightTop[1] += d4->getH() + 1.0;
	dmat4 t04 = translate(chasis->getModelMat(), rightTop);
	d4->setModelMat(auxMatDrone4*t04*rot);
}

void Drone::move(bool up)
{
	/*//chasis
	dmat4 auxMat = modelMat;
	dmat4 t1 = translate(dmat4(1), glm::dvec3(r*cos(radians(incrAng + i)), r*sin(radians(incrAng + i)), 0.0));
	dmat4 rot = rotate(dmat4(1), radians(incrAng), dvec3(0.0, 0.0, 1.0));
	//rotor*/
	if (up) {
		incrAng += 5;
	}
	else {
		incrAng -= 5;
	}
}

void Drone::moveRight(bool right)
{
	if (right) {
		radiant -= 5;
	}
	else {
		radiant += 5;
	}
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

/*Esfera::~Esfera()
{
	gluDeleteQuadric(q);
}*/



void Esfera::render(Camera const & cam)
{
	uploadMvM(cam.getViewMat());
	glPushMatrix();
	glColor3f(0.8, 0.4, 0.2);
	glRotatef(90.0, 1.0, 0.0, 0.0);
	gluQuadricDrawStyle(q, GLU_LINE);
	gluSphere(q, radius, 50, 50);
	glPopMatrix();
}

void Esfera::render(glm::dmat4 const & modelViewMat)
{
	if (mesh != nullptr) {
		uploadMvM(modelViewMat);
		//GLfloat luz[] = { 0.5, 0.5, 0.5, 1.0 };
		//glEnable(GL_COLOR_MATERIAL);
		glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);
		//glLightfv(GL_LIGHT0, GL_AMBIENT, luz);
		glColor3f(0.8, 0.4, 0.2);
		//glDisable(GL_LIGHT0);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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

Rectangulo::Rectangulo(GLdouble h, GLdouble w)
{
	width = w;
	height = h;
	mesh = Mesh::generaRectanguloRotor(h, w);
}

Rectangulo::~Rectangulo()
{
	delete mesh; mesh = nullptr;
}

void Rectangulo::render(glm::dmat4 const & modelViewMat)
{
	dmat4 auxMat = modelMat;
	glColor3f(0.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	modelMat = rotate(modelMat, radians(incrAng), dvec3(0.0, 0.0, 1.0));
	uploadMvM(modelViewMat);
	mesh->render();
	modelMat = auxMat;
}

void Rectangulo::render(Camera const & cam)
{
}

void Rectangulo::update()
{
}

void Rectangulo::update(GLuint)
{
}

void Rectangulo::incrementAng()
{
	incrAng++;
}

void Rectangulo::decrementAng()
{
	incrAng--;
}

Cilindro::Cilindro(GLdouble tr, GLdouble br, GLdouble h, glm::dvec3 color)
{
	q = gluNewQuadric();
	baseR = br;
	topR = tr;
	height = h;
	color_out = color;
}

GLdouble Cilindro::getR()
{
	return baseR;
}

GLdouble Cilindro::getH()
{
	return height;
}

void Cilindro::render(glm::dmat4 const & modelViewMat)
{
	uploadMvM(modelViewMat);
	glColor3f(color_out[0], color_out[1], color_out[2]);
	gluQuadricDrawStyle(q, GLU_FILL);
	gluCylinder(q, baseR, topR, height, 20, 10);
}

void Cilindro::render(Camera const & cam)
{
}

void Cilindro::update()
{
}

void Cilindro::update(GLuint)
{
}

QuadricEntity::QuadricEntity()
{
	q = gluNewQuadric();
}

QuadricEntity::~QuadricEntity()
{
	gluDeleteQuadric(q);
}

SuperDrone::SuperDrone(Chasis * c0, Chasis * c1, Rotor * r0, Rotor * r)
{
	grObjects.push_back(new Drone(c0, r0, 0.0));
	dvec3 t1 = c0->getLeftBottomCorner();
	//rotor height
	GLdouble offset = 5.0;
	t1[1] += 4.0 + 2.0 + offset;
	Drone* d1 = new Drone(c1, r, 0.0);
	d1->setModelMat(translate(dmat4(1), t1));
	grObjects.push_back(d1);
	Chasis* c2 = new Chasis(c1->getLado(), c1->getHeight(), 0.0);
	dvec3 t2 = c0->getLeftTopCorner();
	t2[1] += 4.0 + 2.0 + offset;
	Drone* d2 = new Drone(c2, r, 0.0);
	d2->setModelMat(translate(dmat4(1), t2));
	grObjects.push_back(d2);
	Chasis* c3 = new Chasis(c1->getLado(), c1->getHeight(), 0.0);
	dvec3 t3 = c0->getRightTopCorner();
	t3[1] += 4.0 + 2.0 + offset;
	Drone* d3 = new Drone(c3, r, 0.0);
	d3->setModelMat(translate(dmat4(1), t3));
	grObjects.push_back(d3);
	Chasis* c4 = new Chasis(c1->getLado(), c1->getHeight(), 0.0);
	dvec3 t4 = c0->getRightBottomCorner();
	t4[1] += 4.0 + 2.0 + offset;
	Drone* d4 = new Drone(c4, r, 0.0);
	d4->setModelMat(translate(dmat4(1), t4));
	grObjects.push_back(d4);
}
