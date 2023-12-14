#include "Headers/ModelCharacter.h"



/*************************** Init Model ************************************************/
ModelCharacter::ModelCharacter(std::string modelPath)
{
    model = new Model();
    path=modelPath;
}
ModelCharacter::ModelCharacter(Model &vmodel)
{
    model = &vmodel;
    
}

void ModelCharacter::LoadModelShader(Shader * shaderMulLighting)
{
    if (!path.empty())  
        model->loadModel(path);
	model->setShader(shaderMulLighting);
}



/********************** Getter/Seter ************************************************/
void ModelCharacter::setScale(glm::vec3 newScale){
    scale.x = newScale.x;
    scale.y = newScale.y;
    scale.z = newScale.z;
}
void ModelCharacter::setScale(float newScale){
    scale.x = newScale;
    scale.y = newScale;
    scale.z = newScale;
}
glm::vec3 ModelCharacter::getScale(){
    return  scale;
}
void ModelCharacter::rotate(float newRotation){
    rotation += newRotation;
}
float ModelCharacter::getCurrentRotation(){
    return rotation;
}

void ModelCharacter::setTerrain(Terrain &newTerreno){
    terreno = &newTerreno;
}

/******************************* RENDER ****************************************************************/
void ModelCharacter::render(){
    interpolationMovementHandler();
    movementDelayHandler();
    glm::mat4 modelMatrixBoddy = glm::mat4(modelMatrix);
    modelMatrixBoddy = glm::translate(modelMatrixBoddy, glm::vec3(0.0 ,0.5, 0.0));
    modelMatrixBoddy = glm::scale(modelMatrixBoddy, scale);
    modelMatrixBoddy = glm::rotate(modelMatrixBoddy,rotation,glm::vec3(0,1,0)); 

    model->render(modelMatrixBoddy);
}



/************************ Movement ***********************************************************************/
void ModelCharacter::moveLeft(){
    if (position == Center && moving==false)
    {
        modelMatrixGoal = glm::translate(modelMatrixGoal, glm::vec3(horizontalStride ,0.0,0.0 ));
        position = Left;
        moving = true;
        time = TimeManager::Instance().GetTime();
    }
    else if (position == Right && moving==false)
    {
        modelMatrixGoal = glm::translate(modelMatrixGoal, glm::vec3(horizontalStride ,0.0,0.0 ));
        position = Center;
        moving = true;
        time = TimeManager::Instance().GetTime();
    } 
}
void ModelCharacter::moveRight(){
    if (position == Center && moving==false)
    {
        modelMatrixGoal = glm::translate(modelMatrixGoal, glm::vec3(-horizontalStride ,0.0,0.0 ));
        position = Right;
        moving = true;
        time = TimeManager::Instance().GetTime();
    }
    else if (position == Left && moving==false)
    {
        modelMatrixGoal = glm::translate(modelMatrixGoal, glm::vec3(-horizontalStride ,0.0,0.0 ));
        position = Center;
        moving = true;
        time = TimeManager::Instance().GetTime();
    } 
}
void ModelCharacter::jump(){
    if (!jumping)
    {
        jumping = true;
        t0 = TimeManager::Instance().GetTime();
        h0 = terreno->getHeightTerrain(modelMatrix[3][0],modelMatrix[3][2]);
    }
    
}
void ModelCharacter::bendDown(){
    if (jumping && !bending)
    {       
        bending = true;
        jumping = false;
        bend_t0 = TimeManager::Instance().GetTime();
        b_delay = true;
    }else if (!jumping && !bending && !b_delay)
    {
        bend = true;
        bending = true;
        bending_t0 = TimeManager::Instance().GetTime();
        this->scale.y = 0.1;
        model->setScaleAABB(glm::vec3(scaleModel));
        std::cout << "Shirnk" << std::endl;
    }
    
    
}

