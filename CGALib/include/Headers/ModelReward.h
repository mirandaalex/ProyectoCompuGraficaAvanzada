/*
 * Model.h
 *
 *  Created on: 14/09/2023
 *      Author: Alex
 */

#ifndef REWARD_PROY_H_
#define REWARD_PROY_H_

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
#include "ParticlesModel.h"


enum ModelRewardPoss{
  TOP,
  BOT
};

class DLL_PUBLIC ModelReward
{
private:
    /*Models
    */
    glm::mat4 modelMatrixGoal = glm::mat4(1.0f);
    glm::vec3 initalPoss = glm::vec3(0.0f);
    std::string path;
    glm::vec3 scale = glm::vec3(1.0f);
    float rotation = 0.0f;
    //Movimiento
    void interpolationMovementHandler();
    void movementDelayHandler();
    //movimiento 
    ModelRewardPoss position = BOT;
    bool moving = false;
    float verticalStride = 0.2f;
    //salto
    Terrain *terreno;
 

public:
    
    Model *model;
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    ParticlesModel *particle;
    glm::vec3 movvec = glm::vec3(0.0 ,0.5, 0.0);
    //Init
    ModelReward(std::string path,glm::vec3 initPoss);
    ModelReward(std::string path);
    ModelReward(Model &vmodel);
    ~ModelReward();
    void destroy();
    void render(glm::mat4 proj, glm::mat4 view);
    void LoadModelShader(Shader * shaderMulLighting);
    //Getter/Setter
    void setScale(float newScale);
    void setScale(glm::vec3 newScale);
    glm::vec3 getScale();
    void rotate(float newRotation);
    float getCurrentRotation();
    void setTerrain(Terrain &newTerreno);

    //Movimiento
    void move(glm::vec3 move);
    void moveTB();

    

};

class DLL_PUBLIC ModelObstacle
{
private:
    /*Models
    */
    glm::mat4 modelMatrixGoal = glm::mat4(1.0f);
    glm::vec3 initalPoss = glm::vec3(0.0f);
    std::string path;
    glm::vec3 scale = glm::vec3(1.0f);
    float rotation = 0.0f;
    //Movimiento
    void interpolationMovementHandler();
    void movementDelayHandler();
    //movimiento 
    
    bool moving = false;
    float verticalStride = 0.2f;
    //salto
    Terrain *terreno;
 

public:
    int MINRANGE = -40;
    int MAXRANGE = 40;
    Model *model;
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    ParticlesModel *particle;
    bool rendered = false;
    glm::vec3 movvec = glm::vec3(0.0 ,0.5, 0.0);
    //Init
    ModelObstacle() =default;
    ModelObstacle(const ModelObstacle& other) =default;
    ModelObstacle(ModelObstacle&& other) =default;
    
    ModelObstacle & operator=(const ModelObstacle& other) =default;
    ModelObstacle & operator=(ModelObstacle&& other) =default;


    ModelObstacle(std::string path,glm::vec3 initPoss);
    ModelObstacle(std::string path);
    ModelObstacle(Model &vmodel);
    ~ModelObstacle();
    void destroy();
    void render(glm::mat4 proj, glm::mat4 view);
    void LoadModelShader(Shader * shaderMulLighting);
    //Getter/Setter
    void setScale(float newScale);
    void setScale(glm::vec3 newScale);
    glm::vec3 getScale();
    void rotate(float newRotation);
    float getCurrentRotation();
    void setTerrain(Terrain &newTerreno);

    //Movimiento
    void move(glm::vec3 move);
    void generate_position(int& state_obstacle, float& _random_x_obstacle, float& movement_obstacles, float & difficulty);

    

};

#endif /* REWARD_PROY_H_ */