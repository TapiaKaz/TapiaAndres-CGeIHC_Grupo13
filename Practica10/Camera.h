#pragma once

#include <glew.h>
#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <glfw3.h>

class Camera
{
public:
	Camera();
	Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);

	void keyControl(bool* keys, GLfloat deltaTime);
	void mouseControl(GLfloat xChange, GLfloat yChange);

	glm::vec3 getCameraPosition();
	glm::vec3 getCameraDirection();
	glm::mat4 calculateViewMatrix();

	// ==========================================
	// MODO TERCERA PERSONA
	// ==========================================

	// Seguir un target (personaje) en tercera persona
	void followTarget(glm::vec3 targetPosition, GLfloat deltaTime);

	// Configurar distancia y altura de la cámara
	void setThirdPersonDistance(GLfloat distance) { thirdPersonDistance = distance; }
	void setThirdPersonHeight(GLfloat height) { thirdPersonHeight = height; }

	// ⭐ NUEVO: Obtener la distancia actual (para zoom)
	GLfloat getThirdPersonDistance() { return thirdPersonDistance; }

	// Alternar entre modo libre y tercera persona
	void setThirdPersonMode(bool enabled) { thirdPersonMode = enabled; }
	bool isThirdPersonMode() { return thirdPersonMode; }

	~Camera();

private:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 worldUp;

	GLfloat yaw;
	GLfloat pitch;

	GLfloat moveSpeed;
	GLfloat turnSpeed;

	// Configuración de tercera persona
	bool thirdPersonMode;
	GLfloat thirdPersonDistance;  // Distancia detrás del personaje
	GLfloat thirdPersonHeight;    // Altura sobre el personaje
	GLfloat cameraSmoothing;      // Suavizado del movimiento de cámara

	void update();
};