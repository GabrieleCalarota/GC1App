#pragma once
#include <GL/freeglut.h>
#include <glm.hpp>
#include "Pixmap32RGBA.h"

class Texture
{
public:
	Texture() : w(0), h(0), id(0) {};
	~Texture() { if (id != 0) glDeleteTextures(1, &id); };
	void load(const std::string & BMP_Name, GLubyte alpha = 255);
	void loadColorBuffer(); //load previous render
	// cargar y transferir a GPU
	void bind(GLint modo = GL_REPLACE); // para mezcla de colores
	void unbind() { glBindTexture(GL_TEXTURE_2D, 0); };
protected:
	GLuint w, h; // dimensiones de la imagen
	GLuint id;
	// identificador interno (GPU) de la textura
	void init();
};

