//#pragma once
#ifndef _H_Element_H_
#define _H_Element_H_

#include <GL/freeglut.h>
#include <glm.hpp>
#include "Entity.h"

//-------------------------------------------------------------------------

class GrElement
{
public:
	GrElement() : modelMat(1.0) {};
	GrElement(Entity * ent = nullptr) : modelMat(1.0) { entity = ent; };
	virtual ~GrElement() { delete entity; };

	virtual void render(glm::dmat4 const& modelViewMat);

protected:
	Entity * entity = nullptr;
	glm::dmat4 modelMat;

	virtual void setMvM(glm::dmat4 const& modelViewMat);
};

//-------------------------------------------------------------------------

#endif //_H_Element_H_