//#pragma once
#ifndef _H_Entities_H_
#define _H_Entities_H_

#include <GL/freeglut.h>
#include <glm.hpp>

#include "Camera.h"
#include "Mesh.h"
#include "Texture.h"

//-------------------------------------------------------------------------

class Entity 
{
public:
	Entity() : modelMat(1.0) { }; 
	virtual ~Entity() { };

	virtual void render(Camera const& cam) = 0;
	virtual void render(glm::dmat4 const & modelViewMat) = 0;
	virtual void update() = 0;
	virtual void update(GLuint) = 0;

	// modeling matrix
	glm::dmat4 const& getModelMat() const { return modelMat; };

	void setModelMat(glm::dmat4 const& aMat) { modelMat = aMat; }
  
protected:

	Mesh* mesh = nullptr;   // surface mesh
	glm::dmat4 modelMat;    // modeling matrix
	double incrAng = 0;		 // angle incremental for updates
	Texture texture;		// texture variable

	// transfers modelViewMat to the GPU
	virtual void uploadMvM(glm::dmat4 const& modelViewMat) const;
};
//-------------------------------------------------------------------------

class EjesRGB : public Entity 
{
public:
	EjesRGB(GLdouble l);
	~EjesRGB();
	virtual void render(Camera const& cam); 
	virtual void update();
	virtual void update(GLuint);
	virtual void render(glm::dmat4 const & modelViewMat);
};
//-------------------------------------------------------------------------

class Poliespiral : public Entity
{
public:
	Poliespiral(glm::dvec2 verIni,
		GLdouble angIni,
		GLdouble incrAng,
		GLdouble ladoIni,
		GLdouble incrLado,
		GLuint numVert);
	~Poliespiral();
	virtual void render(Camera const& cam);
	virtual void update();
	virtual void update(GLuint);
	virtual void render(glm::dmat4 const & modelViewMat);
};
//-------------------------------------------------------------------------

class Dragon : public Entity
{
public:
	Dragon(GLuint numVert);
	~Dragon();
	virtual void render(Camera const& cam);
	virtual void update();
	virtual void update(GLuint);
	virtual void render(glm::dmat4 const & modelViewMat);
};
//-------------------------------------------------------------------------

class TrianguloRGB : public Entity
{
public:
	TrianguloRGB(GLdouble r);
	~TrianguloRGB();
	virtual void render(Camera const& cam);
	virtual void update();
	virtual void render(glm::dmat4 const & modelViewMat);
};
//-------------------------------------------------------------------------
class RectanguloRGB : public Entity
{
public:
	RectanguloRGB(GLdouble h, GLdouble w);
	~RectanguloRGB();
	virtual void render(Camera const& cam);
	virtual void update();
	virtual void update(GLuint);
	virtual void render(glm::dmat4 const & modelViewMat);
};
//-------------------------------------------------------------------------

class Estrella3D : public Entity
{
public:
	Estrella3D(GLdouble re, GLdouble np, GLdouble h);
	~Estrella3D();
	virtual void render(Camera const& cam);
	virtual void update();
	virtual void render(glm::dmat4 const & modelViewMat);
	virtual void update(GLuint);
protected:
	Mesh * mesh2 = nullptr;
	double incrAngY = 0;
	double incrAngZ = 0;
};
//-------------------------------------------------------------------------

class Caja : public Entity
{
public:
	Caja();
	Caja(GLdouble);
	~Caja();
	virtual void render(Camera const& cam);
	virtual void render(glm::dmat4 const & modelViewMat);
	virtual void update();
	virtual void update(GLuint);
protected:
	double lado;
	int n;
}; 
//-------------------------------------------------------------------------

class CajaTex : public Caja
{
public:
	CajaTex(GLdouble, int number_of = 12);
	~CajaTex();
	virtual void render(Camera const& cam);
	virtual void render(glm::dmat4 const & modelViewMat);
	virtual void update();
	virtual void update(GLuint);
protected:
	Texture texture_intern;
};
//-------------------------------------------------------------------------

class Tablero : public Caja
{
public:
	Tablero(GLdouble, int side = 1, int number_of = 12);
	~Tablero();
	virtual void render(Camera const& cam);
	virtual void render(glm::dmat4 const & modelViewMat);
	virtual void update();
	virtual void update(GLuint);
protected:
	double const scalex = 3.0;
	double const scaley = 0.3;
	double const scalez = 0.01;
	int side;
};
//-------------------------------------------------------------------------*/

class TrianguloAnimado : public Entity
{
public:
	TrianguloAnimado(GLdouble);
	~TrianguloAnimado();
	virtual void render(Camera const& cam);
	virtual void render(glm::dmat4 const & modelViewMat);
	virtual void update();
	virtual void update(GLuint);
protected:
	double incrExtAng = 0;
	double raggio_int = 0;
	double const r_ext = 300;
	double new_x= 0, new_y = 0;
	double const centre_x=0, centre_y=0;
};
//-------------------------------------------------------------------------

class Suelo : public Entity
{
public:
	Suelo(GLdouble h, GLdouble w,GLuint rh, GLuint rw);
	~Suelo();
	virtual void render(Camera const& cam);
	virtual void render(glm::dmat4 const & modelViewMat);
	virtual void update();
	virtual void update(GLuint);
};
//-------------------------------------------------------------------------

class Foto : public Entity
{
public:
	Foto(GLdouble h, GLdouble w);
	~Foto();
	virtual void render(Camera const& cam);
	virtual void render(glm::dmat4 const & modelViewMat);
	virtual void update();
	virtual void update(GLuint);
};
//-------------------------------------------------------------------------
class Rotor : public Entity
{
public:
	Rotor(GLdouble baseR, GLdouble topR, GLdouble h, glm::dvec3 color, bool giro=true);
	~Rotor();
	GLdouble getR();
	GLdouble getH();
	virtual void render(Camera const& cam);
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update();
	void update(bool b);
	virtual void update(GLuint);
protected:
	GLUquadricObj* q;
	GLdouble baseR, topR, height;
	bool horario;
	glm::dvec3 color_out;
};
//-------------------------------------------------------------------------
class Chasis : public Entity
{
public:
	Chasis(GLdouble l, GLdouble h, GLdouble R);
	~Chasis();
	GLdouble getLado();
	GLdouble getHeight();
	virtual void render(Camera const& cam);
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update();
	virtual void update(GLuint);
protected:
	GLdouble lado, height;
};
//-------------------------------------------------------------------------
class Drone : public Entity
{
public:
	Drone(Chasis* c, Rotor* d, GLdouble);
	~Drone();
	virtual void render(Camera const& cam);
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update();
	virtual void update(GLuint);
	void move(bool);
protected:
	Chasis* chasis;
	Rotor* d1,* d2,* d3, *d4;
};
//-------------------------------------------------------------------------
class Esfera : public Entity
{
public:
	Esfera(GLdouble r);
	Esfera(GLdouble r, int m, int n);
	~Esfera();
	virtual void render(Camera const& cam);
	virtual void render(glm::dmat4 const& modelViewMat);
	virtual void update();
	virtual void update(GLuint);
protected:
	GLUquadricObj* q;
	GLdouble radius, m, n;
};
//-------------------------------------------------------------------------

#endif //_H_Entities_H_