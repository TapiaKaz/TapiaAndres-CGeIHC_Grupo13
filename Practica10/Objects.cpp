#include "Objects.h"

Objects::Objects()
{
    // Constructor vacío
}

Objects::~Objects()
{
    // Destructor vacío (OpenGL limpia automáticamente)
}

void Objects::LoadTextures()
{
    // Cargar texturas básicas
    brickTexture = Texture("Textures/brick.png");
    brickTexture.LoadTextureA();

    dirtTexture = Texture("Textures/dirt.png");
    dirtTexture.LoadTextureA();

    plainTexture = Texture("Textures/plain.png");
    plainTexture.LoadTextureA();

    // Textura del piso (usa la que tengas activa)
    pisoTexture = Texture("Textures/pisomadera.png");
    pisoTexture.LoadTextureA();

    // Cargar texturas de Navi
    NaviTextureA = Texture("Texture/fairy_navi_baseColor");
    NaviTextureA.LoadTextureA();

    NaviTextureB = Texture("Texture/fairy_wings_baseColor");
    NaviTextureB.LoadTextureA();
}

void Objects::LoadModels()
{
    // Cargar modelo de Navi
    Navi = Model();
    Navi.LoadModel("Models/Navi.obj");

    // Cargar modelo de la Lampara
    Lamp = Model();
    Lamp.LoadModel("Models/Lamp.obj");

	// Cargar modelo de la Choza
	Choza = Model();
	Choza.LoadModel("Models/Choza.obj");

    // Cargar Modelos de Deku Link

	DekuBase = Model();
	DekuBase.LoadModel("Models/DekuLink/DekuBase.obj");

	DekuBrazo = Model();
	DekuBrazo.LoadModel("Models/DekuLink/DekuBrazo.obj");

	DekuPierna = Model();
	DekuPierna.LoadModel("Models/DekuLink/DekuPierna.obj");

    // Cargar Luna
	Luna = Model();
	Luna.LoadModel("Models/Luna.obj");

    // Cargar hombre de las mascaras:
    Salesman = Model();
	Salesman.LoadModel("Models/Salesman.obj");

    // Cargar Piramide
    Piramide = Model();
	Piramide.LoadModel("Models/Piramide.obj");

	// Cargar Reloj
	Reloj = Model();
	Reloj.LoadModel("Models/Reloj.obj");

	// Cargar Ring
	Ring = Model();
	Ring.LoadModel("Models/Ring.obj");

	// Cargar SkullKid
	SkullKid = Model();
	SkullKid.LoadModel("Models/SkullKid.obj");

    // Cargar Paredes
    ParedUno = Model();
	ParedUno.LoadModel("Models/Paredes/ParedUno.obj");

	ParedDos = Model();
	ParedDos.LoadModel("Models/Paredes/ParedDos.obj");
}   

void Objects::LoadAll()
{
    LoadTextures();
    LoadModels();
}