#define _USE_MATH_DEFINES
#include <cmath>
//glew include
#include <GL/glew.h>

//std includes
#include <string>
#include <iostream>

//glfw include
#include <GLFW/glfw3.h>

// program include
#include "Headers/TimeManager.h"

// Shader include
#include "Headers/Shader.h"

// Model geometric includes
#include "Headers/Sphere.h"
#include "Headers/Cylinder.h"
#include "Headers/Box.h"
#include "Headers/FirstPersonCamera.h"

//GLM include
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Headers/Texture.h"

// Include loader Model class
#include "Headers/Model.h"

#include "Headers/AnimationUtils.h"
#include "Headers/Terrain.h"
// Incluye modelos del proyecto
#include "Headers/ModelCharacter.h"
#include "Headers/ModelReward.h"
#include "Headers/GameManager.h"
#include "Headers/World.h"
#include "Headers/ScoreManager.h"

#define ARRAY_SIZE_IN_ELEMENTS(a) (sizeof(a)/sizeof(a[0]))

int screenWidth;
int screenHeight;

GLFWwindow *window;

Shader shader;
//Shader con skybox
Shader shaderSkybox;
//Shader con multiples luces
Shader shaderMulLighting;
//Shader Terrain
Shader shaderTerrain;
// Shader para dibujar un objeto con solo textura
Shader shaderTexture;
//Shader para dibujar el buffer de profunidad
Shader shaderDepth;
// Shader para visualizar el buffer de profundidad
Shader shaderViewDepth;

std::shared_ptr<FirstPersonCamera> camera(new FirstPersonCamera());

Sphere skyboxSphere(20, 20);
Box boxCesped;


Sphere esfera1(10, 10);

int modelSelected=0;
bool enableCountSelected=true;

GLuint skyboxTextureID;
//Shader terreno
GLuint textureTerrainRID;
GLuint textureTerrainGID;
GLuint textureTerrainBID;
GLuint textureTerrainBlendMapID;
GLuint textureCespedID;
// Terrain terrain(-1, -1, 200, 10, "../Textures/heightmap3.png");
Terrain terrain(-1, -1, 200, 10, "../Textures/pista_relieve.png");
//Modelo Proyecto
ModelCharacter minecard("../models/minecart/minecard.fbx");
// ModelReward reward("../models/Minecraft/esmeralda.fbx", glm::vec3(1,1,1));
GameManager gameManager(true);
// ModelObstacle muro_contencion0("../models/Minecraft/andesita.obj", glm::vec3(1,1,1));
//obstaculos
Model modelMuro;
//Model muro_contencion2;

Model obs0;
Model obs1;
Model obs2;
Model obs3;

vector<Model*> obss = {
	&obs0,
	&obs1,
	&obs2,
	&obs3
};
// Trapper
Obstacle aux_obs;
vector<Obstacle> obstacles = { Obstacle(), Obstacle(), Obstacle(), Obstacle() };
Trapper<Obstacle>trapper(obstacles);
bool op = true;
// Terrain
// Terrain terrain(-1, -1, 200, 10, "../Textures/pista_relieve.png");

// GLuint textureCespedID, textureWallID, textureWindowID, textureHighwayID, textureLandingPadID;
// GLuint textureTerrainRID,textureTerrainGID,textureTerrainBID, textureTerrainBlendMapID;
 //GLuint textureInit1ID, textureInit2ID, textureActivaID, textureScreenID;
// GLuint skyboxTextureID;
//Texturas Menu
GLuint textureInit1ID, textureInit2ID, textureInit3ID, textureActivaID,textureScreen1ID, textureScreen2ID, textureScreenID, textureScreen3ID, textureScreen4ID;
bool iniciaPartida = false, presionarOpcion = false, presionarOpcion2 = false;
Box boxIntro;


GLenum types[6] = {
GL_TEXTURE_CUBE_MAP_POSITIVE_X,
GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
GL_TEXTURE_CUBE_MAP_NEGATIVE_Z };

std::string fileNames[6] = { "../Textures/SkyBox/SkyBox_Front.tga",
		"../Textures/SkyBox/SkyBox_Back.tga",
		"../Textures/SkyBox/SkyBox_Top.tga",
		"../Textures/SkyBox/SkyBox_Botton.tga",
		"../Textures/SkyBox/SkyBox_Right.tga",
		"../Textures/SkyBox/SkyBox_Left.tga" };

bool exitApp = false;
int lastMousePosX, offsetX = 0;
int lastMousePosY, offsetY = 0;

ScoreManager scoreManager(-0.75, 0.75);

//bb
glm::mat4 modelMatrixMuro = glm::mat4(1.0f);
//glm::mat4 matrixModelMuro2 = glm::mat4(1.0);

