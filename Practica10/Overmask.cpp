#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include "Model.h"
#include "Skybox.h"
#include "Objects.h"
#include "Render.h"  

#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"

const float toRadians = 3.14159265f / 180.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;
Objects objects;
Skybox skybox;

Material Material_brillante;
Material Material_opaco;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

DirectionalLight mainLight;
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

static const char* vShader = "shaders/shader_light.vert";
static const char* fShader = "shaders/shader_light.frag";

//función para teclado de keyframes 
void inputKeyframes(bool* keys);

//variables para keyframes
float reproduciranimacion, habilitaranimacion, guardoFrame, reinicioFrame, ciclo, ciclo2, contador = 0;

void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
    unsigned int vLength, unsigned int normalOffset)
{
    for (size_t i = 0; i < indiceCount; i += 3)
    {
        unsigned int in0 = indices[i] * vLength;
        unsigned int in1 = indices[i + 1] * vLength;
        unsigned int in2 = indices[i + 2] * vLength;
        glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
        glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
        glm::vec3 normal = glm::cross(v1, v2);
        normal = glm::normalize(normal);

        in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
        vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
        vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
        vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
    }

    for (size_t i = 0; i < verticeCount / vLength; i++)
    {
        unsigned int nOffset = i * vLength + normalOffset;
        glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
        vec = glm::normalize(vec);
        vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
    }
}

void CreateObjects()
{
    unsigned int indices[] = {
        0, 3, 1,
        1, 3, 2,
        2, 3, 0,
        0, 1, 2
    };

    GLfloat vertices[] = {
        -1.0f, -1.0f, -0.6f,    0.0f, 0.0f,     0.0f, 0.0f, 0.0f,
        0.0f, -1.0f, 1.0f,      0.5f, 0.0f,     0.0f, 0.0f, 0.0f,
        1.0f, -1.0f, -0.6f,     1.0f, 0.0f,     0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,       0.5f, 1.0f,     0.0f, 0.0f, 0.0f
    };

    unsigned int floorIndices[] = {
        0, 2, 1,
        1, 2, 3
    };

    GLfloat floorVertices[] = {
        -10.0f, 0.0f, -10.0f,   0.0f, 0.0f,     0.0f, -1.0f, 0.0f,
        10.0f, 0.0f, -10.0f,    10.0f, 0.0f,    0.0f, -1.0f, 0.0f,
        -10.0f, 0.0f, 10.0f,    0.0f, 10.0f,    0.0f, -1.0f, 0.0f,
        10.0f, 0.0f, 10.0f,     10.0f, 10.0f,   0.0f, -1.0f, 0.0f
    };

    unsigned int vegetacionIndices[] = {
       0, 1, 2,
       0, 2, 3,
       4,5,6,
       4,6,7
    };

    GLfloat vegetacionVertices[] = {
        -0.5f, -0.5f, 0.0f,     0.0f, 0.0f,     0.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f,      1.0f, 0.0f,     0.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.0f,       1.0f, 1.0f,     0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.0f,      0.0f, 1.0f,     0.0f, 0.0f, 0.0f,

        0.0f, -0.5f, -0.5f,     0.0f, 0.0f,     0.0f, 0.0f, 0.0f,
        0.0f, -0.5f, 0.5f,      1.0f, 0.0f,     0.0f, 0.0f, 0.0f,
        0.0f, 0.5f, 0.5f,       1.0f, 1.0f,     0.0f, 0.0f, 0.0f,
        0.0f, 0.5f, -0.5f,      0.0f, 1.0f,     0.0f, 0.0f, 0.0f,
    };

    Mesh* obj1 = new Mesh();
    obj1->CreateMesh(vertices, indices, 32, 12);
    meshList.push_back(obj1);

    Mesh* obj2 = new Mesh();
    obj2->CreateMesh(vertices, indices, 32, 12);
    meshList.push_back(obj2);

    Mesh* obj3 = new Mesh();
    obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
    meshList.push_back(obj3);

    Mesh* obj4 = new Mesh();
    obj4->CreateMesh(vegetacionVertices, vegetacionIndices, 64, 12);
    meshList.push_back(obj4);

    calcAverageNormals(indices, 12, vertices, 32, 8, 5);
    calcAverageNormals(vegetacionIndices, 12, vegetacionVertices, 64, 8, 5);
}

