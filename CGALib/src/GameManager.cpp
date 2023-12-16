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
void GameManager::setShader(Shader *vshaderMulLighting){
    shader = vshaderMulLighting;
    boxCollider.init();
	boxCollider.setShader(shader);
	boxCollider.setColor(color);
    shaderInit = true;
    initAudio();
}
void GameManager::setTerrain(Terrain &Terrainv){
    terreno = &Terrainv;
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
	buffer[1] = alutCreateBufferFromFile("../sounds/explosion1.wav");
    buffer[2] = alutCreateBufferFromFile("../sounds/minecraft.wav");
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
	
    alSourcef(source[1], AL_PITCH, 1.0f);
	alSourcef(source[1], AL_GAIN, 0.25f);
	alSourcefv(source[1], AL_POSITION, sourceObstPos);
	alSourcefv(source[1], AL_VELOCITY, sourceObstVel);
	alSourcei(source[1], AL_BUFFER, buffer[1]);
	alSourcei(source[1], AL_LOOPING, AL_FALSE);
	alSourcef(source[1], AL_MAX_DISTANCE, 2000);

    alSourcef(source[2], AL_PITCH, 1.0f);
	alSourcef(source[2], AL_GAIN, 2.0f);
	alSourcefv(source[2], AL_POSITION, sourceAmbPos);
	alSourcefv(source[2], AL_VELOCITY, sourceAmbVel);
	alSourcei(source[2], AL_BUFFER, buffer[2]);
	alSourcei(source[2], AL_LOOPING, AL_TRUE);
	alSourcef(source[2], AL_MAX_DISTANCE, 2000);

    sourceAmbPos[0] = 0;
    sourceAmbPos[1] = 1;
    sourceAmbPos[2] = 1;
    alSourcefv(source[2], AL_POSITION, sourceAmbPos);
    listenerCharacterPos[0] = 0;
    listenerCharacterPos[1] = 1;
    listenerCharacterPos[2] = 0;
    alListenerfv(AL_POSITION, listenerCharacterPos);

    glm::vec3 upModel = glm::normalize(glm::vec3(0,1,0));
    glm::vec3 frontModel = glm::normalize(glm::vec3(0,0,-1));

    listenerCharacterOri[0] = frontModel.x;
    listenerCharacterOri[1] = frontModel.y;
    listenerCharacterOri[2] = frontModel.z;
    listenerCharacterOri[3] = upModel.x;
    listenerCharacterOri[4] = upModel.y;
    listenerCharacterOri[5] = upModel.z;
    alListenerfv(AL_ORIENTATION, listenerCharacterOri);
    alSourcePlay(source[2]);
}
void GameManager::playAudio(glm::mat4 esmeraldPoss, int idx){
        //ALfloat objposs[] ={esmeraldPoss[3].x,esmeraldPoss[3].y,esmeraldPoss[3].z};
        if(idx==0){
        sourceEsmeraldPos[0] = esmeraldPoss[3].x;
		sourceEsmeraldPos[1] = esmeraldPoss[3].y;
		sourceEsmeraldPos[2] = esmeraldPoss[3].z;
		alSourcefv(source[0], AL_POSITION, sourceEsmeraldPos);
        }else if (idx==1)
        {
        sourceObstPos[0] = esmeraldPoss[3].x;
		sourceObstPos[1] = esmeraldPoss[3].y;
		sourceObstPos[2] = esmeraldPoss[3].z;
		alSourcefv(source[1], AL_POSITION, sourceObstPos);      
        }

		// Listener for the Thris person camera
		// listenerCharacterPos[0] = player->modelMatrix[3].x;
		// listenerCharacterPos[1] = player->modelMatrix[3].y;
		// listenerCharacterPos[2] = player->modelMatrix[3].z;
		// alListenerfv(AL_POSITION, listenerCharacterPos);

		// glm::vec3 upModel = glm::normalize(player->modelMatrix[1]);
		// glm::vec3 frontModel = glm::normalize(player->modelMatrix[2]);

		// listenerCharacterOri[0] = frontModel.x;
		// listenerCharacterOri[1] = frontModel.y;
		// listenerCharacterOri[2] = frontModel.z;
		// listenerCharacterOri[3] = upModel.x;
		// listenerCharacterOri[4] = upModel.y;
		// listenerCharacterOri[5] = upModel.z;

		alListenerfv(AL_ORIENTATION, listenerCharacterOri);
        if (idx==0)
        {
        alSourcePlay(source[0]);
            /* code */
        }else if (idx==1)
        {
        alSourcePlay(source[1]);
            /* code */
        }
        
        

}


