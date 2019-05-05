//#pragma once
#ifndef _H_Mesh_H_
#define _H_Mesh_H_

#define _USE_MATH_DEFINES
#include <GL/freeglut.h>
#include <glm.hpp>
#include <math.h>

//-------------------------------------------------------------------------

class Mesh 
{
public:
	static Mesh* createRGBAxes(GLdouble l); // creates a new 3D RGB axes mesh
	static Mesh* generaPoliespiral(glm::dvec2 verIni, GLdouble angIni, GLdouble
		incrAng, GLdouble ladoIni, GLdouble incrLado, GLuint numVert); // creates a new poliespiral
	static Mesh* generaDragon(GLuint numVert);	//create a new dragon
	static Mesh* generaTriangulo(GLdouble r, double x, double y);	//create a triangle
	static Mesh* generaTrianguloRGB(GLdouble r, double x, double y);	//create a RGB triangle
	static Mesh* generaRectangulo(GLdouble h, GLdouble w);	//create a triangle
	static Mesh* generaRectanguloRGB(GLdouble h, GLdouble w);	//create a RGB triangle
	static Mesh* generaEstrella3D(GLdouble er, GLdouble np, GLdouble h);	//create a estrella
	static Mesh* generaContCubo(GLdouble l);	//create a Cubo
	static Mesh* generaSuelo(GLdouble, GLdouble, GLdouble);
	static Mesh* generaRectanguloTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh); //cubre el rectángulo con una imagen que se repite rw veces a lo ancho y rh a lo alto.
	static Mesh* generaEstrellaTexCor(GLdouble r, GLdouble nL, GLdouble h); //coordenadas de textura a la estrella centrando la imagen en su vértice (0, 0, 0)
	static Mesh* generaCajaTexCor(GLdouble l); //caja con texturas 
	static Mesh* generaFoto(GLdouble h, GLdouble w); //rectangulo con foto de renderizado anterior
	static Mesh* generaTablero(GLdouble x, GLdouble h, GLdouble w);
	static Mesh* generaRectanguloRotor(GLdouble h, GLdouble w);	//create a triangle



	Mesh(void) { };
	~Mesh(void);
	virtual void render();

	glm::dvec3* getVertices() { return vertices; };  // vertex array
	glm::dvec4* getColors() { return colors; };      // color array
   
protected:

	GLuint numVertices = 0;   // arrays size (number of elements)
	GLuint primitive = GL_TRIANGLES;  // graphic primitive: GL_POINTS, GL_LINES, GL_TRIANGLES, ...

	glm::dvec3* vertices = nullptr;  // vertex array
	glm::dvec4* colors = nullptr;    // color array
	glm::dvec2* texturas = nullptr;	 // texturas array
};

class MBR : public Mesh {
public:
	MBR(int, int, glm::dvec3*);
	void vertexBuilding();
	void normalize();
	void render();
protected:
	int m; // numero de puntos del perfil
	int n; // numero de rotaciones que se toman
	glm::dvec3* perfil = nullptr; //perfil original en el plano XY
	glm::dvec3* normals = nullptr;
};

//-------------------------------------------------------------------------

#endif //_H_Scene_H_