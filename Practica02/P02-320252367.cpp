//Práctica 2: índices, mesh, proyecciones, transformaciones geométricas
#include <stdio.h>
#include <string.h>
#include<cmath>
#include<vector>
#include <glew.h>
#include <glfw3.h>

//glm
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>

//clases para dar orden y limpieza al código
#include"Mesh.h"
#include"Shader.h"
#include"Window.h"

//Dimensiones de la ventana
const float toRadians = 3.14159265f / 180.0; //grados a radianes
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<MeshColor*> meshColorList;
std::vector<Shader>shaderList;

//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";

//shaders nuevos se crearían acá
static const char* fShaderRojo = "shaders/shaderRojo.frag";
static const char* fShaderAzul = "shaders/shaderAzul.frag";
static const char* fShaderCafe = "shaders/shaderCafe.frag";
static const char* fShaderVerde = "shaders/shaderVerde.frag";
static const char* fShaderVerdeClaro = "shaders/shaderVerdeClaro.frag";

float angulo = 0.0f;

//color café en RGB : 0.478, 0.255, 0.067

//Pirámide triangular regular
void CreaPiramide()
{
	unsigned int indices[] = {
		0,1,2,
		1,3,2,
		3,0,2,
		1,0,3

	};
	GLfloat vertices[] = {
		-0.5f, -0.5f,0.0f,	//0
		0.5f,-0.5f,0.0f,	//1
		0.0f,0.5f, -0.25f,	//2
		0.0f,-0.5f,-0.5f,	//3

	};
	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);
}

//Vértices de un cubo
void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	GLfloat cubo_vertices[] = {
		// front
		-0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		// back
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f
	};
	Mesh* cubo = new Mesh();
	cubo->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
	meshList.push_back(cubo);
}

