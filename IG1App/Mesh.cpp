
#include "Mesh.h"

using namespace glm;

//-------------------------------------------------------------------------

Mesh ::~Mesh(void) 
{
  delete[] vertices;  vertices = nullptr;
  delete[] colors;    colors = nullptr;
  delete[] texturas; texturas = nullptr;
}
//-------------------------------------------------------------------------

void Mesh::render()
{
  if (vertices != nullptr) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, vertices);  // number of coordinates per vertex, type of each coordinate, stride, pointer 
    if (colors != nullptr) {
      glEnableClientState(GL_COLOR_ARRAY);
      glColorPointer(4, GL_DOUBLE, 0, colors);   // number of coordinates per color, type of each coordinate, stride, pointer 
    }
	if (texturas != nullptr) {
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_DOUBLE, 0, texturas);
	}
	
    glDrawArrays(primitive, 0, numVertices);   // primitive graphic, first index and number of elements to be rendered

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
  }
}
//-------------------------------------------------------------------------

Mesh * Mesh::createRGBAxes(GLdouble l)
{
  Mesh* m = new Mesh();
  m->primitive = GL_LINES;
  m->numVertices = 6;

  m->vertices = new dvec3[m->numVertices];
  // X axis vertices
  m->vertices[0] = dvec3(0.0, 0.0, 0.0);   
  m->vertices[1] = dvec3(l, 0.0, 0);
  // Y axis vertices
  m->vertices[2] = dvec3(0, 0.0, 0.0);
  m->vertices[3] = dvec3(0.0, l, 0.0); 
  // Z axis vertices
  m->vertices[4] = dvec3(0.0, 0.0, 0.0);
  m->vertices[5] = dvec3(0.0, 0.0, l);

  m->colors = new dvec4[m->numVertices];
  // X axis color: red  ( Alpha = 1 : fully opaque)
  m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
  m->colors[1] = dvec4(1.0, 0.0, 0.0, 1.0);
  // Y axis color: green
  m->colors[2] = dvec4(0.0, 1.0, 0.0, 1.0);
  m->colors[3] = dvec4(0.0, 1.0, 0.0, 1.0);
  // Z axis color: blue
  m->colors[4] = dvec4(0.0, 0.0, 1.0, 1.0);
  m->colors[5] = dvec4(0.0, 0.0, 1.0, 1.0);
 
  return m; 
}
//-------------------------------------------------------------------------

/*POLIESPIRAL*/
Mesh * Mesh::generaPoliespiral(glm::dvec2 verIni, GLdouble angIni, GLdouble
	incrAng, GLdouble ladoIni, GLdouble incrLado, GLuint numVert) {

	Mesh* m = new Mesh();
	m->primitive = GL_LINE_STRIP;
	m->numVertices = numVert;

	m->vertices = new dvec3[m->numVertices];

	double x = verIni.x;
	double y = verIni.y;
	double lado = ladoIni;
	double ang = angIni;
	int i = 0;
	for (i; i < m->numVertices; i++) {
		m->vertices[i] = dvec3(x, y, 0.0);
		x = x + lado * cos(radians(ang));
		y = y + lado * sin(radians(ang));
		lado += incrLado;
		ang += incrAng;
	}
	return m;
}
//-------------------------------------------------------------------------

/* DRAGO */
Mesh * Mesh::generaDragon(GLuint numVert)
{
	double PR1 = 0.787473;
	double PR2 = 1 - PR1;
	double x = 0.0;
	double y = 0.0;
	double azar = 0.0;
	Mesh* m = new Mesh();
	m->primitive = GL_POINTS;
	m->numVertices = numVert;

	m->vertices = new dvec3[m->numVertices];


	for (int i = 0; i < numVert; i++) {
		azar = rand() / double(RAND_MAX);
		m->vertices[i] = dvec3(x, y, 0.0);
		double oldx = x;
		if (azar < PR1) {
			// T1
			x = 0.824074 * oldx + 0.281482 * y - 0.882290;
			y = -0.212346 * oldx + 0.864198 * y - 0.110607;
		}
		else {
			// T2 
			x = 0.088272 * oldx + 0.520988 * y + 0.785360;
			y = -0.463889 * oldx - 0.377778 * y + 8.095795;
		}
	}
	return m;
}
//-------------------------------------------------------------------------