void ModelCharacter::interpolationMovementHandler(){
    //Calcula las posiciones en x,y 
    //Movimiento horizontal
    float f = modelMatrixGoal[3][0];
    float i = modelMatrix[3][0];
    modelMatrix[3][0] = glm::mix(f,i,0.5f); 

    //Movimiento vertical
    if (jumping)
    {
        double t = TimeManager::Instance().GetTime() - t0;
        double h = h0 + v0*t -0.5*g*t*t;
        modelMatrix[3][1] = float(h);
    }else if (!jumping && bending && !bend)
    {
        float t_h = terreno->getHeightTerrain(modelMatrix[3][0],modelMatrix[3][2]);
        float t_i = modelMatrix[3][1];
        modelMatrix[3][1] = glm::mix(t_h,t_i,0.5f);
    }else{
        modelMatrix[3][1] = terreno->getHeightTerrain(modelMatrix[3][0],modelMatrix[3][2]);
        
    }

    if (bend && !bending)
    {
        
        bend= false;
        this->scale.y = 0.4;
        model->setScaleAABB(glm::vec3(1/scaleModel));
        std::cout << "No Shirnk " << scale.y <<std::endl;
    }
    

}
void ModelCharacter::movementDelayHandler(){
    //Calcula los tiempos permitidos para moverse
    //Movimiento horizontal
    double currTime = TimeManager::Instance().GetTime();
    if ((currTime - time) > delay && moving)
    {
        moving = false;
    }
    if (!jumping && modelMatrix[3][1] <= terreno->getHeightTerrain(modelMatrix[3][0],modelMatrix[3][2]) && bending && !bend)
    {
        jumping = false;
        bending = false;
    }else if (jumping && modelMatrix[3][1] <= terreno->getHeightTerrain(modelMatrix[3][0],modelMatrix[3][2]))
    {
        jumping = false;
    }
    if(bending && jumping && bend){
        bending = false;
    }
    else if ((currTime - bending_t0) > bending_delay && bending){
        bending = false;
    }else if ((currTime - bend_t0> bend_delay))
    {
       b_delay = false;
    }
    
    
}


/***********************Destroy****************************/
void ModelCharacter::destroy(){
    model->destroy();
}

ModelCharacter::~ModelCharacter()
{
	model->destroy();
}









//V1

// void ModelCharacter::jump(){
//     if (!jumping)
//     {
//         jumping = true;
//         t0 = TimeManager::Instance().GetTime();
//         h0 = terreno->getHeightTerrain(modelMatrix[3][0],modelMatrix[3][2]);
//     }
    
// }
// void ModelCharacter::bendDown(){
//     if (jumping && !bending)
//     {
//         g *= g_scaler;
//         bending = true;
//     }else if (!jumping && !bending)
//     {
//         bend = true;
//         bending = true;
//         bending_t0 = TimeManager::Instance().GetTime();
//         scale.y *= scaleModel;
//         model->setScaleAABB(glm::vec3(scaleModel));
//     }
    
    
// }

// void ModelCharacter::interpolationMovementHandler(){
//     //Calcula las posiciones en x,y 
//     //Movimiento horizontal
//     float f = modelMatrixGoal[3][0];
//     float i = modelMatrix[3][0];
//     modelMatrix[3][0] = glm::mix(f,i,0.5f); 

//     //Movimiento vertical
//     if (jumping)
//     {
//         double t = TimeManager::Instance().GetTime() - t0;
//         double h = h0 + v0*t -0.5*g*t*t;
//         modelMatrix[3][1] = float(h);
//     }else{
//         modelMatrix[3][1] = terreno->getHeightTerrain(modelMatrix[3][0],modelMatrix[3][2]);
//         g = g_const;
//     }

//     if (bend && !bending)
//     {
//         bend = false;
//         scale.y /= scaleModel;
//         model->setScaleAABB(glm::vec3(1/scaleModel));
//     }
    

// }
// void ModelCharacter::movementDelayHandler(){
//     //Calcula los tiempos permitidos para moverse
//     //Movimiento horizontal
//     double currTime = TimeManager::Instance().GetTime();
//     if ((currTime - time) > delay && moving)
//     {
//         moving = false;
//     }
//     if (jumping && modelMatrix[3][1] <= terreno->getHeightTerrain(modelMatrix[3][0],modelMatrix[3][2]) && bending)
//     {
//         jumping = false;
//         bending = false;
//     }else if (jumping && modelMatrix[3][1] <= terreno->getHeightTerrain(modelMatrix[3][0],modelMatrix[3][2]))
//     {
//         jumping = false;
//     }
//     if(bending && jumping && bend){
//         bending = false;
//     }
//     else if ((currTime - bending_t0) > bending_delay && bending){
//         bending = false;
//     }
    
// }