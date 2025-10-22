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
	GLfloat gethelicopterx() { return helicopterx; } // Agregado funcion para obtener el mov del helicoptero
	bool getShouldClose() {
		return  glfwWindowShouldClose(mainWindow);}
	bool* getsKeys() { return keys; }
	void swapBuffers() { return glfwSwapBuffers(mainWindow); }
	
	GLfloat getMovimientoAuto() { return movimientoAuto; } // funcion setter agregada para marcar la dirección del movimiento del auto que nos da el teclado
																								//las luces cuando se precione una tecla

	GLboolean getEstadoNavi() { return navi; } // funcion para retornar si se preciono espacio o no
	~Window();
private: 
	GLFWwindow *mainWindow;
	GLint width, height;
	bool keys[1024];
	GLint bufferWidth, bufferHeight;
	void createCallbacks();
	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	GLfloat muevex, helicopterx; // Agregando variable para el mov del helicoptero
	GLfloat movimientoAuto; // Agregado para saber cuando el usuario apreciona alguna tecla
	GLboolean navi;
	bool mouseFirstMoved;
	static void ManejaTeclado(GLFWwindow* window, int key, int code, int action, int mode);
	static void ManejaMouse(GLFWwindow* window, double xPos, double yPos);

};

