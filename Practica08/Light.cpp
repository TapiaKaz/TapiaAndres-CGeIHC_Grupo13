#include "Light.h"

Light::Light()
{
	color = glm::vec3(1.0f, 1.0f, 1.0f);
	ambientIntensity = 1.0f;
	diffuseIntensity = 0.0f;
	prendida = true; // por defecto todas las luces deben de estar prendidas
}


Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity)
{
	color = glm::vec3(red, green, blue);
	ambientIntensity = aIntensity;
	diffuseIntensity = dIntensity;
	prendida = true;
}

void Light::setEstado(GLboolean estadoNuevo) { prendida = estadoNuevo; } // setter que establece el valor de la luz en apagado o prendido
GLboolean Light::getEstadoLuz() { return prendida; } // getter para obtener el estado de la luz
void Light::changeColor(float red, float green, float blue) { color = glm::vec3(red, green, blue); }

Light::~Light()
{
}