/* Triangulo */
Mesh * Mesh::generaTriangulo(GLdouble r, double centre_x, double centre_y) {

	Mesh* m = new Mesh();
	m->primitive = GL_TRIANGLES;
	m->numVertices = 3;
	m->vertices = new dvec3[m->numVertices];
	double x = 0.0;
	double y = 0.0;
	double angIni = 90.0;
	double incrAng = 120.0;
	double ang = angIni;
	for (int i = 0; i < 3; i++) {
		x = centre_x + r * cos(radians(ang));
		y = centre_y + r * sin(radians(ang));
		m->vertices[i] = dvec3(x, y, 0.0);
		ang += incrAng;
	}
	return m;
}
//-------------------------------------------------------------------------


/* TrianguloRGB */
Mesh * Mesh::generaTrianguloRGB(GLdouble r, double x, double y) {

	Mesh* m = generaTriangulo(r,x,y);
	m->colors = new dvec4[3];
	m->colors[0] = dvec4(1.0, 0.0, 0.0, 1.0);
	m->colors[1] = dvec4(0.0, 1.0, 0.0, 1.0);
	// Y axis color: green
	m->colors[2] = dvec4(0.0, 0.0, 1.0, 1.0);

	return m;
}
//-------------------------------------------------------------------------

/* Rectangulo */
Mesh * Mesh::generaRectangulo(GLdouble h, GLdouble w) {

	Mesh* m = new Mesh();
	m->primitive = GL_TRIANGLE_STRIP;
	m->numVertices = 4;
	m->vertices = new dvec3[m->numVertices];
	double x = 0;
	double y = 0;
	m->vertices[0] = dvec3(x, y, 0.0);
	m->vertices[1] = dvec3(x + w, y, 0.0);
	m->vertices[2] = dvec3(x, y - h, 0.0);
	m->vertices[3] = dvec3(x + w, y - h, 0.0);

	return m;
}
//-------------------------------------------------------------------------


/* RectanguloRGB */
Mesh * Mesh::generaRectanguloRGB(GLdouble h, GLdouble w) {

	Mesh* m = generaRectangulo(h, w);

	return m;
}
//-------------------------------------------------------------------------


/* Estrella3D */
Mesh * Mesh::generaEstrella3D(GLdouble re, GLdouble np, GLdouble h) {

	Mesh* m = new Mesh();
	m->primitive = GL_TRIANGLE_FAN;
	m->numVertices = 2 * np + 2;
	double ri = re / 2;
	m->vertices = new dvec3[m->numVertices];
	m->colors = new dvec4[m->numVertices];
	double x = 0.0;
	double y = 0.0;
	double z = 0.0;
	double incrAng = 360 / (2*np);
	double ang = 0.0;
	m->vertices[0] = dvec3(x, y, z);
	for (int i = 1; i < (m->numVertices); i++) {
		if (i % 2 == 0) {
			x = re * cos(radians(ang));
			y = re * sin(radians(ang));
		}
		else {
			x = ri * cos(radians(ang));
			y = ri * sin(radians(ang));
		}
		m->vertices[i] = dvec3(x, y, h);
		m->colors[i] = dvec4(0.6,1/(10+i),0.2,1.0);
		ang += incrAng;
	}
	return m;
}
//-------------------------------------------------------------------------

/* Caja */
Mesh * Mesh::generaContCubo(GLdouble l) {
	Mesh* m = new Mesh();
	m->primitive = GL_TRIANGLE_STRIP;
	m->numVertices = 14;
	m->vertices = new dvec3[m->numVertices];
	double x = 0;
	double y = 0;
	double z = 0;
	m->vertices[0] = dvec3(x-(l / 2),y+l/2, z+(l / 2));
	m->vertices[1] = dvec3(x-(l / 2), y-l/2, z+(l / 2));
	m->vertices[2] = dvec3(x+(l / 2), y+l/2 , z + (l / 2));
	m->vertices[3] = dvec3(x+(l / 2), y-l/2, z+ (l / 2));
	m->vertices[4] = dvec3(x+(l / 2), y+l/2, z-(l / 2));
	m->vertices[5] = dvec3(x+(l / 2), y-l/2, z-(l / 2));
	m->vertices[6] = dvec3(x-(l / 2), y+l/2, z-(l / 2));
	m->vertices[7] = dvec3(x-(l / 2), y-l/2, z-(l / 2));
	m->vertices[8] = dvec3(x-(l / 2), y+l/2,z+( l / 2));
	m->vertices[9] = dvec3(x-(l / 2), y-l/2, z+(l / 2));
	m->vertices[10] = dvec3(x - (l / 2), y-l/2, z - (l / 2));
	m->vertices[11] = dvec3(x - (l / 2), y-l/2, z + (l / 2));
	m->vertices[12] = dvec3(x + (l / 2), y-l/2, z - (l / 2));
	m->vertices[13] = dvec3(x + (l / 2), y-l/2, z + (l / 2));
	
	return m;
}
//-------------------------------------------------------------------------

