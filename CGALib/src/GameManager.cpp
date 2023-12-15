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
    initAudio();
}
void GameManager::initAudio(){
    alutInit(0, nullptr);
	alListenerfv(AL_POSITION, listenerCharacterPos);
	alListenerfv(AL_VELOCITY, listenerCharacterVel);
	alListenerfv(AL_ORIENTATION, listenerCharacterOri);
	alGetError(); // clear any error messages
	if (alGetError() != AL_NO_ERROR) {
		printf("- Error creating buffers !!\n");
		exit(1);
	}
	else {
		printf("init() - No errors yet.");
	}
	// Generate buffers, or else no sound will happen!
	alGenBuffers(NUM_BUFFERS, buffer);
	buffer[0] = alutCreateBufferFromFile("../sounds/pickup.wav");
	int errorAlut = alutGetError();
	if (errorAlut != ALUT_ERROR_NO_ERROR){
		printf("- Error open files with alut %d !!\n", errorAlut);
		exit(2);
	}

	alGetError(); /* clear error */
	alGenSources(NUM_SOURCES, source);

	if (alGetError() != AL_NO_ERROR) {
		printf("- Error creating sources !!\n");
		exit(2);
	}
	else {
		printf("init - no errors after alGenSources\n");
	}
	alSourcef(source[0], AL_PITCH, 1.0f);
	alSourcef(source[0], AL_GAIN, 3.0f);
	alSourcefv(source[0], AL_POSITION, sourceEsmeraldPos);
	alSourcefv(source[0], AL_VELOCITY, sourceEsmeraldVel);
	alSourcei(source[0], AL_BUFFER, buffer[0]);
	alSourcei(source[0], AL_LOOPING, AL_FALSE);
	alSourcef(source[0], AL_MAX_DISTANCE, 2000);
}
void GameManager::playAudio(glm::mat4 esmeraldPoss){
        sourceEsmeraldPos[0] = esmeraldPoss[3].x;
		sourceEsmeraldPos[1] = esmeraldPoss[3].y;
		sourceEsmeraldPos[2] = esmeraldPoss[3].z;
		alSourcefv(source[0], AL_POSITION, sourceEsmeraldPos);

		

		// Listener for the Thris person camera
		listenerCharacterPos[0] = player->modelMatrix[3].x;
		listenerCharacterPos[1] = player->modelMatrix[3].y;
		listenerCharacterPos[2] = player->modelMatrix[3].z;
		alListenerfv(AL_POSITION, listenerCharacterPos);

		glm::vec3 upModel = glm::normalize(player->modelMatrix[1]);
		glm::vec3 frontModel = glm::normalize(player->modelMatrix[2]);

		listenerCharacterOri[0] = frontModel.x;
		listenerCharacterOri[1] = frontModel.y;
		listenerCharacterOri[2] = frontModel.z;
		listenerCharacterOri[3] = upModel.x;
		listenerCharacterOri[4] = upModel.y;
		listenerCharacterOri[5] = upModel.z;

		alListenerfv(AL_ORIENTATION, listenerCharacterOri);
        alSourcePlay(source[0]);

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
                    if(!(rewards[idx]->particle->showing))
                        playAudio(rewards[idx]->modelMatrix);
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