void CreateShaders()
{
    Shader* shader1 = new Shader();
    shader1->CreateFromFiles(vShader, fShader);
    shaderList.push_back(*shader1);
}

/////////////////////////////// KEYFRAMES NAVI /////////////////////

bool animacion = false;

// Variables de Navi
float movNavi_x = 0.0f, movNavi_y = 2.5f, movNavi_z = 0.0f;
float giroNavi = 0.0f;

#define MAX_FRAMES 100
int i_max_steps = 100;
int i_curr_steps = 0;

typedef struct _frame
{
    float movNavi_x;
    float movNavi_y;
    float movNavi_z;
    float movNavi_xInc;
    float movNavi_yInc;
    float movNavi_zInc;
    float giroNavi;
    float giroNaviInc;
} FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 0;
bool play = false;
int playIndex = 0;

// Guardar un Keyframe
void saveFrame(void)
{
    printf("GUARDANDO KEYFRAME[%d]\n", FrameIndex);

    KeyFrame[FrameIndex].movNavi_x = movNavi_x;
    KeyFrame[FrameIndex].movNavi_y = movNavi_y;
    KeyFrame[FrameIndex].movNavi_z = movNavi_z;
    KeyFrame[FrameIndex].giroNavi = giroNavi;

    std::ofstream archivo("keyframes.txt", std::ios::app);
    if (archivo.is_open())
    {
        archivo << "KeyFrame[" << FrameIndex << "]: ";
        archivo << "movNavi_x=" << movNavi_x << ", ";
        archivo << "movNavi_y=" << movNavi_y << ", ";
        archivo << "movNavi_z=" << movNavi_z << ", ";
        archivo << "giroNavi=" << giroNavi << "\n";
        archivo.close();
        printf("✓ Frame guardado en 'keyframes.txt'\n");
    }
    else
    {
        printf("✗ ERROR: No se pudo abrir el archivo\n");
    }

    FrameIndex++;
}

// Reiniciar Navi al primer frame
void resetElements(void)
{
    movNavi_x = KeyFrame[0].movNavi_x;
    movNavi_y = KeyFrame[0].movNavi_y;
    movNavi_z = KeyFrame[0].movNavi_z;
    giroNavi = KeyFrame[0].giroNavi;
}

// Calcular interpolación entre frames
void interpolation(void)
{
    KeyFrame[playIndex].movNavi_xInc = (KeyFrame[playIndex + 1].movNavi_x - KeyFrame[playIndex].movNavi_x) / i_max_steps;
    KeyFrame[playIndex].movNavi_yInc = (KeyFrame[playIndex + 1].movNavi_y - KeyFrame[playIndex].movNavi_y) / i_max_steps;
    KeyFrame[playIndex].movNavi_zInc = (KeyFrame[playIndex + 1].movNavi_z - KeyFrame[playIndex].movNavi_z) / i_max_steps;
    KeyFrame[playIndex].giroNaviInc = (KeyFrame[playIndex + 1].giroNavi - KeyFrame[playIndex].giroNavi) / i_max_steps;
}

// Animar Navi entre keyframes
void animate(void)
{
    if (play)
    {
        if (i_curr_steps >= i_max_steps)
        {
            playIndex++;
            if (playIndex > FrameIndex - 2)
            {
                printf("Animación terminada.\n");
                playIndex = 0;
                play = false;
            }
            else
            {
                i_curr_steps = 0;
                interpolation();
            }
        }
        else
        {
            movNavi_x += KeyFrame[playIndex].movNavi_xInc;
            movNavi_y += KeyFrame[playIndex].movNavi_yInc;
            movNavi_z += KeyFrame[playIndex].movNavi_zInc;
            giroNavi += KeyFrame[playIndex].giroNaviInc;
            i_curr_steps++;
        }
    }
}

