/*
 * Model.h
 *
 *  Created on: 14/09/2023
 *      Author: Alex
 */

#ifndef MODEL_PROY_H_
#define MODEL_PROY_H_

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
#include "Headers/Terrain.h"

enum ModelPoss{
  Left,
  Center,
  Right
};

class DLL_PUBLIC ModelCharacter
{
private:
    /*Models
    */
    Model *modelCharacter;
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    glm::mat4 modelMatrixGoal = glm::mat4(1.0f);
    glm::vec3 initalPoss = glm::vec3(0.0f);
    std::string path;
    int animation_ix = 0;
    glm::vec3 scale = glm::vec3(1.0f);
    float rotation = 0.0f;
    //Movimiento
    void interpolationMovementHandler();
    void movementDelayHandler();
    //movimiento lateral
    ModelPoss position = Center;
    float horizontalStride = 1.0f;
    bool moving = false;
    double time = 0.0;
    double delay = 0.15;
    //salto
    Terrain *terreno;
    bool jumping = false;
    double v0 = 9.0;
    double t0 = 0.0;
    double h0;
    double g = 14.5;
    //agacharse
    bool bending = false;
    bool bend = false;
    bool b_delay = false;
    double bending_t0;
    double bend_t0=0.0;
    double bending_delay=1.0;
    double bend_delay=0.2;
    float scaleModel = 0.5;

public:

    //Init
    ModelCharacter(std::string path);
    ModelCharacter(Model &model);
    ~ModelCharacter();
    void destroy();
    void render();
    void LoadModelShader(Shader * shaderMulLighting);
    //Getter/Setter
    void setScale(float newScale);
    void setScale(glm::vec3 newScale);
    glm::vec3 getScale();
    void rotate(float newRotation);
    float getCurrentRotation();
    void setTerrain(Terrain &newTerreno);

    //Movimiento
    void moveLeft();
    void moveRight();
    void jump();
    void bendDown();
};


#endif /* MODEL_PROY_H_ */