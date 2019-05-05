//#pragma once
#ifndef _H_Camera_H_
#define _H_Camera_H_

#include <GL/freeglut.h>
#include <gtc/matrix_access.hpp>
#include <glm.hpp>

#include "Viewport.h"
//-------------------------------------------------------------------------

class Camera {
public:
	Camera(Viewport* avp) : vp(avp), viewMat(1.0), projMat(1.0),
							xRight(avp->getW() / 2.0), xLeft(-xRight), 
							yTop(avp->getH() / 2.0), yBot(-yTop) { };
	~Camera() {};
	Viewport* getVP() { return vp; }

	// view matrix (the inverse of modeling matrix)
	glm::dmat4 const& getViewMat() const { return viewMat; };
	void uploadVM() const; // transfers viewMat to the GPU

	void set2D();  // eye(0,0,500), look(0,0,0), up(0, 1, 0)
	void set3D();  // eye(500,500,500), look(0,10,0), up(0, 1, 0)
    
	void pitch(GLdouble a); // rotates a degrees on the X axis
	void yaw(GLdouble a);   // rotates a degrees on the Y axis
	void roll(GLdouble a);  // rotates a degrees on the Z axis

	// projection matrix
	glm::dmat4 const& getProjMat() const { return projMat; };
	void uploadPM() const;  // transfers projMat to the GPU

	// set scene visible area size and transfers projMat to the GPU
	void uploadSize(GLdouble aw, GLdouble ah); 

	// update scale factor and transfers projMat to GPU
	void uploadScale(GLdouble s); 

	void setCenital();
	void moveLR(GLdouble cs);
	void moveFB(GLdouble cs);
	void moveUD(GLdouble cs);
	void lookLR(GLdouble cs);
	void lookUD(GLdouble cs);

	void orbit(GLdouble ax);
	void orbit(GLdouble ax, GLdouble ay);

	
protected:
	
	glm::dmat4 viewMat;    // view matrix = inverse of modeling matrix
	
	glm::dmat4 projMat;     // projection matrix
	
	GLdouble xRight, xLeft, yTop, yBot;    // size of scene visible area
	GLdouble nearVal = 500, farVal = 10000;  // view volume
	GLdouble factScale = 1;

	glm::dvec3 eye = { 1000.0, 1000.0, 1000.0 };
	glm::dvec3 look = { 0.0, 0.0, 0.0 };
	glm::dvec3 up = { 0.0, 1.0, 0.0 };
	glm::dvec3 front = { 0.0, 0.0, -1.0 };
	glm::dvec3 u = { 1.0, 0.0, 0.0 };
	glm::dvec3 v = { 0.0, 1.0, 0.0 };
	glm::dvec3 n = { 0.0, 0.0, 1.0 };


	GLdouble radio = 1000.0, ang = 0.0;
	bool orto = true;
	
	Viewport* vp;
	void setAxes();
	void setVM();
	void uploadPM();
};

//-------------------------------------------------------------------------

#endif //_H_Camera_H_