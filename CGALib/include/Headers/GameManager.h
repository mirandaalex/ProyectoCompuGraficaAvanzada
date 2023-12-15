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

#define NUM_BUFFERS 1
#define NUM_SOURCES 1
#define NUM_ENVIRONMENTS 1
// Listener
ALfloat listenerCharacterPos[] = { 0.0, 0.0, 4.0 };
ALfloat listenerCharacterVel[] = { 0.0, 0.0, 0.0 };
ALfloat listenerCharacterOri[] = { 0.0, 0.0, 1.0, 0.0, 1.0, 0.0 };
// Source 0
ALfloat sourceEsmeraldPos[] = { -2.0, 0.0, 0.0 };
ALfloat sourceEsmeraldVel[] = { 0.0, 0.0, 0.0 };

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


class DLL_PUBLIC GameManager
{
private:
  std::map<std::string, std::tuple<AbstractModel::OBB, glm::mat4, glm::mat4> > collidersOBB;  
  bool drawColiders=false;
  std::vector<ModelReward*> rewards;
  ModelCharacter *player;
  Box boxCollider;
  glm::vec4 color;
  bool shaderInit=false;

  //audio
  
public:

    //Init
    GameManager();
    GameManager(bool vDrawColiders);
    GameManager(bool vDrawColiders, glm::vec4 vcolor);
    ~GameManager();
    void setShader(Shader * shaderMulLighting);
    void initAudio();
    void playAudio(glm::mat4 esmeraldPoss);
    void setDrawColiders(bool);
    void add(ModelCharacter &ply1);
    void add(ModelReward &rw);
    void loop();
    void handleColision(std::map<std::string, bool> collisionDetection);
    std::map<std::string, bool> detectColision();
    void drawWireColiders();
    void updateColliders();
};


#endif /* GAMEMAN_H_ */