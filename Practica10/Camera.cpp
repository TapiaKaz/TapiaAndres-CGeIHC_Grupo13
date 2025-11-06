#include "Camera.h"

Camera::Camera()
{
	thirdPersonMode = false;
	thirdPersonDistance = 10.0f;
	thirdPersonHeight = 3.0f;
	cameraSmoothing = 5.0f;
}

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed)
{
	position = startPosition;
	worldUp = startUp;
	yaw = startYaw;
	pitch = startPitch;
	front = glm::vec3(0.0f, 0.0f, -1.0f);

	moveSpeed = startMoveSpeed;
	turnSpeed = startTurnSpeed;

	// Configuración tercera persona
	thirdPersonMode = false;
	thirdPersonDistance = 10.0f;
	thirdPersonHeight = 3.0f;
	cameraSmoothing = 5.0f;

	update();
}

void Camera::keyControl(bool* keys, GLfloat deltaTime)
{
	// Solo permitir control libre si NO está en modo tercera persona
	if (thirdPersonMode) return;

	GLfloat velocity = moveSpeed * deltaTime;

	if (keys[GLFW_KEY_W])
	{
		position -= front * velocity;
	}

	if (keys[GLFW_KEY_S])
	{
		position += front * velocity;
	}

	if (keys[GLFW_KEY_A])
	{
		position += right * velocity;
	}

	if (keys[GLFW_KEY_D])
	{
		position -= right * velocity;
	}
}

void Camera::mouseControl(GLfloat xChange, GLfloat yChange)
{
	xChange *= turnSpeed;
	yChange *= turnSpeed;

	yaw += xChange;
	pitch += yChange;


	if (pitch > 89.0f)
	{
		pitch = 89.0f;
	}

	if (pitch < -89.0f)
	{
		pitch = -89.0f;
	}

	update();
}

void Camera::followTarget(glm::vec3 targetPosition, GLfloat deltaTime)
{
	if (!thirdPersonMode) return;

	// ==========================================
	// MOVIMIENTO ESFÉRICO COMPLETO
	// ==========================================

	// Convertir ángulos a radianes
	float radYaw = glm::radians(yaw);
	float radPitch = glm::radians(pitch);

	// Calcular posición en coordenadas esféricas
	// X = radio * cos(pitch) * sin(yaw)
	// Y = radio * sin(pitch)
	// Z = radio * cos(pitch) * cos(yaw)

	glm::vec3 offset;
	offset.x = thirdPersonDistance * cos(radPitch) * sin(radYaw);
	offset.y = thirdPersonDistance * sin(radPitch);
	offset.z = thirdPersonDistance * cos(radPitch) * cos(radYaw);

	// Posición deseada de la cámara (target + offset esférico)
	glm::vec3 desiredPosition = targetPosition - offset;

	// Suavizar el movimiento de la cámara (lerp)
	float lerpFactor = cameraSmoothing * deltaTime;
	if (lerpFactor > 1.0f) lerpFactor = 1.0f;

	position = glm::mix(position, desiredPosition, lerpFactor);

	// Hacer que la cámara siempre mire al target
	front = glm::normalize(targetPosition - position);

	// Actualizar vectores right y up
	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}

glm::mat4 Camera::calculateViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

glm::vec3 Camera::getCameraPosition()
{
	return position;
}

glm::vec3 Camera::getCameraDirection()
{
	return glm::normalize(front);
}

void Camera::update()
{
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}

Camera::~Camera()
{
}