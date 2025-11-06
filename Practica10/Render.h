#pragma once

#include <glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <vector>

#include "Objects.h"
#include "Material.h"
#include "Mesh.h"

void RenderDekuLink(GLuint uniformModel, Objects& objects,
    glm::vec3 position = glm::vec3(-5.0f, 0.0f, 0.0f),
    float rotation = 0.0f,
    float armSwing = 0.0f,
    float legSwing = 0.0f);

void RenderLuna(GLuint uniformModel, Objects& objects,
    glm::vec3 position = glm::vec3(-0.0f, 150.0f, 250.0f));


void RenderPiramide(GLuint uniformModel, Objects& objects,
    glm::vec3 position = glm::vec3(-0.0f, 0.0f, 500.0f));

void RenderReloj(GLuint uniformModel, Objects& objects,
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 300.0f));

void RenderRing(GLuint uniformModel, Objects& objects,
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 100.0f));

// NPCs
void RenderSalesMan(GLuint uniformModel, Objects& objects,
    glm::vec3 position = glm::vec3(8.0f, 4.5f, 110.0f));

void RenderSkullKid(GLuint uniformModel, Objects& objects,
    glm::vec3 position = glm::vec3(-10.0f, 4.5f, 90.0f));

void RenderNavi(GLuint uniformModel, Objects& objects,
    glm::vec3 position, glm::vec3 rotation);

// Entorno
void RenderParedes(GLuint uniformModel, Objects& objects);

void RenderFloor(GLuint uniformModel, GLuint uniformColor, GLuint uniformSpecularIntensity,
    GLuint uniformShininess, Objects& objects, Material& material,
    std::vector<Mesh*>& meshList);

void RenderLampara(GLuint uniformModel, Objects& objects,
    glm::vec3 position = glm::vec3(5.0f, -1.0f, -20.0f));

void RenderChoza(GLuint uniformModel, Objects& objects,
    glm::vec3 position = glm::vec3(65.0f, 0.0f, 0.0f));
