#include "Headers/ModelReward.h"

/*************************** Audio Init ************************************************/




/*************************** Init Model ************************************************/
ModelReward::ModelReward(std::string modelPath, glm::vec3 initPoss)
{
    
    modelMatrix[3].x = initalPoss.x;
    modelMatrix[3].y = initalPoss.y;
    modelMatrix[3].z = initalPoss.z;
    model = new Model();
    path=modelPath;

    //particulas
    particle = new ParticlesModel(modelMatrix);
   

    

}
ModelReward::ModelReward(std::string modelPath)
{
    model = new Model();
    path=modelPath;
    //particulas
    particle = new ParticlesModel(modelMatrix);
}
ModelReward::ModelReward(Model &vmodel)
{
    model = &vmodel;
    //particulas
    particle = new ParticlesModel(modelMatrix);
    
}

void ModelReward::LoadModelShader(Shader * shaderMulLighting)
{
    if (!path.empty())  
        model->loadModel(path);
	model->setShader(shaderMulLighting);
    particle->setShader();
}



/********************** Getter/Seter ************************************************/
void ModelReward::setScale(glm::vec3 newScale){
    scale.x = newScale.x;
    scale.y = newScale.y;
    scale.z = newScale.z;
}
void ModelReward::setScale(float newScale){
    scale.x = newScale;
    scale.y = newScale;
    scale.z = newScale;
}
glm::vec3 ModelReward::getScale(){
    return  scale;
}
void ModelReward::rotate(float newRotation){
    rotation += newRotation;
}
float ModelReward::getCurrentRotation(){
    return rotation;
}

void ModelReward::setTerrain(Terrain &newTerreno){
    terreno = &newTerreno;
    particle->setTerrain(newTerreno);
    //modelMatrix[3][1] = terreno->getHeightTerrain(modelMatrix[3][0],modelMatrix[3][2]);
}

/******************************* RENDER ****************************************************************/
void ModelReward::render(glm::mat4 proj, glm::mat4 view){
    moveTB();
    interpolationMovementHandler();
    movementDelayHandler();
    glm::mat4 modelMatrixBoddy = glm::mat4(modelMatrix);
    modelMatrixBoddy = glm::translate(modelMatrixBoddy, glm::vec3(0.0 ,0.5, 0.0));
    modelMatrixBoddy = glm::scale(modelMatrixBoddy, scale);
    modelMatrixBoddy = glm::rotate(modelMatrixBoddy,rotation,glm::vec3(0,1,0)); 
    //model->enableWireMode();
    model->render(modelMatrixBoddy);
    particle->loop(proj,view);
}



/************************ Movement ***********************************************************************/
void ModelReward::move(glm::vec3 move){
    modelMatrix[3][0] = move.x;
    modelMatrix[3][1] = move.y;
    modelMatrix[3][2] = move.z;
}

void ModelReward::moveTB(){
    if (position == TOP && moving==false)
    {
        modelMatrixGoal = glm::translate(modelMatrixGoal, glm::vec3(0.0 ,-verticalStride,0.0 ));
        position = BOT;
        moving = true;
    }
    else if (position == BOT && moving==false)
    {
        modelMatrixGoal = glm::translate(modelMatrixGoal, glm::vec3(0.0 ,verticalStride,0.0 ));
        position = TOP;
        moving = true;
    } 
}


void ModelReward::interpolationMovementHandler(){
    //Calcula las posiciones en y 
    //Movimiento vertical

    if (position==TOP)
    {
        modelMatrix[3][1] += 0.002; 
    }else if (position = BOT)
    {
        modelMatrix[3][1] -= 0.002; 
    }
    
    
    

}
void ModelReward::movementDelayHandler(){
    if (position==BOT && modelMatrix[3][1] <= modelMatrixGoal[3][1])
    {
        moving = false;
        modelMatrix[3][1] = modelMatrixGoal[3][1];
    }else if (position==TOP && modelMatrix[3][1] >= modelMatrixGoal[3][1])
    {
        moving = false;
        modelMatrix[3][1] = modelMatrixGoal[3][1];
    }
    
    
}


/***********************Destroy****************************/
void ModelReward::destroy(){
    model->destroy();
}

ModelReward::~ModelReward()
{
	model->destroy();
}