void GameManager::setDrawColiders(bool vColiders){
    drawColiders = vColiders;
}
void  GameManager::add(ModelCharacter &ply1){
    player = &ply1;

}
void  GameManager::add(ModelReward *rw){
    rewards.push_back(rw);

}

void  GameManager::add(ModelObstacle *obst){
    obstacles.push_back(obst);

}
/************************Loop*************************************************/
void GameManager::loop(glm::mat4& proj,glm::mat4& view){
    updateColliders();
    std::map<std::string, bool> collisionDetection = detectColision();
    handleColision(collisionDetection);
    if(drawColiders && shaderInit) drawWireColiders();
    if(vivo){
        handlerObjts(proj,view);
        upscore();}
    if(estado==Moviendo)rendObjts(proj,view);
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
                if (it->first.substr(0,6) == "reward" && jt->first == "player")
                {
                    
                    int idx = std::stoi((it->first.substr(7)));
                    if(checkColiderValidRewards(idx)){
                        if(!(rewards[idx]->particle->showing))
                            playAudio(rewards[idx]->modelMatrix,0);
                        if(idx == 0){
                            glm::vec3 poss(-2,terreno->getHeightTerrain(-2,0)+1.0f,0);
                            rewards[idx]->particle->DrawParticles(poss);
                            // rewards[idx]->move(glm::vec3(-30));
                            // aux0=NON;
                        }else if(idx == 1){
                            glm::vec3 poss(0,terreno->getHeightTerrain(0,0)+1.0f,0);
                            rewards[idx]->particle->DrawParticles(poss);
                            // rewards[idx]->move(glm::vec3(-30));
                            // aux1=NON;
                        }else if(idx == 2){
                            glm::vec3 poss(2,terreno->getHeightTerrain(2,0)+1.0f,0);
                            rewards[idx]->particle->DrawParticles(poss);
                            // rewards[idx]->move(glm::vec3(-30));
                            // aux2=NON;
                        }
                        score+=1;
                    }
                }
                else if (it->first.substr(0,6) == "obstac" && vivo &&jt->first == "player" )
                { //colisiones con  obstacles
                    int idx = std::stoi((it->first.substr(9)));
                    if(checkColiderValidObstacle(idx)){
                        playAudio(obstacles[idx]->modelMatrix,1);
                        vivo = false;
                        vidas--;
                    }
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
        modelmatrixCollider = glm::translate(modelmatrixCollider, rw->movvec);
        modelCollider.e = rw->model->getObb().e * rw->getScale();
        modelCollider.c = glm::vec3(modelmatrixCollider[3]);
        addOrUpdateColliders(collidersOBB, "reward_" + std::to_string(i), modelCollider, rw->modelMatrix);
    }

    //obstacles
    for (size_t i = 0; i < obstacles.size(); i++)
    {
        ModelObstacle* obst = obstacles[i];
        AbstractModel::OBB modelCollider;
        glm::mat4 modelmatrixCollider = glm::mat4(obst->modelMatrix);
        // Set the orientation of collider before doing the scale
        modelCollider.u = glm::quat_cast(modelmatrixCollider);
        modelmatrixCollider = glm::scale(modelmatrixCollider, obst->getScale());
        modelmatrixCollider = glm::translate(modelmatrixCollider,
                glm::vec3(obst->model->getObb().c.x,
                        obst->model->getObb().c.y,
                        obst->model->getObb().c.z));
        modelmatrixCollider = glm::translate(modelmatrixCollider, obst->movvec);
        modelCollider.e = obst->model->getObb().e * obst->getScale();
        modelCollider.c = glm::vec3(modelmatrixCollider[3]);
        addOrUpdateColliders(collidersOBB, "obstacle_" + std::to_string(i), modelCollider, obst->modelMatrix);
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

bool GameManager::checkColiderValidRewards(int idx){
    if(idx==0){
        return (aux0==REW);
    }else if(idx==1){
        return (aux1==REW);
    }else if(idx==2){
        return (aux2==REW);
    }
    return false;
}
bool GameManager::checkColiderValidObstacle(int idx){
    if(idx==0){
        return (aux0==OBS);
    }else if(idx==1){
        return (aux1==OBS);
    }else if(idx==2){
        return (aux2==OBS);
    }
    return false;
}
void GameManager::upscore(){
    scoret0 = TimeManager::Instance().GetTime();

    if (scoret0-scoret1 > scoretdelay)
    {
        score++;
        scoret1 = scoret0;
        std::cout << "Score: " << score << std::endl;
    }
    
}
void GameManager::make_tuple(){
    
    aux0 = possibilities(std::rand()%3);
    aux1 = possibilities(std::rand()%3);
    aux2 = possibilities(std::rand()%3);
    
    

}
void GameManager::reset_tuple(){
    currPoss = initPoss;
    aux0 = NON;
    aux1 = NON;
    aux2 = NON;

    float h = terreno->getHeightTerrain(positionDesplazamiento[0],currPoss);
    glm::vec3 tmp(positionDesplazamiento[0],1.0f,currPoss);
    rew0->move(tmp);

    h = terreno->getHeightTerrain(positionDesplazamiento[0],currPoss);
    tmp = glm::vec3(positionDesplazamiento[0],1.0f,currPoss);
    obs0->move(tmp);

    h = terreno->getHeightTerrain(positionDesplazamiento[1],currPoss);
    tmp = glm::vec3(positionDesplazamiento[1],1.0f,currPoss);
    rew1->move(tmp);

    h = terreno->getHeightTerrain(positionDesplazamiento[1],currPoss);
    tmp = glm::vec3(positionDesplazamiento[1],1.0f,currPoss);
    obs1->move(tmp);

    
    h = terreno->getHeightTerrain(positionDesplazamiento[2],currPoss);
    tmp =  glm::vec3(positionDesplazamiento[2],1.0f,currPoss);
    rew2->move(tmp);
    
    h = terreno->getHeightTerrain(positionDesplazamiento[2],currPoss);
    tmp = glm::vec3(positionDesplazamiento[2],1.0f,currPoss);
    obs2->move(tmp);
       
}
void GameManager::rendObjts(glm::mat4 proj,glm::mat4 view){
    if(aux0 == REW){
        rew0->render(proj,view);

    }else if(aux0 == OBS){
        
        obs0->render(proj,view);
    }
    if(aux1 == REW){

        rew1->render(proj,view);
        
    }else if(aux1 == OBS){
        
        obs1->render(proj,view);
    }
    if(aux2 == REW){
        
        rew2->render(proj,view);
        
    }else if(aux2 == OBS){
        obs2->render(proj,view);
    }   
}

void GameManager::movObjts(){
    if(aux0 == REW){
        float h = terreno->getHeightTerrain(positionDesplazamiento[0],currPoss);
        glm::vec3 tmp(positionDesplazamiento[0],1.0f,currPoss);
        rew0->move(tmp);
    }else if(aux0 == OBS){
        float h = terreno->getHeightTerrain(positionDesplazamiento[0],currPoss);
        glm::vec3 tmp(positionDesplazamiento[0],1.0f,currPoss);
        obs0->move(tmp);
    }
    if(aux1 == REW){
        float h = terreno->getHeightTerrain(positionDesplazamiento[1],currPoss);
        glm::vec3 tmp(positionDesplazamiento[1],1.0f,currPoss);
        rew1->move(tmp);
    }else if(aux1 == OBS){     
        float h = terreno->getHeightTerrain(positionDesplazamiento[1],currPoss);
        glm::vec3 tmp(positionDesplazamiento[1],1.0f,currPoss);
        obs1->move(tmp);
    }
    if(aux2 == REW){    
        float h = terreno->getHeightTerrain(positionDesplazamiento[2],currPoss);
        glm::vec3 tmp(positionDesplazamiento[2],1.0f,currPoss);
        rew2->move(tmp);
        
    }else if(aux2 == OBS){
        float h = terreno->getHeightTerrain(positionDesplazamiento[2],currPoss);
        glm::vec3 tmp(positionDesplazamiento[2],1.0f,currPoss);
        obs2->move(tmp);
    }   
}

void GameManager::handlerObjts(glm::mat4 proj,glm::mat4 view){
    if(estado == Iniciando){
        make_tuple();
        genObjs(proj,view);
        estado = Moviendo;
        // estado = temp;
        currPoss = initPoss;
    }else if (estado == Moviendo) 
    {
        movObjts();
        if (meta-currPoss>0.0f)
        {
            currPoss += stride * vel;
        }else{
            estado = Meta;
        }
        
    }else if (estado == Meta)
    {
        reset_tuple();
        make_tuple();
        vel+=aceleracion;
        estado = Moviendo;
    }
    
    
}

void GameManager::genObjs(glm::mat4 proj,glm::mat4 view){

        scoret0=TimeManager::Instance().GetTime();
        scoret1=TimeManager::Instance().GetTime();

        rew0 = new ModelReward("../models/Minecraft/esmeralda.fbx",glm::vec3(0,50.0,0));
        rew0->LoadModelShader(shader);
        rew0->setTerrain(*terreno);
        rew0->setScale(1.0f);;
        rew0->render(proj, view);
        add(rew0);        
        
        obs0 = new ModelObstacle("../models/Minecraft/grass.fbx",glm::vec3(0,50.0,0));
        obs0->LoadModelShader(shader);
        obs0->setTerrain(*terreno);
        obs0->setScale(1.0f);
        obs0->render(proj, view);
        add(obs0);   

        rew1 = new ModelReward("../models/Minecraft/esmeralda.fbx",glm::vec3(0,50.0,0));
        rew1->LoadModelShader(shader);
        rew1->setTerrain(*terreno);
        rew1->setScale(1.0f);
        rew1->render(proj, view);
        add(rew1);  

        obs1 = new ModelObstacle("../models/Minecraft/grass.fbx",glm::vec3(0,50.0,0));
        obs1->LoadModelShader(shader);
        obs1->setTerrain(*terreno);
        obs1->setScale(1.0f);
        obs1->render(proj, view);
        add(obs1);  

        rew2 = new ModelReward("../models/Minecraft/esmeralda.fbx",glm::vec3(0,50.0,0));
        rew2->LoadModelShader(shader);
        rew2->setTerrain(*terreno);
        rew2->setScale(1.0f);
        rew2->render(proj, view);
        add(rew2);  

        obs2 = new ModelObstacle("../models/Minecraft/grass.fbx",glm::vec3(0,50.0,0));
        obs2->LoadModelShader(shader);
        obs2->setTerrain(*terreno);
        obs2->setScale(1.0f);
        obs2->render(proj, view);
        add(obs2);       
}

void GameManager::revivir(){
    if(vidas > 0){
        vivo = true;
        estado = Meta;
        vel -=aceleracion;
        reset_tuple();
    }else{
        vivo = true;
        estado = Meta;
        score = 0;
        vel = velI;
        vidas = 3;
        reset_tuple();
    }
}