/*SUELO*/
Mesh * Mesh::generaSuelo(GLdouble h, GLdouble w, GLdouble p)
{
	Mesh* m = new Mesh();
	m->primitive = GL_TRIANGLE_STRIP;
	m->numVertices = 4;
	m->vertices = new dvec3[m->numVertices];
	double x = 0;
	double y = 0;
	m->vertices[0] = dvec3(-h/2, 0.0, -w/2);
	m->vertices[1] = dvec3(h/2, 0.0, -w/2);
	m->vertices[2] = dvec3(-h/2, 0.0 , w/2);
	m->vertices[3] = dvec3(h/2, 0.0, w/2);
	return m;
}
//-------------------------------------------------------------------------

/*SueloTex*/
Mesh * Mesh::generaRectanguloTexCor(GLdouble w, GLdouble h, GLuint rw, GLuint rh)
{
	Mesh *m = generaSuelo(h, w, 0);
	m->texturas = new dvec2[m->numVertices];
	m->texturas[0] = dvec2(0, rh);
	m->texturas[1] = dvec2(0, 0);
	m->texturas[2] = dvec2(rw, rh);
	m->texturas[3] = dvec2(rw, 0);
	return m;
}
//-------------------------------------------------------------------------

/*EstrellaTex*/
Mesh * Mesh::generaEstrellaTexCor(GLdouble r, GLdouble nL, GLdouble h)
{
	Mesh *m = generaEstrella3D(r, nL, h);
	m->texturas = new dvec2[m->numVertices];
	double x = 0;
	double y = 0;
	double ang = 0;
	double incr = 360.0 / (2 * nL);
	m->texturas[0] = dvec2(0.5, 0.5);
	for (int i = 1; i < m->numVertices; i++) {
		x = 0.5 + 0.5 * cos(radians(ang));
		y = 0.5 + 0.5 * sin(radians(ang));
		m->texturas[i] = dvec2(x, y);
		ang += incr;
	}
	return m;
}
//-------------------------------------------------------------------------

/*CajaTex*/
Mesh * Mesh::generaCajaTexCor(GLdouble l)
{
	Mesh* m = generaContCubo(l);
	m->texturas = new dvec2[m->numVertices];
	m->texturas[0] = dvec2(0,1);
	m->texturas[1] = dvec2(0,0);
	m->texturas[2] = dvec2(1,1);
	m->texturas[3] = dvec2(1,0);
	m->texturas[4] = dvec2(2,1);
	m->texturas[5] = dvec2(2,0);
	m->texturas[6] = dvec2(3,1);
	m->texturas[7] = dvec2(3,0);
	m->texturas[8] = dvec2(4,1);
	m->texturas[9] = dvec2(4,0);
	m->texturas[10] = dvec2(3, 0);
	m->texturas[11] = dvec2(0, 0);
	m->texturas[12] = dvec2(2, 0);
	m->texturas[13] = dvec2(1, 0);
	return m;
}
//-------------------------------------------------------------------------

