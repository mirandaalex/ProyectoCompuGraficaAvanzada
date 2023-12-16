/*
 * Model.h
 *
 *  Created on: 14/09/2023
 *      Author: Alex
 */

#ifndef GAMEMAN_H_
#define GAMEMAN_H_

#if defined _WIN32 || defined __CYGWIN__
  #ifdef BUILDING_DLL
    #ifdef __GNUC__
      #define DLL_PUBLIC __attribute__ ((dllexport))
    #else
      #define DLL_PUBLIC __declspec(dllexport) // Note: actually gcc seems to also supports this syntax.
    #endif
  #else
    #ifdef __GNUC__
      #define DLL_PUBLIC __attribute__ ((dllimport))
    #else
      #define DLL_PUBLIC __declspec(dllimport) // Note: actually gcc seems to also supports this syntax.
    #endif
  #endif
  #define DLL_LOCAL
#else
  #if __GNUC__ >= 4
    #define DLL_PUBLIC __attribute__ ((visibility ("default")))
    #define DLL_LOCAL  __attribute__ ((visibility ("hidden")))
  #else
    #define DLL_PUBLIC
    #define DLL_LOCAL
  #endif
#endif



#include "Model.h"
#include "TimeManager.h"
#include "Terrain.h"
#include "Colisiones.h"
#include "ModelCharacter.h"
#include "ModelReward.h"
#include "Box.h"
#include <AL/alut.h>


#define NUM_BUFFERS 2
#define NUM_SOURCES 2
#define NUM_ENVIRONMENTS 1
// Listener
ALfloat listenerCharacterPos[] = { 0.0, 0.0, 4.0 };
ALfloat listenerCharacterVel[] = { 0.0, 0.0, 0.0 };
ALfloat listenerCharacterOri[] = { 0.0, 0.0, 1.0, 0.0, 1.0, 0.0 };
// Source 0
ALfloat sourceEsmeraldPos[] = { -2.0, 0.0, 0.0 };
ALfloat sourceEsmeraldVel[] = { 0.0, 0.0, 0.0 };
ALfloat sourceObstPos[] = { -2.0, 0.0, 0.0 };
ALfloat sourceObstVel[] = { 0.0, 0.0, 0.0 };

// Buffers
ALuint buffer[NUM_BUFFERS];
ALuint source[NUM_SOURCES];
ALuint environment[NUM_ENVIRONMENTS];
// Configs
ALsizei size, freq;
ALenum format;
ALvoid *data;
int ch;
ALboolean loop;

enum possibilities{
  REW,
  OBS,
  NON

};
enum estadoObj{
  Iniciando,
  Moviendo,
  Meta,
  temp
};
class DLL_PUBLIC GameManager
{
private:
  std::map<std::string, std::tuple<AbstractModel::OBB, glm::mat4, glm::mat4> > collidersOBB;  
  bool drawColiders=false;
  std::vector<ModelReward*> rewards;
  std::vector<ModelObstacle*> obstacles;
  ModelCharacter *player;
  Box boxCollider;
  glm::vec4 color;
  bool shaderInit=false;
  Terrain *terreno;
  Shader *shader;
  std::vector<std::tuple<possibilities,possibilities,possibilities>> render_queue;
   std::vector<possibilities> possible_renders = {
    REW,
    OBS,
    NON
  };
  bool genTuple = true;
  double initTime, currTime, delay;
  
public:
  ModelObstacle *obs0, *obs1,*obs2;
  ModelReward *rew0, *rew1,*rew2;
    estadoObj estado = Iniciando;
    possibilities aux0,aux1,aux2;
    std::vector<float> positionDesplazamiento = {-2.0, 0.0, 2.0};
    float meta =10.0f;
    const float initPoss=-50.0f;
    float currPoss=0.0f;
    float stride=0.1f;
    float vel=1.0f;
    float aceleracion=0.2f;
    bool vivo = true;
    int score = 0;
    double scoret0,scoret1;
    double scoretdelay = 5.0;
    const int vidas_max = 3;
    int vidas = 3;
    //Init
    GameManager();
    GameManager(bool vDrawColiders);
    GameManager(bool vDrawColiders, glm::vec4 vcolor);
    ~GameManager();
    void setShader(Shader * vshaderMulLighting);
    void setTerrain(Terrain & Terrainv);
    void initAudio();
    void playAudio(glm::mat4 esmeraldPoss, int idx);
    void setDrawColiders(bool);
    void add(ModelCharacter &ply1);
    void add(ModelReward *rw);
    void add(ModelObstacle *obst);
    void loop(glm::mat4 &,glm::mat4&);
    void revivir();
    void handleColision(std::map<std::string, bool> collisionDetection);
    std::map<std::string, bool> detectColision();
    void drawWireColiders();
    void updateColliders();
    bool checkColiderValidRewards(int idx);
    bool checkColiderValidObstacle(int idx);
    
    void make_tuple(); // internamente crea tuplas de forma drandom con base en las possibilities
    void reset_tuple(); // internamente crea tuplas de forma drandom con base en las possibilities
    void genObjs(glm::mat4 proj,glm::mat4 view);
    void handlerObjts(glm::mat4 proj,glm::mat4 view);
    void rendObjts(glm::mat4,glm::mat4);
    void movObjts();
    void upscore();
};

#endif /* GAMEMAN_H_ */