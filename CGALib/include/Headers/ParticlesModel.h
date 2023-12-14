/*
 * Model.h
 *
 *  Created on: 14/09/2023
 *      Author: Alex
 */

#ifndef PARTICLESMODEL_H_
#define PARTICLESMODEL_H_

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




class DLL_PUBLIC ParticlesModel
{
private:
    Shader shaderE;
    GLuint initVel, startTime;
    GLuint VAOParticles;
    GLuint nParticles = 200;
    double currTimeParticles, lastTimeParticles;
    double particleslife = 5.0;
    float particlessize = 10.0f;
    float gravity = 0.4f;
    float vmin=0.4f;
    float vmax=0.6f;
    GLuint textureID;
    std::string texture;
    bool showing = false;
    //poss
    glm::mat4* modelPoss;
    Terrain *terrain;

    const std::string texture_def = "../Textures/bluewater.png";
    const std::string vertex_shader = "../Shaders/particlesFountain.vs";
    const std::string fragment_shader = "../Shaders/particlesFountain.fs";
public:

    //Init
    ParticlesModel(glm::mat4& model);
    ParticlesModel(glm::mat4& model, std::string texture_path);
    ~ParticlesModel();
    void initParticleBuffers();
    void initTexture();
    void setModelMatrix(glm::mat4& model);
    void setTerrain(Terrain &vterr);
    void setShader();
    void setShader(std::string vs,std::string fs);
    void DrawParticles();
    void loop(glm::mat4 proj, glm::mat4 view);
};


#endif /* PARTICLESMODEL_H_ */