/*Foto*/
Mesh * Mesh::generaFoto(GLdouble h, GLdouble w) {
	Mesh* m = generaRectangulo(h, w);
	m->texturas = new dvec2[m->numVertices];
	m->texturas[0] = dvec2(0, 1);
	m->texturas[1] = dvec2(1, 1);
	m->texturas[2] = dvec2(0, 0);
	m->texturas[3] = dvec2(1, 0);
	return m;
}
Mesh * Mesh::generaTablero(GLdouble p, GLdouble h, GLdouble w)
{
	Mesh* m = new Mesh();
	m->primitive = GL_TRIANGLE_STRIP;
	m->numVertices = 10;
	m->vertices = new dvec3[m->numVertices];
	double x = 100;
	double y = 0;
	double z = 0;
	m->vertices[0] = dvec3(x - (p / 2), y + h, z + (w / 2));
	m->vertices[1] = dvec3(x - (p / 2), y, z + (w / 2));
	m->vertices[2] = dvec3(x + (p / 2), y + h, z + (w / 2));
	m->vertices[3] = dvec3(x + (p / 2), y, z + (w / 2));
	m->vertices[4] = dvec3(x + (p / 2), y + h, z - (w / 2));
	m->vertices[5] = dvec3(x + (p / 2), y, z - (w / 2));
	m->vertices[6] = dvec3(x - (p / 2), y + h, z - (w / 2));
	m->vertices[7] = dvec3(x - (p / 2), y, z - (w / 2));
	m->vertices[8] = dvec3(x - (p / 2), y + h, z + (w / 2));
	m->vertices[9] = dvec3(x - (p / 2), y, z + (w / 2));
	return m;
}
Mesh * Mesh::generaRectanguloRotor(GLdouble h, GLdouble w)
{

		Mesh* m = new Mesh();
		m->primitive = GL_TRIANGLE_STRIP;
		m->numVertices = 4;
		m->vertices = new dvec3[m->numVertices];
		double x = 0;
		double y = 0;
		double z = 0;
		m->vertices[0] = dvec3(x-w/2, 0.0, 0.0);
		m->vertices[1] = dvec3(x + w/2, 0.0, 0.0);
		m->vertices[2] = dvec3(x-w/2, 0.0, h);
		m->vertices[3] = dvec3(x + w/2, 0.0, h);

		return m;
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

MBR::MBR(int puntos, int rotaciones, glm::dvec3 * perfil1)
{
	m = puntos;
	n = rotaciones;
	perfil = perfil1;
	numVertices = n * m;
	vertexBuilding();
	normalize();
}
//-------------------------------------------------------------------------

void MBR::vertexBuilding()
{
	//this->numVertices = n * m;
	this->vertices = new dvec3[this->numVertices];
	for (int i = 0; i < n; i++) {
		double theta = i * 2 * M_PI / n;
		double c = cos(theta);
		double s = sin(theta);
		for (int j = 0; j < m; j++) {
			int indice = i * m + j;
			double x = c * perfil[j][0] + s * perfil[j][2];
			double z = -s * perfil[j][0] + c * perfil[j][2];
			dvec3 p = dvec3(x, perfil[j][1], z);
			vertices[indice] = p;
		}
	}
}
//-------------------------------------------------------------------------

void MBR::normalize()
{
	this->normals = new dvec3[this->numVertices];
	for (int i = 0; i < this->numVertices; i++) {
		this->normals[i] = dvec3(0, 0, 0);
	}
	for (int i = 0; i < n; i++) {
	for (int j = 0; j < m - 1; j++) {
		int indice = i * m + j;
		dvec3 aux0 = this->vertices[indice];
		dvec3 aux1 = this->vertices[(indice + m)%(n*m)];
		dvec3 aux2 = this->vertices[(indice + 1 + m)%(n*m)];

		dvec3 norm = glm::cross(aux2 - aux1, aux0 - aux1);
		normals[indice] += norm;
		normals[(indice + m) % (n*m)] += norm;
		normals[(indice + 1 + m) % (n*m)] += norm;
		normals[indice + 1] += norm;

	}
	normals[i] = glm::normalize(normals[i]);
	}	
}
//-------------------------------------------------------------------------

void MBR::render()
{
	if (vertices != nullptr) {
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_DOUBLE, 0, vertices);
		if (normals != nullptr) {
			glEnableClientState(GL_NORMAL_ARRAY);
			glNormalPointer(GL_DOUBLE, 0, normals);
			primitive = GL_POLYGON;
			for (int i = 0; i < n; i++) {
				for (int j = 0; j < m - 1; j++) {
					int indice = i * m + j;
					unsigned int index[] = { indice, (indice + m) % (n*m), (indice + m + 1) % (n*m), indice + 1 };
					glDrawElements(primitive, 4, GL_UNSIGNED_INT, index);
				}
			}
		}
		glDisableClientState(GL_NORMAL_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
	
	
}
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------