///////////////* FIN KEYFRAMES*////////////////////////////

int main()
{
    mainWindow = Window(1366, 768);
    mainWindow.Initialise();

    CreateObjects();
    CreateShaders();

    // Configuración de cámara
    camera = Camera(
        glm::vec3(0.0f, 15.0f, 15.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        -90.0f,
        -30.0f,
        0.3f,
        0.5f
    );
    camera.setThirdPersonMode(true);
    camera.setThirdPersonDistance(15.0f);
    camera.setThirdPersonHeight(5.0f);

    objects.LoadAll();

    // Skybox
    std::vector<std::string> skyboxFaces;
    skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
    skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
    skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
    skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
    skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
    skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");
    skybox = Skybox(skyboxFaces);

    Material_brillante = Material(4.0f, 256);
    Material_opaco = Material(0.3f, 4);

    // Luces
    mainLight = DirectionalLight(1.0f, 1.0f, 1.0f, 0.3f, 0.3f, 0.0f, 0.0f, -1.0f);

    unsigned int pointLightCount = 0;
    pointLights[0] = PointLight(1.0f, 1.0f, 1.0f, 12.5f, 10.0f, 5.0f, 10.0f, -20.0f, 0.5f, 0.5f, 0.1f);
    pointLightCount++;
    pointLights[1] = PointLight(1.0f, 0.0f, 1.0f, 0.1f, 0.1f, -2.0f, 3.0f, 0.0f, 0.0f, 0.0f, 0.03f);
    pointLightCount++;

    unsigned int spotLightCount = 0;

    GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
        uniformSpecularIntensity = 0, uniformShininess = 0;
    GLuint uniformColor = 0;
    glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);

    // Estado del personaje
    glm::vec3 dekuPosition = glm::vec3(0.0f, 0.0f, 0.0f);
    float dekuRotation = 0.0f;
    float dekuSpeed = 1.0f;  

    float walkAnimationTime = 0.0f;
    bool isWalking = false;

    printf(" REPRODUCCIÓN DE ANIMACIÓN\n");
    printf("  [ESPACIO] → Reproducir / Pausar animación de Navi\n");
    printf("  [0]       → Reiniciar animación al primer keyframe\n\n");

    printf(" CREAR Y GUARDAR KEYFRAMES\n");
    printf("  [L] → Guardar keyframe actual (posición y rotación)\n");
    printf("  [P] → Habilitar guardar otro keyframe\n\n");

    printf(" MOVIMIENTO DE Nᴀᴠɪ (ajustar posición manual)\n");
    printf("  Eje X (horizontal):\n");
    printf("     [1] → Mover izquierda (-1.0)\n");
    printf("     [7] → Mover derecha  (+1.0)\n\n");

    printf("  Eje Y (vertical):\n");
    printf("     [3] → Bajar (-1.0)\n");
    printf("     [9] → Subir (+1.0)\n\n");

    printf("  Eje Z (profundidad):\n");
    printf("     [Q] → Mover hacia atrás (-1.0)\n");
    printf("     [E] → Mover hacia adelante (+1.0)\n\n");

    printf("🔹 ROTACIÓN DE Nᴀᴠɪ\n");
    printf("  [5] → Rotar hacia la derecha (+15° en eje Y)\n\n");
    printf("════════════════════════════════════════════════════════\n\n");

    // Loop principal
    while (!mainWindow.getShouldClose())
    {
        GLfloat now = glfwGetTime();
        deltaTime = now - lastTime;
        deltaTime += (now - lastTime) / limitFPS;
        lastTime = now;

        glfwPollEvents();

        //-------Para Keyframes
        inputKeyframes(mainWindow.getsKeys());
        animate();

        // ===== ZOOM CON RUEDA DEL MOUSE =====
        float scrollOffset = mainWindow.getScrollChange();
        if (scrollOffset != 0.0f)
        {
            float currentDistance = camera.getThirdPersonDistance();
            currentDistance -= scrollOffset * 2.0f;

            if (currentDistance < 5.0f) currentDistance = 5.0f;
            if (currentDistance > 30.0f) currentDistance = 30.0f;

            camera.setThirdPersonDistance(currentDistance);
        }

        // ===== MOVIMIENTO DEL PERSONAJE =====
        glm::vec3 movement(0.0f);
        isWalking = false;

        if (mainWindow.isMoving())
        {
            isWalking = true;

            glm::vec3 forward = camera.getCameraDirection();
            forward.y = 0.0f;
            forward = glm::normalize(forward);

            glm::vec3 right = glm::normalize(glm::cross(forward, glm::vec3(0.0f, 1.0f, 0.0f)));

            if (mainWindow.isMovingForward())
                movement += forward;
            if (mainWindow.isMovingBackward())
                movement -= forward;
            if (mainWindow.isMovingRight())
                movement += right;
            if (mainWindow.isMovingLeft())
                movement -= right;

            if (glm::length(movement) > 0.0f)
            {
                movement = glm::normalize(movement);
                dekuPosition += movement * dekuSpeed * deltaTime;
                dekuRotation = glm::degrees(atan2(movement.x, movement.z));
            }
        }

        // ===== ANIMACIÓN DE CAMINATA =====
        if (isWalking)
        {
            walkAnimationTime += deltaTime * 0.1f;  // ⭐ CORREGIDO: velocidad normal
        }

        float armSwing = isWalking ? sin(walkAnimationTime) * 30.0f : 0.0f;
        float legSwing = isWalking ? sin(walkAnimationTime) * 15.0f : 0.0f;

		// Configuración de cámara de link
        camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());
        camera.followTarget(dekuPosition + glm::vec3(0.0f, 2.0f, 0.0f), deltaTime);


        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        skybox.DrawSkybox(camera.calculateViewMatrix(), projection);

        shaderList[0].UseShader();
        uniformModel = shaderList[0].GetModelLocation();
        uniformProjection = shaderList[0].GetProjectionLocation();
        uniformView = shaderList[0].GetViewLocation();
        uniformEyePosition = shaderList[0].GetEyePositionLocation();
        uniformColor = shaderList[0].getColorLocation();
        uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
        uniformShininess = shaderList[0].GetShininessLocation();

        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
        glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

        glm::vec3 lowerLight = camera.getCameraPosition();
        lowerLight.y -= 0.3f;
        spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());

        shaderList[0].SetDirectionalLight(&mainLight);
        shaderList[0].SetPointLights(pointLights, pointLightCount);
        shaderList[0].SetSpotLights(spotLights, spotLightCount);

        
        // piso
        RenderFloor(uniformModel, uniformColor, uniformSpecularIntensity,
            uniformShininess, objects, Material_opaco, meshList);

        // Control luz Navi
        if (!mainWindow.getEstadoNavi()) {
            pointLights[1].setEstado(false);
        }
        else {
            pointLights[1].changeColor(1.0f, 0.0f, 1.0f);
            pointLights[1].setEstado(true);
        }

        RenderLampara(uniformModel, objects);
        RenderChoza(uniformModel, objects);
        RenderSalesMan(uniformModel, objects);
        RenderPiramide(uniformModel, objects);
        RenderReloj(uniformModel, objects);
        RenderRing(uniformModel, objects);
        RenderSkullKid(uniformModel, objects);
        RenderDekuLink(uniformModel, objects, dekuPosition, dekuRotation, armSwing, legSwing);
        RenderLuna(uniformModel, objects);
		RenderParedes(uniformModel, objects);

        //RenderNavi(uniformModel, objects, glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,0.0f,0.0f));
		                                        // Traslación              // Rotación
        
        glm::vec3 naviPos(
            movNavi_x + cos(glm::radians(giroNavi)) * 5.0f,
            movNavi_y + sin(glfwGetTime() * 3.0f) * 0.5f, // leve oscilación
            movNavi_z + sin(glm::radians(giroNavi)) * 5.0f
        );

        RenderNavi(uniformModel, objects, naviPos, glm::vec3(0.0f, giroNavi, 0.0f));

        glDisable(GL_BLEND);
        glUseProgram(0);
        mainWindow.swapBuffers();
    }
    return 0;
}

