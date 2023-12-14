#include "Headers/GameManager.h"


GameManager::GameManager(){

}
GameManager::~GameManager(){

}

GameManager::GameManager(bool vDrawColiders){
    drawColiders = vDrawColiders;
}
GameManager::GameManager(bool vDrawColiders, glm::vec4 vcolor){
    drawColiders = vDrawColiders;
    color = vcolor;
}
/************************Setters*********************************************/
void GameManager::setShader(Shader * shaderMulLighting){
    boxCollider.init();
	boxCollider.setShader(shaderMulLighting);
	boxCollider.setColor(color);
    shaderInit = true;

}
void GameManager::setDrawColiders(bool vColiders){
    drawColiders = vColiders;
}
void  GameManager::add(ModelCharacter &ply1){
    player = &ply1;

}
void  GameManager::add(ModelReward &rw){
    rewards.push_back(&rw);

}
/************************Loop*************************************************/
void GameManager::loop(){
    updateColliders();
    std::map<std::string, bool> collisionDetection = detectColision();
    handleColision(collisionDetection);
    if(drawColiders && shaderInit) drawWireColiders();
}


/*************************Colisiones**************************************************/
/*1*/
void GameManager::handleColision(
std::map<std::string, bool> collisionDetection){

}

/*2*/
std::map<std::string, bool> GameManager::detectColision(){

    std::map<std::string, bool> collisionDetection;

    for (std::map<std::string,
    std::tuple<AbstractModel::OBB, glm::mat4, glm::mat4>>::iterator it =
    collidersOBB.begin(); it != collidersOBB.end(); it++) {
        bool isColision = false;
        for (std::map<std::string,
            std::tuple<AbstractModel::OBB, glm::mat4, glm::mat4>>::iterator jt =
            collidersOBB.begin(); jt != collidersOBB.end(); jt++) {
            if (it != jt && it->first.substr(0,6) !=jt->first.substr(0,6) &&
                testOBBOBB(std::get<0>(it->second), std::get<0>(jt->second))) {
                // std::cout << "Hay colision entre " << it->first << " y el modelo " <<
                //     jt->first << std::endl;
                isColision = true;
                if (it->first.substr(0,6) == "reward")
                {
                    
                    int idx = std::stoi((it->first.substr(7)));
                    rewards[idx]->particle->DrawParticles();
                }
                
            }
        }
        addOrUpdateCollisionDetection(collisionDetection, it->first, isColision);
    }

    return collisionDetection;
}

/*3*/
void GameManager::updateColliders(){
    //Player
    AbstractModel::OBB modelCollider;
    glm::mat4 modelmatrixCollider = glm::mat4(player->modelMatrix);
    // Set the orientation of collider before doing the scale
    modelCollider.u = glm::quat_cast(modelmatrixCollider);
    modelmatrixCollider = glm::translate(modelmatrixCollider, glm::vec3(0.0,0.5,0.0));
    modelmatrixCollider = glm::scale(modelmatrixCollider, player->getScale());
    modelmatrixCollider = glm::translate(modelmatrixCollider,
            glm::vec3(player->model->getObb().c.x,
                    player->model->getObb().c.y,
                    player->model->getObb().c.z));
    modelCollider.e = player->model->getObb().e * player->getScale();
    modelCollider.c = glm::vec3(modelmatrixCollider[3]);
    addOrUpdateColliders(collidersOBB, "player", modelCollider, player->modelMatrix);
    
    //Rewards
    for (size_t i = 0; i < rewards.size(); i++)
    {
        ModelReward* rw = rewards[i];
        AbstractModel::OBB modelCollider;
        glm::mat4 modelmatrixCollider = glm::mat4(rw->modelMatrix);
        // Set the orientation of collider before doing the scale
        modelCollider.u = glm::quat_cast(modelmatrixCollider);
        modelmatrixCollider = glm::scale(modelmatrixCollider, rw->getScale());
        modelmatrixCollider = glm::translate(modelmatrixCollider,
                glm::vec3(rw->model->getObb().c.x,
                        rw->model->getObb().c.y,
                        rw->model->getObb().c.z));
        modelmatrixCollider = glm::translate(modelmatrixCollider, glm::vec3(0.0,0.5,0.0));
        modelCollider.e = rw->model->getObb().e * rw->getScale();
        modelCollider.c = glm::vec3(modelmatrixCollider[3]);
        addOrUpdateColliders(collidersOBB, "reward_" + std::to_string(i), modelCollider, rw->modelMatrix);
    }
    
}

/*4*/
void GameManager::drawWireColiders(){
    for (std::map<std::string, std::tuple<AbstractModel::OBB, glm::mat4, glm::mat4> >::iterator it =
        collidersOBB.begin(); it != collidersOBB.end(); it++) {
        glm::mat4 matrixCollider = glm::mat4(1.0);
        matrixCollider = glm::translate(matrixCollider, std::get<0>(it->second).c);
        matrixCollider = matrixCollider * glm::mat4(std::get<0>(it->second).u);
        matrixCollider = glm::scale(matrixCollider, std::get<0>(it->second).e * 2.0f);
        boxCollider.setColor(color);
        boxCollider.enableWireMode();
        boxCollider.render(matrixCollider);
    }
}