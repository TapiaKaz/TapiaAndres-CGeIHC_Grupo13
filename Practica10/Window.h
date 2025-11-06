#pragma once
#include<stdio.h>
#include<glew.h>
#include<glfw3.h>

class Window
{
public:
	Window();
	Window(GLint windowWidth, GLint windowHeight);
	int Initialise();
	GLfloat getBufferWidth() { return bufferWidth; }
	GLfloat getBufferHeight() { return bufferHeight; }
	GLfloat getXChange();
	GLfloat getYChange();
	GLfloat getmuevex() { return muevex; }
	GLfloat gethelicopterx() { return helicopterx; }
	bool getShouldClose() {
		return  glfwWindowShouldClose(mainWindow);
	}
	bool* getsKeys() { return keys; }
	void swapBuffers() { return glfwSwapBuffers(mainWindow); }

	GLfloat getMovimientoAuto() { return movimientoAuto; }
	GLboolean getEstadoNavi() { return navi; }

	// ==========================================
	// NUEVOS MÉTODOS PARA CONTROL DEL PERSONAJE
	// ==========================================

	// Retorna true si hay algún input de movimiento (WASD)
	bool isMoving() { return movingForward || movingBackward || movingLeft || movingRight; }

	// Getters individuales de dirección
	bool isMovingForward() { return movingForward; }
	bool isMovingBackward() { return movingBackward; }
	bool isMovingLeft() { return movingLeft; }
	bool isMovingRight() { return movingRight; }

	// ==========================================
	// NUEVO: SOPORTE PARA RUEDA DEL MOUSE (SCROLL)
	// ==========================================
	GLfloat getScrollChange();

	~Window();

private:
	GLFWwindow* mainWindow;
	GLint width, height;
	bool keys[1024];
	GLint bufferWidth, bufferHeight;
	void createCallbacks();
	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	GLfloat muevex, helicopterx;
	GLfloat movimientoAuto;
	GLboolean navi;
	bool mouseFirstMoved;

	// Estados de movimiento
	bool movingForward;
	bool movingBackward;
	bool movingLeft;
	bool movingRight;

	// NUEVO: Variable para el scroll
	GLfloat scrollChange;

	static void ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode);
	static void ManejaMouse(GLFWwindow* window, double xPos, double yPos);
	static void ManejaScroll(GLFWwindow* window, double xOffset, double yOffset);  // NUEVA
};