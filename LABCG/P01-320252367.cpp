#include <stdio.h>
#include <string.h>
#include <glew.h>
#include <glfw3.h>

//Dimensiones de la ventana
const int WIDTH = 600, HEIGHT = 600;
GLuint VAO, VBO, shader;

//LENGUAJE DE SHADER (SOMBRAS) GLSL
//Vertex Shader
//recibir color, salida Vcolor
static const char* vShader = "						\n\
#version 330										\n\
layout (location =0) in vec3 pos;					\n\
void main()											\n\
{													\n\
gl_Position=vec4(pos.x,pos.y,pos.z,1.0f); 			\n\
}";

//Fragment Shader
//recibir Vcolor y dar de salida color
static const char* fShader = "						\n\
#version 330										\n\
out vec4 color;										\n\
void main()											\n\
{													\n\
	color = vec4(0.7f,0.0f,8.0f,1.0f);	 			\n\
}";



void CrearTriangulo()
{
	GLfloat vertices[] = {
		-0.8f, 0.3f, 0.0f,
		-0.8f, 0.4f, 0.0f,
		-0.3f, 0.4f, 0.0f, // Triangulo 1

		-0.3f, 0.4f, 0.0f,
		-0.8f, 0.3f, 0.0f,
		-0.3f, 0.3f, 0.0f, // Triangulo 2

		-0.6f, 0.3f, 0.0f,
		-0.6f,-0.2f, 0.0f,
		-0.5f, 0.3f, 0.0f, // Triangulo 3

		-0.6f,-0.2f, 0.0f,
		-0.5f, 0.3f, 0.0f,
		-0.5f,-0.2f, 0.0f, // Triangulo 4 para la T

		-0.1f, 0.3f, 0.0f,
		-0.1f, 0.4f, 0.0f,
		 0.3f, 0.4f, 0.0f, // Triangulo 5

		-0.1f, 0.3f, 0.0f,
		 0.3f, 0.4f, 0.0f,
		 0.3f, 0.3f, 0.0f, // Triangulo 6

		-0.1f, 0.3f, 0.0f,
		-0.1f,-0.2f, 0.0f,
		 0.0f,-0.2f, 0.0f, // Triaungulo 7

		 0.0f,-0.2f, 0.0f,
		-0.1f, 0.3f, 0.0f,
		 0.0f, 0.4f, 0.0f, // Trianugulo 8

		 0.0f,-0.2f, 0.0f,
		 0.0f,-0.1f, 0.0f,
		 0.3f,-0.1f, 0.0f, // Triangulo 9

		 0.0f,-0.2f, 0.0f,
		 0.3f,-0.1f, 0.0f,
		 0.3f,-0.2f, 0.0f, // Triangulo 10

		 0.3f,-0.1f, 0.0f,
		 0.2f,-0.1f, 0.0f,
		 0.2f, 0.1f, 0.0f, // Triangulo 11

		 0.2f, 0.1f, 0.0f,
		 0.3f,-0.1f, 0.0f,
		 0.3f, 0.1f, 0.0f, // Triangulo 12

		 0.2f, 0.1f, 0.0f,
		 0.1f, 0.1f, 0.0f,
		 0.1f, 0.0f, 0.0f, // Triangulo 13

		 0.2f, 0.1f, 0.0f,
		 0.2f, 0.0f, 0.0f,
		 0.1f, 0.0f, 0.0f, // Triangulo 13 Para la G

		 0.5f,-0.2f, 0.0f,
		 0.5f, 0.3f, 0.0f,
		 0.6f,-0.2f, 0.0f, // Triangulo 15

		 0.6f,-0.2f, 0.0f,
		 0.6f, 0.3f, 0.0f, 
		 0.5f, 0.3f, 0.0f, // Triangulo 16

		 0.5f, 0.3f, 0.0f,
		 0.5f, 0.4f, 0.0f,
		 0.7f, 0.4f, 0.0f, // Triangulo 17

		 0.7f, 0.4f, 0.0f,
		 0.7f, 0.3f, 0.0f,
		 0.5f, 0.3f, 0.0f, // Triangulo 18

		 0.7f, 0.4f, 0.0f,
		 0.8f, 0.4f, 0.0f,
		 0.8f,-0.2f, 0.0f, // Triangulo 19

		 0.7f, 0.4f, 0.0f,
		 0.7f,-0.2f, 0.0f,
		 0.8f,-0.2f, 0.0f, // Triangulo 20

		 0.6f, 0.0f, 0.0f,
		 0.6f, 0.1f, 0.0f,
		 0.7f, 0.1f, 0.0f, // Triaungulo 21

		 0.6f, 0.0f, 0.0f,
		 0.7f, 0.0f, 0.0f,
		 0.7f, 0.1f, 0.0f, // Triangulo 22 para la A
	};
	glGenVertexArrays(1, &VAO); //generar 1 VAO
	glBindVertexArray(VAO);//asignar VAO

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //pasarle los datos al VBO asignando tamano, los datos y en este caso es est�tico pues no se modificar�n los valores

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);//Stride en caso de haber datos de color por ejemplo, es saltar cierta cantidad de datos
	glEnableVertexAttribArray(0);
	//agregar valores a v�rtices y luego declarar un nuevo vertexAttribPointer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}