std::vector<glm::vec3> muroPosition ={
	glm::vec3 (4.0f, 0.0f, 5.0f),
	glm::vec3 (4.0f, 0.0f, 3.0f),
	glm::vec3 (4.0f, 0.0f, 1.0f),
	glm::vec3 (4.0f, 0.0f, -1.0f),
	glm::vec3 (4.0f, 0.0f, -3.0f),
	glm::vec3 (4.0f, 0.0f, -5.0f),
	glm::vec3 (4.0f, 0.0f, -7.0f),
	glm::vec3 (4.0f, 0.0f, -9.0f),
	glm::vec3 (4.0f, 0.0f, -11.0f),
	glm::vec3 (4.0f, 0.0f, -13.0f),
	glm::vec3 (4.0f, 0.0f, -15.0f),
	glm::vec3 (4.0f, 0.0f, -17.0f),
	glm::vec3 (4.0f, 0.0f, -19.0f),
	glm::vec3 (4.0f, 0.0f, -21.0f),
	glm::vec3 (4.0f, 0.0f, -23.0f),
	glm::vec3 (4.0f, 0.0f, -25.0f),
	glm::vec3 (4.0f, 0.0f, -27.0f),
	glm::vec3 (4.0f, 0.0f, -29.0f),
	glm::vec3 (4.0f, 0.0f, -31.0f),
	glm::vec3 (4.0f, 0.0f, -33.0f),
	glm::vec3 (4.0f, 0.0f, -35.0f),
	glm::vec3 (4.0f, 0.0f, -37.0f),
	glm::vec3 (4.0f, 0.0f, -39.0f),
	glm::vec3 (4.0f, 0.0f, -41.0f),
	glm::vec3 (4.0f, 0.0f, -43.0f),
	glm::vec3 (4.0f, 0.0f, -45.0f),
	glm::vec3 (4.0f, 0.0f, -47.0f),
	glm::vec3 (4.0f, 0.0f, -49.0f),
	glm::vec3 (4.0f, 0.0f, -51.0f),
	glm::vec3 (4.0f, 0.0f, -53.0f),
	glm::vec3 (4.0f, 0.0f, -55.0f),
	glm::vec3 (4.0f, 0.0f, -57.0f),
	glm::vec3 (4.0f, 0.0f, -59.0f),
	glm::vec3 (4.0f, 0.0f, -61.0f),
	glm::vec3 (4.0f, 0.0f, -63.0f),
	glm::vec3 (4.0f, 0.0f, -65.0f),
	glm::vec3 (4.0f, 0.0f, -67.0f),
	glm::vec3 (4.0f, 0.0f, -69.0f),
	glm::vec3 (4.0f, 0.0f, -71.0f),
	glm::vec3 (4.0f, 0.0f, -73.0f),
	glm::vec3 (4.0f, 0.0f, -75.0f),
	glm::vec3 (4.0f, 0.0f, -77.0f),
	glm::vec3 (4.0f, 0.0f, -79.0f),

	glm::vec3 (-4.0f, 0.0f, 5.0f),
	glm::vec3 (-4.0f, 0.0f, 3.0f),
	glm::vec3 (-4.0f, 0.0f, 1.0f),
	glm::vec3 (-4.0f, 0.0f, -1.0f),
	glm::vec3 (-4.0f, 0.0f, -3.0f),
	glm::vec3 (-4.0f, 0.0f, -5.0f),
	glm::vec3 (-4.0f, 0.0f, -7.0f),
	glm::vec3 (-4.0f, 0.0f, -9.0f),
	glm::vec3 (-4.0f, 0.0f, -11.0f),
	glm::vec3 (-4.0f, 0.0f, -13.0f),
	glm::vec3 (-4.0f, 0.0f, -15.0f),
	glm::vec3 (-4.0f, 0.0f, -17.0f),
	glm::vec3 (-4.0f, 0.0f, -19.0f),
	glm::vec3 (-4.0f, 0.0f, -21.0f),
	glm::vec3 (-4.0f, 0.0f, -23.0f),
	glm::vec3 (-4.0f, 0.0f, -25.0f),
	glm::vec3 (-4.0f, 0.0f, -27.0f),
	glm::vec3 (-4.0f, 0.0f, -29.0f),
	glm::vec3 (-4.0f, 0.0f, -31.0f),
	glm::vec3 (-4.0f, 0.0f, -33.0f),
	glm::vec3 (-4.0f, 0.0f, -35.0f),
	glm::vec3 (-4.0f, 0.0f, -37.0f),
	glm::vec3 (-4.0f, 0.0f, -39.0f),
	glm::vec3 (-4.0f, 0.0f, -41.0f),
	glm::vec3 (-4.0f, 0.0f, -43.0f),
	glm::vec3 (-4.0f, 0.0f, -45.0f),
	glm::vec3 (-4.0f, 0.0f, -47.0f),
	glm::vec3 (-4.0f, 0.0f, -49.0f),
	glm::vec3 (-4.0f, 0.0f, -51.0f),
	glm::vec3 (-4.0f, 0.0f, -53.0f),
	glm::vec3 (-4.0f, 0.0f, -55.0f),
	glm::vec3 (-4.0f, 0.0f, -57.0f),
	glm::vec3 (-4.0f, 0.0f, -59.0f),
	glm::vec3 (-4.0f, 0.0f, -61.0f),
	glm::vec3 (-4.0f, 0.0f, -63.0f),
	glm::vec3 (-4.0f, 0.0f, -65.0f),
	glm::vec3 (-4.0f, 0.0f, -67.0f),
	glm::vec3 (-4.0f, 0.0f, -69.0f),
	glm::vec3 (-4.0f, 0.0f, -71.0f),
	glm::vec3 (-4.0f, 0.0f, -73.0f),
	glm::vec3 (-4.0f, 0.0f, -75.0f),
	glm::vec3 (-4.0f, 0.0f, -77.0f),
	glm::vec3 (-4.0f, 0.0f, -79.0f)
};

double deltaTime;
double currTime, lastTime;

// Se definen todos las funciones.
void reshapeCallback(GLFWwindow *Window, int widthRes, int heightRes);
void keyCallback(GLFWwindow *window, int key, int scancode, int action,
		int mode);
void mouseCallback(GLFWwindow *window, double xpos, double ypos);
void mouseButtonCallback(GLFWwindow *window, int button, int state, int mod);
void init(int width, int height, std::string strTitle, bool bFullScreen);
void destroy();
bool processInput(bool continueApplication = true);