void inputKeyframes(bool* keys)
{
    static bool keyLock = false;  // Previene múltiples lecturas con una sola pulsación

    // ======== REPRODUCIR ANIMACIÓN ========
    if (keys[GLFW_KEY_SPACE] && !keyLock)
    {
        if (!play && FrameIndex > 1)
        {
            resetElements();
            interpolation();
            play = true;
            playIndex = 0;
            i_curr_steps = 0;
            printf("▶ Reproduciendo animación de Navi...\n");
        }
        else if (play)
        {
            play = false;
            printf("⏸ Animación pausada.\n");
        }
        keyLock = true;
    }

    // ======== REINICIAR ANIMACIÓN ========
    if (keys[GLFW_KEY_0] && !keyLock)
    {
        resetElements();
        play = false;
        playIndex = 0;
        printf("🔁 Navi reiniciada al primer keyframe.\n");
        keyLock = true;
    }

    // ======== GUARDAR Y HABILITAR NUEVO FRAME ========
    static bool guardado = false;

    if (keys[GLFW_KEY_L] && !keyLock && !guardado)
    {
        saveFrame();
        guardado = true;
        printf(" Frame guardado. Presiona [P] para habilitar otro.\n");
        keyLock = true;
    }
    if (keys[GLFW_KEY_P] && !keyLock)
    {
        guardado = false;
        printf(" Guardado habilitado nuevamente.\n");
        keyLock = true;
    }

    // ======== MOVIMIENTOS DE NAVI ========
    // X (horizontal)
    if (keys[GLFW_KEY_1] && !keyLock)
    {
        movNavi_x -= 1.0f;
        printf("⬅ Navi X -1 → %.2f\n", movNavi_x);
        keyLock = true;
    }
    if (keys[GLFW_KEY_7] && !keyLock)
    {
        movNavi_x += 1.0f;
        printf("➡ Navi X +1 → %.2f\n", movNavi_x);
        keyLock = true;
    }

    // Y (vertical)
    if (keys[GLFW_KEY_3] && !keyLock)
    {
        movNavi_y -= 1.0f;
        printf("⬇ Navi Y -1 → %.2f\n", movNavi_y);
        keyLock = true;
    }
    if (keys[GLFW_KEY_9] && !keyLock)
    {
        movNavi_y += 1.0f;
        printf("⬆ Navi Y +1 → %.2f\n", movNavi_y);
        keyLock = true;
    }

    // Z (profundidad)
    if (keys[GLFW_KEY_Q] && !keyLock)
    {
        movNavi_z -= 1.0f;
        printf("↩ Navi Z -1 → %.2f\n", movNavi_z);
        keyLock = true;
    }
    if (keys[GLFW_KEY_E] && !keyLock)
    {
        movNavi_z += 1.0f;
        printf("↪ Navi Z +1 → %.2f\n", movNavi_z);
        keyLock = true;
    }

    // Rotacion (y)
    if (keys[GLFW_KEY_5] && !keyLock)
    {
        giroNavi += 15.0f;
        if (giroNavi >= 360.0f) giroNavi -= 360.0f;
        printf(" Navi rotación: %.2f°\n", giroNavi);
        keyLock = true;
    }

    // ======== DESBLOQUEO ========
    if (!keys[GLFW_KEY_SPACE] && !keys[GLFW_KEY_0] &&
        !keys[GLFW_KEY_L] && !keys[GLFW_KEY_P] &&
        !keys[GLFW_KEY_1] && !keys[GLFW_KEY_7] &&
        !keys[GLFW_KEY_3] && !keys[GLFW_KEY_9] &&
        !keys[GLFW_KEY_Q] && !keys[GLFW_KEY_E] &&
        !keys[GLFW_KEY_5])
    {
        keyLock = false;
    }
}

//////////////////////////// FIN KEYFRAMES NAVI /////////////////////