void CrearLetrasyFiguras()
{
	GLfloat t_vertices[] = {
	//	  X		Y	  Z		       	 R		 G		 B
		-0.8f, 0.4f, 0.0f,			0.5f,	0.1f,	0.1f,
		-0.3f, 0.4f, 0.0f, 			0.5f,	0.1f,	0.1f, // Triangulo 1
		-0.8f, 0.3f, 0.0f,			0.5f,	0.1f,	0.1f,

		-0.3f, 0.4f, 0.0f,			0.5f,	0.1f,	0.1f,
		-0.8f, 0.3f, 0.0f,			0.5f,	0.1f,	0.1f,
		-0.3f, 0.3f, 0.0f, 			0.5f,	0.1f,	0.1f,// Triangulo 2

		-0.6f, 0.3f, 0.0f,			0.5f,	0.1f,	0.1f,
		-0.6f,-0.2f, 0.0f,			0.5f,	0.1f,	0.1f,
		-0.5f, 0.3f, 0.0f, 			0.5f,	0.1f,	0.1f,// Triangulo 3

		-0.6f,-0.2f, 0.0f,			0.5f,	0.1f,	0.1f,
		-0.5f, 0.3f, 0.0f,			0.5f,	0.1f,	0.1f,
		-0.5f,-0.2f, 0.0f, 			0.5f,	0.1f,	0.1f,// Triangulo 4 para la T

		-0.1f, 0.3f, 0.0f,			0.0f,	0.7f,	0.3f,
		-0.1f, 0.4f, 0.0f,			0.0f,	0.7f,	0.3f,
		 0.3f, 0.4f, 0.0f,			0.0f,	0.7f,	0.3f, // Triangulo 5

		-0.1f, 0.3f, 0.0f,			0.0f,	0.7f,	0.3f,
		 0.3f, 0.4f, 0.0f,			0.0f,	0.7f,	0.3f,
		 0.3f, 0.3f, 0.0f, 			0.0f,	0.7f,	0.3f,// Triangulo 6

		-0.1f, 0.3f, 0.0f,			0.0f,	0.7f,	0.3f,
		-0.1f,-0.2f, 0.0f,			0.0f,	0.7f,	0.3f,
		 0.0f,-0.2f, 0.0f,			0.0f,	0.7f,	0.3f, // Triaungulo 7

		 0.0f,-0.2f, 0.0f,			0.0f,	0.7f,	0.3f,
		-0.1f, 0.3f, 0.0f,			0.0f,	0.7f,	0.3f,
		 0.0f, 0.4f, 0.0f, 			0.0f,	0.7f,	0.3f,// Trianugulo 8

		 0.0f,-0.2f, 0.0f,			0.0f,	0.7f,	0.3f,
		 0.0f,-0.1f, 0.0f,			0.0f,	0.7f,	0.3f,
		 0.3f,-0.1f, 0.0f,			0.0f,	0.7f,	0.3f, // Triangulo 9

		 0.0f,-0.2f, 0.0f,			0.0f,	0.7f,	0.3f,
		 0.3f,-0.1f, 0.0f,			0.0f,	0.7f,	0.3f,
		 0.3f,-0.2f, 0.0f,			0.0f,	0.7f,	0.3f, // Triangulo 10

		 0.3f,-0.1f, 0.0f,			0.0f,	0.7f,	0.3f,
		 0.2f,-0.1f, 0.0f,			0.0f,	0.7f,	0.3f,
		 0.2f, 0.1f, 0.0f,			0.0f,	0.7f,	0.3f, // Triangulo 11

		 0.2f, 0.1f, 0.0f,			0.0f,	0.7f,	0.3f,
		 0.3f,-0.1f, 0.0f,			0.0f,	0.7f,	0.3f,
		 0.3f, 0.1f, 0.0f,			0.0f,	0.7f,	0.3f, // Triangulo 12

		 0.2f, 0.1f, 0.0f,			0.0f,	0.7f,	0.3f,
		 0.1f, 0.1f, 0.0f,			0.0f,	0.7f,	0.3f,
		 0.1f, 0.0f, 0.0f,			0.0f,	0.7f,	0.3f, // Triangulo 13

		 0.2f, 0.1f, 0.0f,			0.0f,	0.7f,	0.3f,
		 0.2f, 0.0f, 0.0f,			0.0f,	0.7f,	0.3f,
		 0.1f, 0.0f, 0.0f,			0.0f,	0.7f,	0.3f, // Triangulo 14 Para la G

		 0.5f,-0.2f, 0.0f,			0.2f,	0.2f,	0.6f,
		 0.5f, 0.3f, 0.0f,			0.2f,	0.2f,	0.6f,
		 0.6f,-0.2f, 0.0f,			0.2f,	0.2f,	0.6f, // Triangulo 15

		 0.6f,-0.2f, 0.0f,			0.2f,	0.2f,	0.6f,
		 0.6f, 0.3f, 0.0f,			0.2f,	0.2f,	0.6f,
		 0.5f, 0.3f, 0.0f,			0.2f,	0.2f,	0.6f, // Triangulo 16

		 0.5f, 0.3f, 0.0f,			0.2f,	0.2f,	0.6f,
		 0.5f, 0.4f, 0.0f,			0.2f,	0.2f,	0.6f,
		 0.7f, 0.4f, 0.0f, 			0.2f,	0.2f,	0.6f,// Triangulo 17

		 0.7f, 0.4f, 0.0f,			0.2f,	0.2f,	0.6f,
		 0.7f, 0.3f, 0.0f,			0.2f,	0.2f,	0.6f,
		 0.5f, 0.3f, 0.0f,			0.2f,	0.2f,	0.6f, // Triangulo 18

		 0.7f, 0.4f, 0.0f,			0.2f,	0.2f,	0.6f,
		 0.8f, 0.4f, 0.0f,			0.2f,	0.2f,	0.6f,
		 0.8f,-0.2f, 0.0f,			0.2f,	0.2f,	0.6f, // Triangulo 19

		 0.7f, 0.4f, 0.0f,			0.2f,	0.2f,	0.6f,
		 0.7f,-0.2f, 0.0f,			0.2f,	0.2f,	0.6f,
		 0.8f,-0.2f, 0.0f,			0.2f,	0.2f,	0.6f, // Triangulo 20

		 0.6f, 0.0f, 0.0f,			0.2f,	0.2f,	0.6f,
		 0.6f, 0.1f, 0.0f,			0.2f,	0.2f,	0.6f,
		 0.7f, 0.1f, 0.0f,			0.2f,	0.2f,	0.6f, // Triaungulo 21

		 0.6f, 0.0f, 0.0f,			0.2f,	0.2f,	0.6f,
		 0.7f, 0.0f, 0.0f,			0.2f,	0.2f,	0.6f,
		 0.7f, 0.1f, 0.0f,			0.2f,	0.2f,	0.6f, // Triangulo 22 para la A
	};

	MeshColor* test = new MeshColor();
	test->CreateMeshColor(t_vertices, 396); // vertices = (9vertices+9colores)x22triangulos
	meshColorList.push_back(test);
}