// Implementacion de todas las funciones.
void init(int width, int height, std::string strTitle, bool bFullScreen) {

	if (!glfwInit()) {
		std::cerr << "Failed to initialize GLFW" << std::endl;
		exit(-1);
	}

	screenWidth = width;
	screenHeight = height;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (bFullScreen)
		window = glfwCreateWindow(width, height, strTitle.c_str(),
				glfwGetPrimaryMonitor(), nullptr);
	else
		window = glfwCreateWindow(width, height, strTitle.c_str(), nullptr,
				nullptr);

	if (window == nullptr) {
		std::cerr
				<< "Error to create GLFW window, you can try download the last version of your video card that support OpenGL 3.3+"
				<< std::endl;
		destroy();
		exit(-1);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);

	glfwSetWindowSizeCallback(window, reshapeCallback);
	glfwSetKeyCallback(window, keyCallback);
	glfwSetCursorPosCallback(window, mouseCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Init glew
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err) {
		std::cerr << "Failed to initialize glew" << std::endl;
		exit(-1);
	}

	glViewport(0, 0, screenWidth, screenHeight);
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// Inicialización de los shaders
	shader.initialize("../Shaders/colorShader.vs", "../Shaders/colorShader.fs");
	shaderSkybox.initialize("../Shaders/skyBox.vs", "../Shaders/skyBox.fs");
	shaderMulLighting.initialize("../Shaders/iluminacion_texture_res.vs", "../Shaders/multipleLights.fs");
	shaderTerrain.initialize("../Shaders/terrain.vs", "../Shaders/terrain.fs");
	//Menu
	shaderTexture.initialize("../Shaders/texturizado.vs", "../Shaders/texturizado.fs");
	// Inicializacion de los objetos.
	skyboxSphere.init();
	skyboxSphere.setShader(&shaderSkybox);
	skyboxSphere.setScale(glm::vec3(20.0f, 20.0f, 20.0f));
	//Menu
	boxIntro.init();
	boxIntro.setShader(&shaderTexture);
	boxIntro.setScale(glm::vec3(2.0, 2.0, 1.0));

	//Proyecto minecard
	terrain.init();
	terrain.setShader(&shaderTerrain);
	minecard.LoadModelShader(&shaderMulLighting);
	minecard.setTerrain(terrain);
	minecard.setScale(0.4f);
	// reward.LoadModelShader(&shaderMulLighting);
	// reward.setTerrain(terrain);
	// reward.setScale(1.0f);

	modelMuro.loadModel("../models/muroPiedra/muroPiedraF.obj");
	modelMuro.setShader(&shaderMulLighting);

	// muro_contencion0.setTerrain(terrain);
	// muro_contencion0.setScale(0.5f);
	gameManager.setShader(&shaderMulLighting);
	gameManager.setTerrain(terrain);
	gameManager.add(minecard);
	// gameManager.add(&reward);
	// gameManager.add(muro_contencion0);

	// gameManager.rew1 = new ModelReward("../models/Minecraft/esmeralda.fbx",glm::vec3(1.0,2.0,3.0));
	// gameManager.obs1 = new ModelObstacle("../models/Minecraft/grass.fbx",glm::vec3(1.0,2.0,4.0));
	// gameManager.rew2 = new ModelReward("../models/Minecraft/esmeralda.fbx",glm::vec3(1.0,2.0,5.0));
	// gameManager.obs2 = new ModelObstacle("../models/Minecraft/grass.fbx",glm::vec3(1.0,2.0,6.0));
	// gameManager.obs0 = new ModelObstacle("../models/Minecraft/grass.fbx",glm::vec3(1.0,2.0,2.0));
	// gameManager.rew0 = new ModelReward("../models/Minecraft/esmeralda.fbx",glm::vec3(1.0,2.0,1.0));
	// gameManager.rew0->LoadModelShader(&shaderMulLighting);
	// gameManager.rew0->setTerrain(terrain);
	// gameManager.rew0->setScale(1.0f);
	// gameManager.obs0->LoadModelShader(&shaderMulLighting);
	// gameManager.obs0->setTerrain(terrain);
	// gameManager.obs0->setScale(1.0f);
	// gameManager.rew1->LoadModelShader(&shaderMulLighting);
	// gameManager.rew1->setTerrain(terrain);
	// gameManager.rew1->setScale(1.0f);
	// gameManager.obs1->LoadModelShader(&shaderMulLighting);
	// gameManager.obs1->setTerrain(terrain);
	// gameManager.obs1->setScale(1.0f);
	// gameManager.rew2->LoadModelShader(&shaderMulLighting);
	// gameManager.rew2->setTerrain(terrain);
	// gameManager.rew2->setScale(1.0f);
	// gameManager.obs2->LoadModelShader(&shaderMulLighting);
	// gameManager.obs2->setTerrain(terrain);
	// gameManager.obs2->setScale(1.0f);

	camera->setPosition(glm::vec3(0.0, 2.5, 5.0));
	
	// Carga de texturas para el skybox
	Texture skyboxTexture = Texture("");
	glGenTextures(1, &skyboxTextureID);
	// Tipo de textura CUBE MAP
	glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTextureID);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	for (int i = 0; i < ARRAY_SIZE_IN_ELEMENTS(types); i++) {
		skyboxTexture = Texture(fileNames[i]);
		skyboxTexture.loadImage(true);
		if (skyboxTexture.getData()) {
			glTexImage2D(types[i], 0, skyboxTexture.getChannels() == 3 ? GL_RGB : GL_RGBA, skyboxTexture.getWidth(), skyboxTexture.getHeight(), 0,
			skyboxTexture.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, skyboxTexture.getData());
		} else
			std::cout << "Failed to load texture" << std::endl;
		skyboxTexture.freeImage();
	}

	// Definiendo la textura a utilizar
	Texture textureCesped("../Textures/grassy2.png");
	// Carga el mapa de bits (FIBITMAP es el tipo de dato de la libreria)
	textureCesped.loadImage();
	// Creando la textura con id 1
	glGenTextures(1, &textureCespedID);
	// Enlazar esa textura a una tipo de textura de 2D.
	glBindTexture(GL_TEXTURE_2D, textureCespedID);
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT); // set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Verifica si se pudo abrir la textura
	if (textureCesped.getData()) {
		// Transferis los datos de la imagen a memoria
		// Tipo de textura, Mipmaps, Formato interno de openGL, ancho, alto, Mipmaps,
		// Formato interno de la libreria de la imagen, el tipo de dato y al apuntador
		// a los datos
		std::cout << "Numero de canales :=> " << textureCesped.getChannels() << std::endl;
		glTexImage2D(GL_TEXTURE_2D, 0, textureCesped.getChannels() == 3 ? GL_RGB : GL_RGBA, textureCesped.getWidth(), textureCesped.getHeight(), 0,
		textureCesped.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureCesped.getData());
		// Generan los niveles del mipmap (OpenGL es el ecargado de realizarlos)
		glGenerateMipmap(GL_TEXTURE_2D);
	} else
		std::cout << "Failed to load texture" << std::endl;
	// Libera la memoria de la textura
	textureCesped.freeImage();

	// Definiendo la textura del mapa de mezclas
	Texture textureR("../Textures/dry_grass.png");
	textureR.loadImage(); // Cargar la textura
	glGenTextures(1, &textureTerrainRID); // Creando el id de la textura del landingpad
	glBindTexture(GL_TEXTURE_2D, textureTerrainRID); // Se enlaza la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping en el eje u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrapping en el eje v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering de minimización
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering de maximimizacion
	if(textureR.getData()){
		// Transferir los datos de la imagen a la tarjeta
		glTexImage2D(GL_TEXTURE_2D, 0, textureR.getChannels() == 3 ? GL_RGB : GL_RGBA, textureR.getWidth(), textureR.getHeight(), 0,
		textureR.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureR.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
		std::cout << "Fallo la carga de textura" << std::endl;
	textureR.freeImage(); // Liberamos memoria

	// Definiendo la textura del mapa de mezclas
	Texture textureG("../Textures/snowy_grass.png");
	textureG.loadImage(); // Cargar la textura
	glGenTextures(1, &textureTerrainGID); // Creando el id de la textura del landingpad
	glBindTexture(GL_TEXTURE_2D, textureTerrainGID); // Se enlaza la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping en el eje u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrapping en el eje v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering de minimización
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering de maximimizacion
	if(textureG.getData()){
		// Transferir los datos de la imagen a la tarjeta
		glTexImage2D(GL_TEXTURE_2D, 0, textureG.getChannels() == 3 ? GL_RGB : GL_RGBA, textureG.getWidth(), textureG.getHeight(), 0,
		textureG.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureG.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
		std::cout << "Fallo la carga de textura" << std::endl;
	textureG.freeImage(); // Liberamos memoria

	// Definiendo la textura del mapa de mezclas
	Texture textureB("../Textures/stone_road.png");
	textureB.loadImage(); // Cargar la textura
	glGenTextures(1, &textureTerrainBID); // Creando el id de la textura del landingpad
	glBindTexture(GL_TEXTURE_2D, textureTerrainBID); // Se enlaza la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping en el eje u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrapping en el eje v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering de minimización
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering de maximimizacion
	if(textureB.getData()){
		// Transferir los datos de la imagen a la tarjeta
		glTexImage2D(GL_TEXTURE_2D, 0, textureB.getChannels() == 3 ? GL_RGB : GL_RGBA, textureB.getWidth(), textureB.getHeight(), 0,
		textureB.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureB.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
		std::cout << "Fallo la carga de textura" << std::endl;
	textureB.freeImage(); // Liberamos memoria

	// Definiendo la textura del mapa de mezclas
	Texture textureBlendMap("../Textures/blend_pista_relieve.png");
	textureBlendMap.loadImage(); // Cargar la textura
	glGenTextures(1, &textureTerrainBlendMapID); // Creando el id de la textura del landingpad
	glBindTexture(GL_TEXTURE_2D, textureTerrainBlendMapID); // Se enlaza la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping en el eje u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrapping en el eje v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering de minimización
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering de maximimizacion
	if(textureBlendMap.getData()){
		// Transferir los datos de la imagen a la tarjeta
		glTexImage2D(GL_TEXTURE_2D, 0, textureBlendMap.getChannels() == 3 ? GL_RGB : GL_RGBA, textureBlendMap.getWidth(), textureBlendMap.getHeight(), 0,
		textureBlendMap.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureBlendMap.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
		std::cout << "Fallo la carga de textura" << std::endl;
	textureBlendMap.freeImage(); // Liberamos memoria

	// Definiendo la textura del primer menu
	Texture textureIntro1("../Textures/menu/menuOp1.png");
	textureIntro1.loadImage(); // Cargar la textura
	glGenTextures(1, &textureInit1ID); // Creando el id de la textura del landingpad
	glBindTexture(GL_TEXTURE_2D, textureInit1ID); // Se enlaza la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping en el eje u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrapping en el eje v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering de minimización
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering de maximimizacion
	if(textureIntro1.getData()){
		// Transferir los datos de la imagen a la tarjeta
		glTexImage2D(GL_TEXTURE_2D, 0, textureIntro1.getChannels() == 3 ? GL_RGB : GL_RGBA, textureIntro1.getWidth(), textureIntro1.getHeight(), 0,
		textureIntro1.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureIntro1.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
		std::cout << "Fallo la carga de textura" << std::endl;
	textureIntro1.freeImage(); // Liberamos memoria

	// Definiendo la textura
	Texture textureIntro2("../Textures/menu/menuOp2.png");
	textureIntro2.loadImage(); // Cargar la textura
	glGenTextures(1, &textureInit2ID); // Creando el id de la textura del landingpad
	glBindTexture(GL_TEXTURE_2D, textureInit2ID); // Se enlaza la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping en el eje u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrapping en el eje v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering de minimización
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering de maximimizacion
	if(textureIntro2.getData()){
		// Transferir los datos de la imagen a la tarjeta
		glTexImage2D(GL_TEXTURE_2D, 0, textureIntro2.getChannels() == 3 ? GL_RGB : GL_RGBA, textureIntro2.getWidth(), textureIntro2.getHeight(), 0,
		textureIntro2.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureIntro2.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
		std::cout << "Fallo la carga de textura" << std::endl;
	textureIntro2.freeImage(); // Liberamos memoria

	// Definiendo la textura
	Texture textureIntro3("../Textures/menu/menuOp3.png");
	textureIntro3.loadImage(); // Cargar la textura
	glGenTextures(1, &textureInit3ID); // Creando el id de la textura del landingpad
	glBindTexture(GL_TEXTURE_2D, textureInit3ID); // Se enlaza la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping en el eje u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrapping en el eje v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering de minimización
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering de maximimizacion
	if(textureIntro3.getData()){
		// Transferir los datos de la imagen a la tarjeta
		glTexImage2D(GL_TEXTURE_2D, 0, textureIntro3.getChannels() == 3 ? GL_RGB : GL_RGBA, textureIntro3.getWidth(), textureIntro3.getHeight(), 0,
		textureIntro3.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureIntro3.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
		std::cout << "Fallo la carga de textura" << std::endl;
	textureIntro3.freeImage(); // Liberamos memoria

	// Definiendo la textura 
	Texture textureScreen("../Textures/3vidas.png");
	textureScreen.loadImage(); // Cargar la textura
	glGenTextures(1, &textureScreenID); // Creando el id de la textura del landingpad
	glBindTexture(GL_TEXTURE_2D, textureScreenID); // Se enlaza la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping en el eje u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrapping en el eje v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering de minimización
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering de maximimizacion
	if(textureScreen.getData()){
		// Transferir los datos de la imagen a la tarjeta
		glTexImage2D(GL_TEXTURE_2D, 0, textureScreen.getChannels() == 3 ? GL_RGB : GL_RGBA, textureScreen.getWidth(), textureScreen.getHeight(), 0,
		textureScreen.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureScreen.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
		std::cout << "Fallo la carga de textura" << std::endl;
	textureScreen.freeImage(); // Liberamos memoria

	// Definiendo la textura 2vidas
	Texture textureScreen1("../Textures/2vidas.png");
	textureScreen1.loadImage(); // Cargar la textura
	glGenTextures(1, &textureScreen1ID); // Creando el id de la textura del landingpad
	glBindTexture(GL_TEXTURE_2D, textureScreen1ID); // Se enlaza la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping en el eje u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrapping en el eje v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering de minimización
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering de maximimizacion
	if(textureScreen1.getData()){
		// Transferir los datos de la imagen a la tarjeta
		glTexImage2D(GL_TEXTURE_2D, 0, textureScreen1.getChannels() == 3 ? GL_RGB : GL_RGBA, textureScreen1.getWidth(), textureScreen1.getHeight(), 0,
		textureScreen1.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureScreen1.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
		std::cout << "Fallo la carga de textura" << std::endl;
	textureScreen1.freeImage(); // Liberamos memoria

	// Definiendo la textura 1 vida 
	Texture textureScreen2("../Textures/1vida.png");
	textureScreen2.loadImage(); // Cargar la textura
	glGenTextures(1, &textureScreen2ID); // Creando el id de la textura del landingpad
	glBindTexture(GL_TEXTURE_2D, textureScreen2ID); // Se enlaza la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping en el eje u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrapping en el eje v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering de minimización
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering de maximimizacion
	if(textureScreen2.getData()){
		// Transferir los datos de la imagen a la tarjeta
		glTexImage2D(GL_TEXTURE_2D, 0, textureScreen2.getChannels() == 3 ? GL_RGB : GL_RGBA, textureScreen2.getWidth(), textureScreen2.getHeight(), 0,
		textureScreen2.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureScreen2.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
		std::cout << "Fallo la carga de textura" << std::endl;
	textureScreen2.freeImage(); // Liberamos memoria

	// Definiendo la textura fin de partida
	Texture textureScreen3("../Textures/finPartida1.png");
	textureScreen3.loadImage(); // Cargar la textura
	glGenTextures(1, &textureScreen3ID); // Creando el id de la textura del landingpad
	glBindTexture(GL_TEXTURE_2D, textureScreen3ID); // Se enlaza la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping en el eje u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrapping en el eje v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering de minimización
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering de maximimizacion
	if(textureScreen3.getData()){
		// Transferir los datos de la imagen a la tarjeta
		glTexImage2D(GL_TEXTURE_2D, 0, textureScreen3.getChannels() == 3 ? GL_RGB : GL_RGBA, textureScreen3.getWidth(), textureScreen3.getHeight(), 0,
		textureScreen3.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureScreen3.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
		std::cout << "Fallo la carga de textura" << std::endl;
	textureScreen3.freeImage(); // Liberamos memoria

	// Definiendo la textura fin de partida
	Texture textureScreen4("../Textures/finPartida2.png");
	textureScreen4.loadImage(); // Cargar la textura
	glGenTextures(1, &textureScreen4ID); // Creando el id de la textura del landingpad
	glBindTexture(GL_TEXTURE_2D, textureScreen4ID); // Se enlaza la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping en el eje u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrapping en el eje v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering de minimización
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering de maximimizacion
	if(textureScreen4.getData()){
		// Transferir los datos de la imagen a la tarjeta
		glTexImage2D(GL_TEXTURE_2D, 0, textureScreen4.getChannels() == 3 ? GL_RGB : GL_RGBA, textureScreen4.getWidth(), textureScreen4.getHeight(), 0,
		textureScreen4.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureScreen4.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
		std::cout << "Fallo la carga de textura" << std::endl;
	textureScreen4.freeImage(); // Liberamos memoria

	scoreManager.init(screenWidth, screenHeight);

}

void destroy() {
	glfwDestroyWindow(window);
	glfwTerminate();
	// --------- IMPORTANTE ----------
	// Eliminar los shader y buffers creados.

	// Shaders Delete
	shader.destroy();
	shaderMulLighting.destroy();
	shaderSkybox.destroy();
	shaderTerrain.destroy();

	//Menu
	boxIntro.destroy();

	//Proyecto minecard
	minecard.destroy();
	terrain.destroy();
	// reward.destroy();
	modelMuro.destroy();
	
	// Textures Delete
	glDeleteTextures(1, &textureCespedID);
	glDeleteTextures(1, &textureTerrainBID);
	glDeleteTextures(1, &textureTerrainGID);
	glDeleteTextures(1, &textureTerrainRID);
	glDeleteTextures(1, &textureTerrainBlendMapID);


	// Cube Maps Delete
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glDeleteTextures(1, &skyboxTextureID);
	glDeleteTextures(1, &textureInit1ID);
	glDeleteTextures(1, &textureInit2ID);
	glDeleteTextures(1, &textureInit3ID);
	glDeleteTextures(1, &textureActivaID);
	glDeleteTextures(1, &textureScreen1ID);
	glDeleteTextures(1, &textureScreen2ID);
	glDeleteTextures(1, &textureScreen3ID);
	glDeleteTextures(1, &textureScreen4ID);
	glDeleteTextures(1, &textureScreenID);
}

void reshapeCallback(GLFWwindow *Window, int widthRes, int heightRes) {
	screenWidth = widthRes;
	screenHeight = heightRes;
	glViewport(0, 0, widthRes, heightRes);
}

void keyCallback(GLFWwindow *window, int key, int scancode, int action,
		int mode) {
	if (action == GLFW_PRESS) {
		switch (key) {
		case GLFW_KEY_ESCAPE:
			exitApp = true;
			break;
		}
	}
}

void mouseCallback(GLFWwindow *window, double xpos, double ypos) {
	offsetX = xpos - lastMousePosX;
	offsetY = ypos - lastMousePosY;
	lastMousePosX = xpos;
	lastMousePosY = ypos;
}

void mouseButtonCallback(GLFWwindow *window, int button, int state, int mod) {
	if (state == GLFW_PRESS) {
		switch (button) {
		case GLFW_MOUSE_BUTTON_RIGHT:
			std::cout << "lastMousePos.y:" << lastMousePosY << std::endl;
			break;
		case GLFW_MOUSE_BUTTON_LEFT:
			std::cout << "lastMousePos.x:" << lastMousePosX << std::endl;
			break;
		case GLFW_MOUSE_BUTTON_MIDDLE:
			std::cout << "lastMousePos.x:" << lastMousePosX << std::endl;
			std::cout << "lastMousePos.y:" << lastMousePosY << std::endl;
			break;
		}
	}
}

bool processInput(bool continueApplication) {
	if (exitApp || glfwWindowShouldClose(window) != 0) {
		return false;
	}
	//menu
	if(!iniciaPartida){
		GLuint textureActivaAuxID;
		bool presionarEnter = glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS;
		bool presionarIntro = glfwGetKey(window, GLFW_KEY_DELETE) == GLFW_PRESS;
		if(textureActivaID == textureInit1ID && presionarEnter){
			textureActivaID = textureScreenID;
			iniciaPartida = true;
			return true;
		}else if(textureActivaID == textureInit3ID && presionarEnter)
			exitApp = true;
		else if(!presionarOpcion && glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS){
			presionarOpcion = true;
			if(textureActivaID == textureInit1ID)
				textureActivaID = textureInit2ID;
			else if(textureActivaID == textureInit2ID)
				textureActivaID = textureInit3ID;
			else if(textureActivaID == textureInit3ID)
				textureActivaID = textureInit1ID;
		}
		else if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_RELEASE)
			presionarOpcion = false;
	}else{


		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			camera->moveFrontCamera(true, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			camera->moveFrontCamera(false, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			camera->moveRightCamera(false, deltaTime);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			camera->moveRightCamera(true, deltaTime);
		if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
			camera->mouseMoveCamera(offsetX, offsetY, deltaTime);
		offsetX = 0;
		offsetY = 0;

		
		bool flush = glfwGetKey(window, GLFW_KEY_R);
		
		if(gameManager.vivo){
			if( glfwGetKey(window, GLFW_KEY_LEFT)  == GLFW_RELEASE && glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
				minecard.moveLeft();
			}else if ( glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_RELEASE && glfwGetKey(window, GLFW_KEY_LEFT)  == GLFW_PRESS)
			{
				minecard.moveRight();
			}
			if ( glfwGetKey(window, GLFW_KEY_SPACE)  == GLFW_PRESS)
			{
				minecard.jump();
			}
			if ( glfwGetKey(window, GLFW_KEY_LEFT_SHIFT)  == GLFW_PRESS)
			{
				minecard.bendDown();
			}
		}else if(!(gameManager.vivo) && gameManager.vidas==0 && glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS){
				
				if (textureActivaID == textureScreen3ID)
				{
					op = true;
					gameManager.revivir();
					scoreManager.reset();
				}else if(textureActivaID==textureScreen4ID){
					exitApp = true;
				}
				
		}
		
		flush = glfwGetKey(window, GLFW_KEY_TAB);
		

		if (gameManager.vidas == 3){
			textureActivaID = textureScreenID;
		}else if(gameManager.vidas == 2){
			textureActivaID = textureScreen1ID;
		}else if(gameManager.vidas == 1){
			textureActivaID = textureScreen2ID;
		}else if (gameManager.vidas == 0){
			if (glfwGetKey(window, GLFW_KEY_TAB)== GLFW_PRESS)
			op = !op;
			if(op){
				textureActivaID= textureScreen3ID;
			}else{
				textureActivaID=textureScreen4ID;
			}
		}
		
	}
	
	
	
	

	glfwPollEvents();
	return continueApplication;
}

void renderAlphaScene(bool render = true){
	/****
	 * Update the position with alpha objects
	 */

	/****
	 * Render de las transparencias
	 */
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_CULL_FACE);
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);

	if(render){
		/*****Render de imagen de frente*****/
		shaderTexture.setMatrix4("projection", 1, false, glm::value_ptr(glm::mat4(1.0)));
		shaderTexture.setMatrix4("view", 1, false, glm::value_ptr(glm::mat4(1.0)));
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureActivaID);
		shaderTexture.setInt("outTexture", 0);
		glEnable(GL_BLEND);
		boxIntro.render();
		glDisable(GL_BLEND);
	}
	glDisable(GL_CULL_FACE);
}

void renderSolidScene(glm::mat4 projection, glm::mat4 view){
	/*******************************************
	 * Skybox
	 *******************************************/
	GLint oldCullFaceMode;
	GLint oldDepthFuncMode;
	// deshabilita el modo del recorte de caras ocultas para ver las esfera desde adentro
	glGetIntegerv(GL_CULL_FACE_MODE, &oldCullFaceMode);
	glGetIntegerv(GL_DEPTH_FUNC, &oldDepthFuncMode);
	shaderSkybox.setFloat("skybox", 0);
	glCullFace(GL_FRONT);
	glDepthFunc(GL_LEQUAL);
	glActiveTexture(GL_TEXTURE0);
	skyboxSphere.render();
	glCullFace(oldCullFaceMode);
	glDepthFunc(oldDepthFuncMode);

	gameManager.loop(projection, view);
}

void renderScene(glm::mat4 projection, glm::mat4 view){
	renderSolidScene(projection, view);
	renderAlphaScene(false);
}

void applicationLoop() {
	bool psi = true;

	
	int state = 0;
	float advanceCount = 0.0;
	float rotCount = 0.0;
	float rotWheelsX = 0.0;
	float rotWheelsY = 0.0;
	int numberAdvance = 0;
	int maxAdvance = 0.0;


	lastTime = TimeManager::Instance().GetTime();

	textureActivaID = textureInit1ID;

	while (psi) {
		currTime = TimeManager::Instance().GetTime();
		if(currTime - lastTime < 0.016666667){
			glfwPollEvents();
			continue;
		}
		lastTime = currTime;
		TimeManager::Instance().CalculateFrameRate(false);
		deltaTime = TimeManager::Instance().DeltaTime;
		psi = processInput(true);

		// Variables donde se guardan las matrices de cada articulacion por 1 frame
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection = glm::perspective(glm::radians(45.0f),
				(float) screenWidth / (float) screenHeight, 0.01f, 100.0f);
		glm::mat4 view = camera->getViewMatrix();

		// Settea la matriz de vista y projection al shader con solo color
		shader.setMatrix4("projection", 1, false, glm::value_ptr(projection));
		shader.setMatrix4("view", 1, false, glm::value_ptr(view));

		// Settea la matriz de vista y projection al shader con skybox
		shaderSkybox.setMatrix4("projection", 1, false,
				glm::value_ptr(projection));
		shaderSkybox.setMatrix4("view", 1, false,
				glm::value_ptr(glm::mat4(glm::mat3(view))));
		// Settea la matriz de vista y projection al shader con multiples luces
		shaderMulLighting.setMatrix4("projection", 1, false,
					glm::value_ptr(projection));
		shaderMulLighting.setMatrix4("view", 1, false,
				glm::value_ptr(view));
		
		shaderTerrain.setMatrix4("projection", 1, false,
					glm::value_ptr(projection));
		shaderTerrain.setMatrix4("view", 1, false,
				glm::value_ptr(view));

		/*******************************************
		 * Propiedades Luz direccional
		 *******************************************/
		shaderMulLighting.setVectorFloat3("viewPos", glm::value_ptr(camera->getPosition()));
		shaderMulLighting.setVectorFloat3("directionalLight.light.ambient", glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
		shaderMulLighting.setVectorFloat3("directionalLight.light.diffuse", glm::value_ptr(glm::vec3(0.7, 0.7, 0.7)));
		shaderMulLighting.setVectorFloat3("directionalLight.light.specular", glm::value_ptr(glm::vec3(0.9, 0.9, 0.9)));
		shaderMulLighting.setVectorFloat3("directionalLight.direction", glm::value_ptr(glm::vec3(-1.0, 0.0, 0.0)));

		shaderTerrain.setVectorFloat3("viewPos", glm::value_ptr(camera->getPosition()));
		shaderTerrain.setVectorFloat3("directionalLight.light.ambient", glm::value_ptr(glm::vec3(0.3, 0.3, 0.3)));
		shaderTerrain.setVectorFloat3("directionalLight.light.diffuse", glm::value_ptr(glm::vec3(0.7, 0.7, 0.7)));
		shaderTerrain.setVectorFloat3("directionalLight.light.specular", glm::value_ptr(glm::vec3(0.9, 0.9, 0.9)));
		shaderTerrain.setVectorFloat3("directionalLight.direction", glm::value_ptr(glm::vec3(-1.0, 0.0, 0.0)));
		/*******************************************
		 * Propiedades SpotLights
		 *******************************************/
		shaderMulLighting.setInt("spotLightCount", 0);
		shaderTerrain.setInt("spotLightCount", 0);
		/*******************************************
		 * Propiedades PointLights
		 *******************************************/
		shaderMulLighting.setInt("pointLightCount", 0);
		shaderTerrain.setInt("pointLightCount", 0);

		

		/************Render de imagen de frente**************/
		if(!iniciaPartida){
			shaderTexture.setMatrix4("projection", 1, false, glm::value_ptr(glm::mat4(1.0)));
			shaderTexture.setMatrix4("view", 1, false, glm::value_ptr(glm::mat4(1.0)));
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, textureActivaID);
			shaderTexture.setInt("outTexture", 0);
			boxIntro.render();
			glfwSwapBuffers(window);
			continue;
		}

		

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureCespedID);
		shaderTerrain.setInt("backgroundTexture", 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textureTerrainRID);
		shaderTerrain.setInt("rTexture",1);

		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, textureTerrainGID);
		shaderTerrain.setInt("gTexture",2);
		
		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, textureTerrainBID);
		shaderTerrain.setInt("bTexture",3);
		
		glActiveTexture(GL_TEXTURE4);
		glBindTexture(GL_TEXTURE_2D, textureTerrainBlendMapID);
		shaderTerrain.setInt("blendMapTexture",4);

		shaderTerrain.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(80, 80)));
		terrain.setPosition(glm::vec3(100, 0, 100));
		terrain.render();
		shaderTerrain.setVectorFloat2("scaleUV", glm::value_ptr(glm::vec2(0, 0)));
		glBindTexture(GL_TEXTURE_2D, 0);
		

		
		
		glEnable(GL_CULL_FACE);

		//Proyecto minecard
		
		minecard.render();
		// reward.render(projection, view);

		for (int i =0; i< muroPosition.size(); i++){
			glm::mat4 modelMatrixMuros = glm::mat4(1.0f);
			modelMatrixMuros = glm::translate(modelMatrixMuros, muroPosition[i]);
			glm::vec3 muroPosition = glm::vec3(modelMatrixMuros[3]);
		//modelMatrixMuro[3][1] = terrain.getHeightTerrain(modelMatrixMuro[3][0], modelMatrixMuro[3][2]);
		//glm::mat4 modelMatrixMuros = glm::mat4(modelMatrixMuro);
		//modelMuro.render(modelMatrixMuros);
		}

		for(int i = 0; i< muroPosition.size(); i++){
			muroPosition[i].y =  terrain.getHeightTerrain(muroPosition[i].x, muroPosition[i].z);
			modelMuro.setPosition(muroPosition[i]);
			modelMuro.setScale(glm::vec3(0.25));
			//modelMuro.setOrientation(glm::vec3(0, muroPosition[i],0));
			modelMuro.render();
		}

		//renderSolidScene();
		renderScene(projection, view);
		/**********Render de transparencias***************/
		renderAlphaScene();
		
		if (gameManager.vidas>0 && !(gameManager.vivo))
		{
			/*Revivir */
			gameManager.revivir();
		}
		// gameManager.rew0->render(projection, view);
        // gameManager.obs0->render(projection, view);
        // gameManager.rew1->render(projection, view);
        // gameManager.obs1->render(projection, view);
        // gameManager.obs2->render(projection, view);
        // gameManager.rew2->render(projection, view);
		
		/*******************************************
		 * Skybox
		 *******************************************/
		GLint oldCullFaceMode;
		GLint oldDepthFuncMode;
		// deshabilita el modo del recorte de caras ocultas para ver las esfera desde adentro
		glGetIntegerv(GL_CULL_FACE_MODE, &oldCullFaceMode);
		glGetIntegerv(GL_DEPTH_FUNC, &oldDepthFuncMode);
		shaderSkybox.setFloat("skybox", 0);
		glCullFace(GL_FRONT);
		glDepthFunc(GL_LEQUAL);
		glActiveTexture(GL_TEXTURE0);
		skyboxSphere.render();
		glCullFace(oldCullFaceMode);
		glDepthFunc(oldDepthFuncMode);

		scoreManager.setScore(gameManager.score);
		scoreManager.renderScore();


		
		

		glfwSwapBuffers(window);
	}
}

int main(int argc, char **argv) {
	init(800, 700, "Window GLFW", false);
	applicationLoop();
	destroy();
	return 1;
}