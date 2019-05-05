#include "CompoundEntity.h"



CompoundEntity::CompoundEntity()
{
}


CompoundEntity::~CompoundEntity()
{
	for (Entity* it : grObjects) delete it;
}

Entity * CompoundEntity::getEntity(int i)
{
	return nullptr;
}

void CompoundEntity::render(glm::dmat4 const& modelViewMat)
{
	glMatrixMode(GL_MODELVIEW);
	glm::dmat4 aMat = modelViewMat * modelMat;
	glLoadMatrixd( glm::value_ptr(aMat));
	for (Entity* it : grObjects) {
		it->render(aMat);
	}
}

void CompoundEntity::update()
{
	for (Entity* it : grObjects) {
		it->update();
	}
}
