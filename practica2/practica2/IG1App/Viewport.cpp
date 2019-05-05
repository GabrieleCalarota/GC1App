#include "Viewport.h"

//-------------------------------------------------------------------------

void Viewport::uploadSize(GLsizei aw, GLsizei ah)
{
	setSize(aw, ah);
	upload();
}
//-------------------------------------------------------------------------

void Viewport::uploadPos(GLsizei al, GLsizei ab)
{
	setPos(al, ab);
	upload();
}
//-------------------------------------------------------------------------

void Viewport::upload() const
{
	glViewport(xLeft, yBot, width, height); // transfers viewport to the GPU
}
//-------------------------------------------------------------------------


