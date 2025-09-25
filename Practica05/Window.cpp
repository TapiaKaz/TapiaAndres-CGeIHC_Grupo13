#include "Window.h"
#include <cmath>

Window::Window()
{
	width = 800;
	height = 600;
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}

Window::Window(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
	rotax = 0.0f;
	rotay = 0.0f;
	rotaz = 0.0f;
	articulacion1 = 0.0f;
	articulacion2 = 0.0f;
	articulacion3 = 0.0f;
	articulacion4 = 0.0f;

	// Variables para Carrito
	carPosition = glm::vec3(10.0f, 18.0f, -10.0f);
	
	carSpeed   = 0.4f; 
	angleSpeed = 0.5f;

	carAngle    = 0.0f;
	wheelRotate = 0.0f;

	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}

void Window::updateCar()
{
	if (keys[GLFW_KEY_UP]) {
		float angleRad = glm::radians(carAngle);
		glm::vec3 forward = glm::vec3(sin(angleRad), 0.0f, cos(angleRad));
		carPosition += forward * carSpeed;
		wheelRotate += 5.0f;

		if (keys[GLFW_KEY_LEFT]) {
			carAngle += angleSpeed;
		}
		if (keys[GLFW_KEY_RIGHT]) {
			carAngle -= angleSpeed;
		}
	}

	if (keys[GLFW_KEY_DOWN]) {
		float angleRad = glm::radians(carAngle);
		glm::vec3 forward = glm::vec3(sin(angleRad), 0.0f, cos(angleRad));
		carPosition -= forward * carSpeed;
		wheelRotate -= 5.0f;

		if (keys[GLFW_KEY_LEFT]) {
			carAngle += angleSpeed;
		}
		if (keys[GLFW_KEY_RIGHT]) {
			carAngle -= angleSpeed;
		}
	}
}

int Window::Initialise()
{
	if (!glfwInit())
	{
		printf("Falló inicializar GLFW");
		glfwTerminate();
		return 1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	mainWindow = glfwCreateWindow(width, height, "Practica XX: Nombre de la práctica", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}

	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);
	glfwMakeContextCurrent(mainWindow);
	createCallbacks();

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		printf("Falló inicialización de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, bufferWidth, bufferHeight);
	glfwSetWindowUserPointer(mainWindow, this);
}

void Window::createCallbacks()
{
	glfwSetKeyCallback(mainWindow, ManejaTeclado);
	glfwSetCursorPosCallback(mainWindow, ManejaMouse);
}

GLfloat Window::getXChange()
{
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

GLfloat Window::getYChange()
{
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}

void Window::ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key == GLFW_KEY_E)
	{
		theWindow->rotax += 10.0;
	}
	if (key == GLFW_KEY_R) 
	{
		theWindow->rotay += 10.0;
	}
	if (key == GLFW_KEY_T && action == GLFW_PRESS)
	{
		theWindow->rotaz += 10.0;
	}
	if (key == GLFW_KEY_F)
	{
		if (theWindow->articulacion1 >= -45.0) theWindow->articulacion1 -= 5.0;
	}
	if (key == GLFW_KEY_G)
	{
		if (theWindow->articulacion2 >= -45.0) theWindow->articulacion2 -= 5.0;
	}
	if (key == GLFW_KEY_H && action == GLFW_PRESS)
	{
		if (theWindow->articulacion3 >= -25.0) theWindow->articulacion3 -= 5.0;
	}
	if (key == GLFW_KEY_J && action == GLFW_PRESS)
	{
		if (theWindow->articulacion4 >= -25.0) theWindow->articulacion4 -= 5.0;
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
		}
	}
}

void Window::ManejaMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (theWindow->mouseFirstMoved)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}

	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;
}

Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}