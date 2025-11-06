#pragma once

#include <vector>
#include "Texture.h"
#include "Model.h"

class Objects
{
public:
    // Texturas
    Texture brickTexture;
    Texture dirtTexture;
    Texture plainTexture;
    Texture pisoTexture;
    Texture NaviTextureA;
    Texture NaviTextureB;

    // Modelos
    Model Navi;
    Model Lamp;
    Model Choza;
        
        // Modelo de Deku
    Model DekuBase;
    Model DekuBrazo;
	Model DekuPierna;

    Model Luna;
    Model Salesman;
    Model Piramide;
    Model Reloj;
    Model Ring;
    Model SkullKid;

    // Paredes
    Model ParedUno;
	Model ParedDos;


    Objects();
    ~Objects();

    // Métodos para cargar recursos
    void LoadTextures();
    void LoadModels();
    void LoadAll(); // Carga todo de una vez
};