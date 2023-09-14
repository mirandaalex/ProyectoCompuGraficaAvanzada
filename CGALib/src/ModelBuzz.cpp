#include "Headers/ModelBuzz.h"


ModelBuzz::ModelBuzz(/* args */)
{
}

ModelBuzz::~ModelBuzz()
{
    //Destroy Buzz
	modelBuzzHead.destroy();
	modelBuzzHip.destroy();
	modelBuzzLeftArm.destroy();
	modelBuzzLeftCalf.destroy();
	modelBuzzLeftFoot.destroy();
	modelBuzzLeftForearm.destroy();
	modelBuzzLeftHand.destroy();
	modelBuzzLeftThigh.destroy();
	modelBuzzLeftWing1.destroy();
	modelBuzzLeftWing2.destroy();
	modelBuzzRightArm.destroy();
	modelBuzzRightCalf.destroy();
	modelBuzzRightFoot.destroy();
	modelBuzzRightForearm.destroy();
	modelBuzzRightHand.destroy();
	modelBuzzRightThigh.destroy();
	modelBuzzRightWing1.destroy();
	modelBuzzRightWing2.destroy();
	modelBuzzTorso.destroy();
}


void ModelBuzz::LoadModel(Shader * shaderMulLighting){
    //model Buzz
	modelBuzzHead.loadModel("../models/buzz/buzzlightyHead.obj");
	modelBuzzHip.loadModel("../models/buzz/buzzlightyHip.obj");
	modelBuzzLeftArm.loadModel("../models/buzz/buzzlightyLeftArm.obj");
	modelBuzzLeftCalf.loadModel("../models/buzz/buzzlightyLeftCalf.obj");
	modelBuzzLeftFoot.loadModel("../models/buzz/buzzlightyLeftFoot.obj");
	modelBuzzLeftForearm.loadModel("../models/buzz/buzzlightyLeftForearm.obj");
	modelBuzzLeftHand.loadModel("../models/buzz/buzzlightyLeftHand.obj");
	modelBuzzLeftThigh.loadModel("../models/buzz/buzzlightyLeftThigh.obj");
	modelBuzzLeftWing1.loadModel("../models/buzz/buzzlightyLeftWing1.obj");
	modelBuzzLeftWing2.loadModel("../models/buzz/buzzlightyLeftWing2.obj");
	modelBuzzRightArm.loadModel("../models/buzz/buzzlightyRightArm.obj");
	modelBuzzRightCalf.loadModel("../models/buzz/buzzlightyRightCalf.obj");
	modelBuzzRightFoot.loadModel("../models/buzz/buzzlightyRightFoot.obj");
	modelBuzzRightForearm.loadModel("../models/buzz/buzzlightyRightForearm.obj");
	modelBuzzRightHand.loadModel("../models/buzz/buzzlightyRightHand.obj");
	modelBuzzRightThigh.loadModel("../models/buzz/buzzlightyRightThigh.obj");
	modelBuzzRightWing1.loadModel("../models/buzz/buzzlightyRightWing1.obj");
	modelBuzzRightWing2.loadModel("../models/buzz/buzzlightyRightWing2.obj");
	modelBuzzTorso.loadModel("../models/buzz/buzzlightyTorso.obj");
	
	modelBuzzHead.setShader(shaderMulLighting);
	modelBuzzHip.setShader(shaderMulLighting);
	modelBuzzLeftArm.setShader(shaderMulLighting);
	modelBuzzLeftCalf.setShader(shaderMulLighting);
	modelBuzzLeftFoot.setShader(shaderMulLighting);
	modelBuzzLeftForearm.setShader(shaderMulLighting);
	modelBuzzLeftHand.setShader(shaderMulLighting);
	modelBuzzLeftThigh.setShader(shaderMulLighting);
	modelBuzzLeftWing1.setShader(shaderMulLighting);
	modelBuzzLeftWing2.setShader(shaderMulLighting);
	modelBuzzRightArm.setShader(shaderMulLighting);
	modelBuzzRightCalf.setShader(shaderMulLighting);
	modelBuzzRightFoot.setShader(shaderMulLighting);
	modelBuzzRightForearm.setShader(shaderMulLighting);
	modelBuzzRightHand.setShader(shaderMulLighting);
	modelBuzzRightThigh.setShader(shaderMulLighting);
	modelBuzzRightWing1.setShader(shaderMulLighting);
	modelBuzzRightWing2.setShader(shaderMulLighting);
	modelBuzzTorso.setShader(shaderMulLighting);
}
void ModelBuzz::render(){
    //buzz
    //gerarquia
    glm::mat4 modelMatrixBuzzTorso = glm::mat4(modelMatrixBuzz);
    modelMatrixBuzzTorso = glm::scale(modelMatrixBuzzTorso, glm::vec3(3.0f));
    
    glm::mat4 modelMatrixBuzzHead = glm::mat4(modelMatrixBuzzTorso);
    modelMatrixBuzzHead = glm::translate(modelMatrixBuzzHead, glm::vec3(0.001533 ,0.6223,-0.001929 ));
    modelMatrixBuzzHead = glm::rotate(modelMatrixBuzzHead,rotBuzzHead,glm::vec3(0,1,0));
    modelMatrixBuzzHead = glm::translate(modelMatrixBuzzHead, glm::vec3(-0.001533 ,-0.6223,0.001929));
    
    glm::mat4 modelMatrixBuzzLeftArm = glm::mat4(modelMatrixBuzzTorso);
    modelMatrixBuzzLeftArm = glm::translate(modelMatrixBuzzLeftArm, glm::vec3(0.134494,0.578733,-0.026198));
    modelMatrixBuzzLeftArm = glm::rotate(modelMatrixBuzzLeftArm,rotBuzzLeftArm,glm::vec3(1,0,0));
    modelMatrixBuzzLeftArm = glm::translate(modelMatrixBuzzLeftArm, glm::vec3(-0.134494,-0.578733,0.026198));	

    glm::mat4 modelMatrixBuzzRightArm = glm::mat4(modelMatrixBuzzTorso);
    modelMatrixBuzzRightArm = glm::translate(modelMatrixBuzzRightArm, glm::vec3(-0.133,0.578632,-0.0263));
    modelMatrixBuzzRightArm = glm::rotate(modelMatrixBuzzRightArm,rotBuzzRightArm,glm::vec3(1,0,0));
    modelMatrixBuzzRightArm = glm::translate(modelMatrixBuzzRightArm, glm::vec3(0.133,-0.578632,0.0263));

    glm::mat4 modelMatrixBuzzHip = glm::mat4(modelMatrixBuzzTorso);
    modelMatrixBuzzHip = glm::translate(modelMatrixBuzzHip, glm::vec3(0.002261,0.478766,-0.000326));
    modelMatrixBuzzHip = glm::rotate(modelMatrixBuzzHip,rotBuzzHip,glm::vec3(0,1,0));
    modelMatrixBuzzHip = glm::translate(modelMatrixBuzzHip, glm::vec3(-0.002261,-0.478766,0.000326));

    glm::mat4 modelMatrixBuzzLeftWing1 = glm::mat4(modelMatrixBuzzTorso);
    glm::mat4 modelMatrixBuzzRightWing1 = glm::mat4(modelMatrixBuzzTorso);

    glm::mat4 modelMatrixBuzzLeftForearm = glm::mat4(modelMatrixBuzzLeftArm);
    modelMatrixBuzzLeftForearm = glm::translate(modelMatrixBuzzLeftForearm, glm::vec3(0.273375 ,0.578534,0.009877));
    modelMatrixBuzzLeftForearm = glm::rotate(modelMatrixBuzzLeftForearm,rotBuzzLeftForearm,glm::vec3(0,1,0));
    modelMatrixBuzzLeftForearm = glm::translate(modelMatrixBuzzLeftForearm, glm::vec3(-0.273375 ,-0.578534,-0.009877));

    glm::mat4 modelMatrixBuzzRightForearm = glm::mat4(modelMatrixBuzzRightArm);
    modelMatrixBuzzRightForearm = glm::translate(modelMatrixBuzzRightForearm, glm::vec3(-0.262414,0.578534,0.008242));
    modelMatrixBuzzRightForearm = glm::rotate(modelMatrixBuzzRightForearm,rotBuzzRightForearm,glm::vec3(0,1,0));
    modelMatrixBuzzRightForearm = glm::translate(modelMatrixBuzzRightForearm, glm::vec3(0.262414,-0.578534,-0.008242));

    glm::mat4 modelMatrixBuzzLeftThigh = glm::mat4(modelMatrixBuzzHip);
    modelMatrixBuzzLeftThigh = glm::translate(modelMatrixBuzzLeftThigh, glm::vec3(0.060687,0.396263,0.005383));
    modelMatrixBuzzLeftThigh = glm::rotate(modelMatrixBuzzLeftThigh,rotBuzzLeftThigh,glm::vec3(1,0,0));
    modelMatrixBuzzLeftThigh = glm::translate(modelMatrixBuzzLeftThigh, glm::vec3(-0.060687,-0.396263,-0.005383));	

    glm::mat4 modelMatrixBuzzRightThigh = glm::mat4(modelMatrixBuzzHip);
    modelMatrixBuzzRightThigh = glm::translate(modelMatrixBuzzRightThigh, glm::vec3(-0.057136,0.396263,0.005383));
    modelMatrixBuzzRightThigh = glm::rotate(modelMatrixBuzzRightThigh,rotBuzzRightThigh,glm::vec3(1,0,0));
    modelMatrixBuzzRightThigh = glm::translate(modelMatrixBuzzRightThigh, glm::vec3(0.057136,-0.396263,-0.005383));
    
    glm::mat4 modelMatrixBuzzRightWing2 = glm::mat4(modelMatrixBuzzRightWing1);
    glm::mat4 modelMatrixBuzzLeftWing2 = glm::mat4(modelMatrixBuzzLeftWing1);
    
    glm::mat4 modelMatrixBuzzLeftHand = glm::mat4(modelMatrixBuzzLeftForearm);
    //modelMatrixBuzzLeftHand = glm::translate(modelMatrixBuzzLeftHand, glm::vec3(0));
    //modelMatrixBuzzLeftHand = glm::rotate(modelMatrixBuzzLeftHand,rotBuzzLeftHand,glm::vec3(1,0,0));
    //modelMatrixBuzzLeftHand = glm::translate(modelMatrixBuzzLeftHand, glm::vec3(0));

    glm::mat4 modelMatrixBuzzRightHand = glm::mat4(modelMatrixBuzzRightForearm);
    //modelMatrixBuzzRightHand = glm::translate(modelMatrixBuzzRightHand, glm::vec3(0));
    //modelMatrixBuzzRightHand = glm::rotate(modelMatrixBuzzRightHand,rotBuzzRightHand,glm::vec3(1,0,0));
    //modelMatrixBuzzRightHand = glm::translate(modelMatrixBuzzRightHand, glm::vec3(0));	

    glm::mat4 modelMatrixBuzzLeftCalf = glm::mat4(modelMatrixBuzzLeftThigh);
    modelMatrixBuzzLeftCalf = glm::translate(modelMatrixBuzzLeftCalf, glm::vec3(0.064331,0.254112,-0.00069));
    modelMatrixBuzzLeftCalf = glm::rotate(modelMatrixBuzzLeftCalf,rotBuzzLeftCalf,glm::vec3(1,0,0));
    modelMatrixBuzzLeftCalf = glm::translate(modelMatrixBuzzLeftCalf, glm::vec3(-0.064331,-0.254112,0.00069));
    /*																	-x			-z		y*/

    glm::mat4 modelMatrixBuzzRightCalf = glm::mat4(modelMatrixBuzzRightThigh);
    modelMatrixBuzzRightCalf = glm::translate(modelMatrixBuzzRightCalf, glm::vec3(-0.064331,0.254112,-0.00069));
    modelMatrixBuzzRightCalf = glm::rotate(modelMatrixBuzzRightCalf,rotBuzzRightCalf,glm::vec3(1,0,0));
    modelMatrixBuzzRightCalf = glm::translate(modelMatrixBuzzRightCalf, glm::vec3(0.064331,-0.254112,0.00069));

    glm::mat4 modelMatrixBuzzLeftFoot = glm::mat4(modelMatrixBuzzLeftCalf);
    //modelMatrixBuzzLeftFoot = glm::translate(modelMatrixBuzzLeftFoot, glm::vec3(0));
    //modelMatrixBuzzLeftFoot = glm::rotate(modelMatrixBuzzLeftFoot,rotBuzzLeftFoot,glm::vec3(1,0,0));
    //modelMatrixBuzzLeftFoot = glm::translate(modelMatrixBuzzLeftFoot, glm::vec3(0));

    glm::mat4 modelMatrixBuzzRightFoot = glm::mat4(modelMatrixBuzzRightCalf);
    //modelMatrixBuzzRightFoot = glm::translate(modelMatrixBuzzRightFoot, glm::vec3(0));
    //modelMatrixBuzzRightFoot = glm::rotate(modelMatrixBuzzRightFoot,rotBuzzRightFoot,glm::vec3(1,0,0));
    //modelMatrixBuzzRightFoot = glm::translate(modelMatrixBuzzRightFoot, glm::vec3(0));
    
    //Render Buzz
    modelBuzzTorso.render(modelMatrixBuzzTorso);
    
    modelBuzzHead.render(modelMatrixBuzzHead);
    modelBuzzLeftArm.render(modelMatrixBuzzLeftArm);
    modelBuzzRightArm.render(modelMatrixBuzzRightArm);
    modelBuzzHip.render(modelMatrixBuzzHip);
    modelBuzzLeftWing1.render(modelMatrixBuzzLeftWing1);
    modelBuzzRightWing1.render(modelMatrixBuzzRightWing1);

    modelBuzzLeftForearm.render(modelMatrixBuzzLeftForearm);
    modelBuzzRightForearm.render(modelMatrixBuzzRightForearm);
    modelBuzzLeftThigh.render(modelMatrixBuzzLeftThigh);
    modelBuzzRightThigh.render(modelMatrixBuzzRightThigh);
    modelBuzzRightWing2.render(modelMatrixBuzzRightWing2);
    modelBuzzLeftWing2.render(modelMatrixBuzzLeftWing2);
    
    modelBuzzLeftHand.render(modelMatrixBuzzLeftHand);
    modelBuzzRightHand.render(modelMatrixBuzzRightHand);
    modelBuzzLeftCalf.render(modelMatrixBuzzLeftCalf);
    modelBuzzRightCalf.render(modelMatrixBuzzRightCalf);

    modelBuzzLeftFoot.render(modelMatrixBuzzLeftFoot);
    modelBuzzRightFoot.render(modelMatrixBuzzRightFoot);

}
void ModelBuzz::destroy(){
    //Destroy Buzz
	modelBuzzHead.destroy();
	modelBuzzHip.destroy();
	modelBuzzLeftArm.destroy();
	modelBuzzLeftCalf.destroy();
	modelBuzzLeftFoot.destroy();
	modelBuzzLeftForearm.destroy();
	modelBuzzLeftHand.destroy();
	modelBuzzLeftThigh.destroy();
	modelBuzzLeftWing1.destroy();
	modelBuzzLeftWing2.destroy();
	modelBuzzRightArm.destroy();
	modelBuzzRightCalf.destroy();
	modelBuzzRightFoot.destroy();
	modelBuzzRightForearm.destroy();
	modelBuzzRightHand.destroy();
	modelBuzzRightThigh.destroy();
	modelBuzzRightWing1.destroy();
	modelBuzzRightWing2.destroy();
	modelBuzzTorso.destroy();
}