#include "Window.h"

Window::Window()
{
	width = 800;
	height = 600;
	movingForward = false;
	movingBackward = false;
	movingLeft = false;
	movingRight = false;
	scrollChange = 0.0f;  // NUEVO
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}

Window::Window(GLint windowWidth, GLint windowHeight)
{
	width = windowWidth;
	height = windowHeight;
	muevex = 2.0f;
	helicopterx = 0.0f;
	navi = true;
	movingForward = false;
	movingBackward = false;
	movingLeft = false;
	movingRight = false;
	scrollChange = 0.0f;  // NUEVO
	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
}

int Window::Initialise()
{
	//Inicialización de GLFW
	if (!glfwInit())
	{
		printf("Falló inicializar GLFW");
		glfwTerminate();
		return 1;
	}
	//Asignando variables de GLFW y propiedades de ventana
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//para solo usar el core profile de OpenGL y no tener retrocompatibilidad
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//CREAR VENTANA
	mainWindow = glfwCreateWindow(width, height, "Overmask - Proyecto Final CG", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tamaño de Buffer
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//MANEJAR TECLADO y MOUSE
	createCallbacks();

	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Falló inicialización de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST); //HABILITAR BUFFER DE PROFUNDIDAD

	//Asignar Viewport
	glViewport(0, 0, bufferWidth, bufferHeight);
	//Callback para detectar que se está usando la ventana
	glfwSetWindowUserPointer(mainWindow, this);
}

void Window::createCallbacks()
{
	glfwSetKeyCallback(mainWindow, ManejaTeclado);
	glfwSetCursorPosCallback(mainWindow, ManejaMouse);
	glfwSetScrollCallback(mainWindow, ManejaScroll);  // NUEVO: Callback del scroll
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

// ==========================================
// NUEVO: Método para obtener cambio de scroll
// ==========================================
GLfloat Window::getScrollChange()
{
	GLfloat theChange = scrollChange;
	scrollChange = 0.0f;  // Reiniciar después de leer
	return theChange;
}

void Window::ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	// Control de Navi con ESPACIO
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		theWindow->navi = !(theWindow->navi);

	// ==========================================
	// CONTROL DE MOVIMIENTO WASD
	// ==========================================

	// Tecla W - Adelante
	if (key == GLFW_KEY_W)
	{
		if (action == GLFW_PRESS)
			theWindow->movingForward = true;
		else if (action == GLFW_RELEASE)
			theWindow->movingForward = false;
	}

	// Tecla S - Atrás
	if (key == GLFW_KEY_S)
	{
		if (action == GLFW_PRESS)
			theWindow->movingBackward = true;
		else if (action == GLFW_RELEASE)
			theWindow->movingBackward = false;
	}

	// Tecla A - Izquierda
	if (key == GLFW_KEY_A)
	{
		if (action == GLFW_PRESS)
			theWindow->movingLeft = true;
		else if (action == GLFW_RELEASE)
			theWindow->movingLeft = false;
	}

	// Tecla D - Derecha
	if (key == GLFW_KEY_D)
	{
		if (action == GLFW_PRESS)
			theWindow->movingRight = true;
		else if (action == GLFW_RELEASE)
			theWindow->movingRight = false;
	}

	// Mantener compatibilidad con teclas anteriores
	theWindow->movimientoAuto = 0.0f;

	if (key == GLFW_KEY_Y && action != GLFW_RELEASE)
	{
		theWindow->muevex += 1.0;
		theWindow->movimientoAuto = -1.0f;
	}
	if (key == GLFW_KEY_U && action != GLFW_RELEASE)
	{
		theWindow->muevex -= 1.0;
		theWindow->movimientoAuto = +1.0f;
	}
	if (key == GLFW_KEY_H) theWindow->helicopterx += 1.0;
	if (key == GLFW_KEY_J) theWindow->helicopterx -= 1.0;

	// Almacenar estado general de teclas
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

// ==========================================
// NUEVO: Callback para la rueda del mouse
// ==========================================
void Window::ManejaScroll(GLFWwindow* window, double xOffset, double yOffset)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	// yOffset: positivo = scroll hacia arriba (zoom in)
	//          negativo = scroll hacia abajo (zoom out)
	theWindow->scrollChange = yOffset;
}

Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}