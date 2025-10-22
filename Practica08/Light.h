#pragma once

#include <glew.h>
#include <glm.hpp>

class Light
{
public:
	Light();
	Light(GLfloat red, GLfloat green, GLfloat blue, 
			GLfloat aIntensity, GLfloat dIntensity);

	~Light();

	void changeColor(float red, float green, float blue);
	void setEstado(GLboolean estado); // funcion setter definida (LineaAgregada)
	GLboolean getEstadoLuz(); // funcion getter definida (LineaAgregada)

protected:
	glm::vec3 color;
	GLfloat ambientIntensity;
	GLfloat diffuseIntensity;
	GLboolean prendida; // Linea agregada para apagar o prender la luz, conociendo su estado (LineaAgregada)
};