void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) //Funci�n para agregar los shaders a la tarjeta gr�fica
//the Program recibe los datos de theShader
{
	GLuint theShader = glCreateShader(shaderType);//theShader es un shader que se crea de acuerdo al tipo de shader: vertex o fragment
	const GLchar* theCode[1];
	theCode[0] = shaderCode;//shaderCode es el texto que se le pasa a theCode
	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);//longitud del texto
	glShaderSource(theShader, 1, theCode, codeLength);//Se le asigna al shader el c�digo
	glCompileShader(theShader);//Se comila el shader
	GLint result = 0;
	GLchar eLog[1024] = { 0 };
	//verificaciones y prevenci�n de errores
	glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al compilar el shader %d es: %s \n", shaderType, eLog);
		return;
	}
	glAttachShader(theProgram, theShader);//Si no hubo problemas se asigna el shader a theProgram el cual asigna el c�digo a la tarjeta gr�fica
}

void CompileShaders() {
	shader = glCreateProgram(); //se crea un programa
	if (!shader)
	{
		printf("Error creando el shader");
		return;
	}
	AddShader(shader, vShader, GL_VERTEX_SHADER);//Agregar vertex shader
	AddShader(shader, fShader, GL_FRAGMENT_SHADER);//Agregar fragment shader
	//Para terminar de linkear el programa y ver que no tengamos errores
	GLint result = 0;
	GLchar eLog[1024] = { 0 };
	glLinkProgram(shader);//se linkean los shaders a la tarjeta gr�fica
	//verificaciones y prevenci�n de errores
	glGetProgramiv(shader, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al linkear es: %s \n", eLog);
		return;
	}
	glValidateProgram(shader);
	glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
		printf("EL error al validar es: %s \n", eLog);
		return;
	}
}

int main()
{
	//Inicializaci�n de GLFW
	if (!glfwInit())
	{
		printf("Fall� inicializar GLFW");
		glfwTerminate();
		return 1;
	}

	//****  LAS SIGUIENTES 4 L�NEAS SE COMENTAN EN DADO CASO DE QUE AL USUARIO NO LE FUNCIONE LA VENTANA Y PUEDA CONOCER LA VERSI�N DE OPENGL QUE TIENE ****/

	//Asignando variables de GLFW y propiedades de ventana
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//para solo usar el core profile de OpenGL y no tener retrocompatibilidad
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//CREAR VENTANA
	GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "TapiaAndres Practica01", NULL, NULL);

	if (!mainWindow)
	{
		printf("Fallo en crearse la ventana con GLFW");
		glfwTerminate();
		return 1;
	}
	//Obtener tama�o de Buffer
	int BufferWidth, BufferHeight;
	glfwGetFramebufferSize(mainWindow, &BufferWidth, &BufferHeight);

	//asignar el contexto
	glfwMakeContextCurrent(mainWindow);

	//permitir nuevas extensiones
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		printf("Fall� inicializaci�n de GLEW");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	// Asignar valores de la ventana y coordenadas
	//Asignar Viewport
	glViewport(0, 0, BufferWidth, BufferHeight);

	//Llamada a las funciones creadas antes del main
	CrearTriangulo();
	CompileShaders();

	// Configuraciones para el cambio de color
	int color = 0;
	// Matriz de colores
	float colors[3][3] = {
		{1.0f, 0.0f, 0.0f}, // Rojo
		{0.0f, 1.0f, 0.0f}, // Verde
		{0.0f, 0.0f, 1.0f}  // Azul
	};
	double lastTime = glfwGetTime(); // tiempo inicial

	//Loop mientras no se cierra la ventana
	while (!glfwWindowShouldClose(mainWindow))
	{
		//Recibir eventos del usuario
		glfwPollEvents();

		//Limpiar la ventana
		glClearColor(colors[color][0], colors[color][1], colors[color][2], 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Crear el contador de cambio de color
		double currentTime = glfwGetTime();
		// En cuanto pasen 3 ó más segundos se actualizara el color
		if (currentTime - lastTime >= 3.0)
		{
			color = (color + 1) % 3; // cambia el valor para actualizar los valores de la matriz
			lastTime = currentTime;  // reiniciar el temporizador
		}
		glUseProgram(shader);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 66);
		glBindVertexArray(0);

		glUseProgram(0);

		glfwSwapBuffers(mainWindow);
		//NO ESCRIBIR NINGUNA L�NEA DESPU�S DE glfwSwapBuffers(mainWindow); 
	}
	return 0;
}