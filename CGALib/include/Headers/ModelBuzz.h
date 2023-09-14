/*
 * Model.h
 *
 *  Created on: 14/09/2023
 *      Author: Alex
 */

#ifndef MODEL_BUZZ_H_
#define MODEL_BUZZ_H_

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

class DLL_PUBLIC ModelBuzz
{
private:
    /*Models
    */
    Model modelBuzzHead;
    Model modelBuzzHip;
    Model modelBuzzLeftArm;
    Model modelBuzzLeftCalf;
    Model modelBuzzLeftFoot;
    Model modelBuzzLeftForearm;
    Model modelBuzzLeftHand;
    Model modelBuzzLeftThigh;
    Model modelBuzzLeftWing1;
    Model modelBuzzLeftWing2;
    Model modelBuzzRightArm;
    Model modelBuzzRightCalf;
    Model modelBuzzRightFoot;
    Model modelBuzzRightForearm;
    Model modelBuzzRightHand;
    Model modelBuzzRightThigh;
    Model modelBuzzRightWing1;
    Model modelBuzzRightWing2;
    Model modelBuzzTorso;
public:
    glm::mat4 modelMatrixBuzz = glm::mat4(1.0f);
    /* *Rot */
    float rotBuzzHead = 0.0;
    float rotBuzzLeftArm = 0.0;
    float rotBuzzRightArm = 0.0;
    float rotBuzzHip = 0.0;
    float rotBuzzLeftForearm = 0.0;
    float rotBuzzRightForearm = 0.0;
    float rotBuzzLeftThigh = 0.0;
    float rotBuzzRightThigh = 0.0;
    float rotBuzzLeftCalf = 0.0;
    float rotBuzzRightCalf = 0.0;
    
    //Joints interpolations Buzz
    std::vector<std::vector<float>> keyFramesBuzzJoints;
    std::vector<std::vector<glm::mat4>> keyFramesBuzz;
    int indexFrameBuzzJoints = 0;
    int indexFrameBuzzJointsNext = 1;
    float interpolationBuzzJoints = 0.0;
    int maxNumPasosBuzzJoints = 20;
    int numPasosBuzzJoints = 0;
    int indexFrameBuzz = 0;
    int indexFrameBuzzNext = 1;
    float interpolationBuzz = 0.0;
    int maxNumPasosBuzz = 200;
    int numPasosBuzz = 0;

    std::vector<float> matrixBuzzJoints;
		std::vector<glm::mat4> matrixBuzz;
    ModelBuzz(/* args */);
    ~ModelBuzz();
    void LoadModel(Shader * shaderMulLighting);
    void render();
    void destroy();
};


#endif /* MODEL_H_ */