#pragma once
#include <vector>
#define _USE_MATH_DEFINES
#include "Entity.h"
#include <GL/freeglut.h>
#include <glm.hpp>
#include <gtc/type_ptr.hpp>
#include <math.h>

class CompoundEntity
{
public:
	CompoundEntity();
	~CompoundEntity();
	Entity* getEntity(int i);
	void render(glm::dmat4 const& modelViewMat);
	void update();
protected:
	std::vector<Entity*> grObjects;
	glm::dmat4 modelMat;
};

