#include "Element.h"

#include <gtc/matrix_transform.hpp>  
#include <gtc/type_ptr.hpp>

using namespace glm;

//-------------------------------------------------------------------------

void GrElement::setMvM(dmat4 const& modelViewMat)
{
	glMatrixMode(GL_MODELVIEW);
	dmat4 aMat = modelViewMat * modelMat;
	glLoadMatrixd(value_ptr(aMat));
}
//-------------------------------------------------------------------------

void GrElement::render(glm::dmat4 const& modelViewMat)
{
	if (entity != nullptr) {
		setMvM(modelViewMat);
		
		entity->render();
		
	}
}