void CreateShaders()
{
	Shader* shaderRojo = new Shader(); // Shader pos 0
	shaderRojo->CreateFromFiles(vShader, fShaderRojo);
	shaderList.push_back(*shaderRojo); 

	Shader* shaderVerdeClaro = new Shader(); // Shader pos 1
	shaderVerdeClaro->CreateFromFiles(vShader, fShaderVerdeClaro);
	shaderList.push_back(*shaderVerdeClaro);

	Shader* shaderAzul = new Shader(); // Shader pos 2
	shaderAzul->CreateFromFiles(vShader, fShaderAzul);
	shaderList.push_back(*shaderAzul);

	Shader* shaderCafe = new Shader(); // Shader pos 3
	shaderCafe->CreateFromFiles(vShader, fShaderCafe);
	shaderList.push_back(*shaderCafe);

	Shader* shaderVerdeOscuro = new Shader(); // Shader pos 4
	shaderVerdeOscuro->CreateFromFiles(vShader, fShaderVerde);
	shaderList.push_back(*shaderVerdeOscuro);
	
	Shader* shader2 = new Shader();//shader para usar color como parte del VAO: letras // Shader pos 5
	shader2->CreateFromFiles(vShaderColor, fShaderColor);
	shaderList.push_back(*shader2);
}



int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialise();

			// ----- SECCIÓN PARA GUARDAR LOS VERTICES EN EL MESHCOLORLIST
	/*
	CrearLetrasyFiguras(); //usa MeshColor, índices en MeshColorList
	*/

	// --- Se llaman a las funciones para llenar el MeshList
	CreaPiramide(); //índice 0 en MeshList
	CrearCubo();	//índice 1 en MeshList
	
	// --- Se Crean los Shaders para la casa y las letras
	CreateShaders();

	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;


	//Projection: Matriz de Dimensión 4x4 para indicar si vemos en 2D( orthogonal) o en 3D) perspectiva
	glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
	//glm::mat4 projection = glm::perspective(glm::radians(60.0f)	,mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);


	//Model: Matriz de Dimensión 4x4 en la cual se almacena la multiplicación de las transformaciones geométricas.
	glm::mat4 model(1.0); //fuera del while se usa para inicializar la matriz con una identidad

	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad


							//---------- SECCIÓN PARA CARGAR LOS SHADERS DE LAS LETRAS -------------//
		/*
					//------- Para las letras hay que usar el -sexto- set de shaders con índice 5 en ShaderList
		//shaderList[5].useShader();
		//uniformModel = shaderList[5].getModelLocation();
		//uniformProjection = shaderList[5].getProjectLocation();

					// --------------------------------------------------------------------------------
		*/


		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));


										//---------- SECCIÓN PARA RENDERIZAR LAS LETRAS -------------//
		/*
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[0]->RenderMeshColor();
		*/
									//------------------------------------------------------------		
		


		//				-------------------- SECCI[ON PARA CASA CON INSTANCIAS 3D -----------------------------
		
		// Paredes 
		shaderList[0].useShader(); // Rojo
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -0.3f, -3.0f));
		model = glm::scale(model, glm::vec3(1.0f, 1.3f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh(); // cubo

		// Techo 
		shaderList[2].useShader(); // Azul
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.678f, -2.5f));
		model = glm::scale(model, glm::vec3(1.25f, 0.65f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh(); // pirámide


		// Puerta y ventanas
		shaderList[1].useShader(); // Verde Claro
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -0.67f, -2.5f));
		model = glm::scale(model, glm::vec3(0.25f, 0.55f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh(); // cubo 
		
		//ventana 1
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.25f, 0.15f, -2.2f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh(); // cubo 

		//Ventana 2
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.25f, 0.15f, -2.2f));
		model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh(); // cubo 

		// ------Arboles-------
		// Tronco izquierda:
		shaderList[3].useShader(); // Verde Claro
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.8f, -0.85f, -2.1f));
		model = glm::scale(model, glm::vec3(0.12f, 0.2f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh(); // cubo 

		// Tronco Derecha:
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.8f, -0.85f, -2.1f));
		model = glm::scale(model, glm::vec3(0.12f, 0.2f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh(); // cubo 

		// arbustos:
		// izquierdo
		shaderList[4].useShader(); // Verde Oscuro
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(-0.8f, -0.5f, -2.0f));
		model = glm::scale(model, glm::vec3(0.26f, 0.5f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh(); // piramide 

		//derecho
		model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.8f, -0.5f, -2.0f));
		model = glm::scale(model, glm::vec3(0.26f, 0.5f, 0.1f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh(); // piramide 
		//
		glUseProgram(0);
		mainWindow.swapBuffers();
	}
	return 0;
}
// inicializar matriz: glm::mat4 model(1.0);
// reestablecer matriz: model = glm::mat4(1.0);
//Traslación
//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
//////////////// ROTACIÓN //////////////////
//model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
////////////////  ESCALA ////////////////
//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
///////////////////// T+R////////////////
/*model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
*/
/////////////R+T//////////
/*model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
*/