#include "Render.h"

void RenderFloor(GLuint uniformModel, GLuint uniformColor, GLuint uniformSpecularIntensity,
    GLuint uniformShininess, Objects& objects, Material& material,
    std::vector<Mesh*>& meshList)
{
    glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
    glm::mat4 model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(30.0f, 1.0f, 50.0f));

    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    glUniform3fv(uniformColor, 1, glm::value_ptr(color));

    objects.pisoTexture.UseTexture();
    material.UseMaterial(uniformSpecularIntensity, uniformShininess);
    meshList[2]->RenderMesh();
}

void RenderLampara(GLuint uniformModel, Objects& objects, glm::vec3 position)
{
    glm::mat4 model = glm::mat4(1.0);
    model = glm::translate(model, position);
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.Lamp.RenderModel();
}

void RenderChoza(GLuint uniformModel, Objects& objects, glm::vec3 position)
{
    glm::mat4 model = glm::mat4(1.0);
    model = glm::translate(model, position);
    model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.Choza.RenderModel();
}

void RenderDekuLink(GLuint uniformModel, Objects& objects, glm::vec3 position,
    float rotation, float armSwing, float legSwing)
{
    glm::vec3 scale = glm::vec3(0.15f, 0.15f, 0.15f);

    // CUERPO BASE
    glm::mat4 model = glm::mat4(1.0);
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, scale);
    glm::mat4 modelBase = model;

    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.DekuBase.RenderModel();

    // BRAZO DERECHO
    model = modelBase;
    model = glm::translate(model, glm::vec3(-2.0f, 12.0f, 0.0f));
    model = glm::rotate(model, glm::radians(armSwing), glm::vec3(1.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.DekuBrazo.RenderModel();

    // BRAZO IZQUIERDO
    model = modelBase;
    model = glm::translate(model, glm::vec3(2.0f, 12.0f, 0.0f));
    model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(-armSwing), glm::vec3(1.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.DekuBrazo.RenderModel();

    // PIERNA DERECHA
    model = modelBase;
    model = glm::rotate(model, glm::radians(legSwing), glm::vec3(1.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.DekuPierna.RenderModel();

    // PIERNA IZQUIERDA
    model = modelBase;
    model = glm::translate(model, glm::vec3(-4.75f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(-legSwing), glm::vec3(1.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.DekuPierna.RenderModel();
}

void RenderLuna(GLuint uniformModel, Objects& objects, glm::vec3 position)
{
    glm::mat4 model = glm::mat4(1.0);
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(135.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(0.02f, 0.02f, 0.02f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.Luna.RenderModel();
}

void RenderPiramide(GLuint uniformModel, Objects& objects, glm::vec3 position)
{
    glm::mat4 model = glm::mat4(1.0);
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(3.0f, 2.8f, 3.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.Piramide.RenderModel();
}

void RenderReloj(GLuint uniformModel, Objects& objects, glm::vec3 position)
{
    glm::mat4 model = glm::mat4(1.0);
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(550.0f, 450.0f, 550.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.Reloj.RenderModel();
}

void RenderRing(GLuint uniformModel, Objects& objects, glm::vec3 position)
{
    glm::mat4 model = glm::mat4(1.0);
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(2.5f, 2.0f, 2.5f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.Ring.RenderModel();
}
// Render Paredes

void RenderParedes(GLuint uniformModel, Objects& objects)
{
    glm::mat4 model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(100.0f,-5.0f,0.0f));
    model = glm::scale(model, glm::vec3(100.1f, 50.1f, 100.1f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.ParedUno.RenderModel();

    model = glm::mat4(1.0);
    model = glm::translate(model, glm::vec3(-100.0f, -5.0f, 0.0f));
    model = glm::scale(model, glm::vec3(100.1f, 50.1f, 100.1f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.ParedUno.RenderModel();
}
// NPCs
void RenderSalesMan(GLuint uniformModel, Objects& objects, glm::vec3 position)
{
    glm::mat4 model = glm::mat4(1.0);
    model = glm::translate(model, position);
	model = glm::rotate(model, glm::radians(215.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.1f, 0.1f, 0.1f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.Salesman.RenderModel();
}

void RenderSkullKid(GLuint uniformModel, Objects& objects, glm::vec3 position)
{
    glm::mat4 model = glm::mat4(1.0);
    model = glm::translate(model, position);
	model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.002f, 0.002f, 0.002f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.SkullKid.RenderModel();
}

void RenderNavi(GLuint uniformModel, Objects& objects, glm::vec3 position, glm::vec3 rotation)
{
    glm::mat4 model = glm::mat4(1.0);
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
    glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
    objects.Navi.RenderModel();
}