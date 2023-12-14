#include "Headers/ParticlesModel.h"


ParticlesModel::ParticlesModel(glm::mat4& model){
    modelPoss = &model;
    texture = texture_def;

}
ParticlesModel::ParticlesModel(glm::mat4& model, std::string texture_path){
    modelPoss = &model;
    texture = texture_path;

}


ParticlesModel::~ParticlesModel(){
    glDeleteTextures(1, &textureID);
    glBindBuffer(GL_ARRAY_BUFFER,0);
	glDeleteBuffers(1,&initVel);
	glDeleteBuffers(1,&startTime);
	glBindVertexArray(0);
	glDeleteVertexArrays(1,&VAOParticles);
}

void ParticlesModel::initTexture(){
    // Definiendo la textura
	Texture textureParticlesFountain(texture);
	textureParticlesFountain.loadImage(); // Cargar la textura
	glGenTextures(1, &textureID); // Creando el id de la textura del landingpad
	glBindTexture(GL_TEXTURE_2D, textureID); // Se enlaza la textura
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // Wrapping en el eje u
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); // Wrapping en el eje v
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); // Filtering de minimización
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // Filtering de maximimizacion
	if(textureParticlesFountain.getData()){
		// Transferir los datos de la imagen a la tarjeta
		glTexImage2D(GL_TEXTURE_2D, 0, textureParticlesFountain.getChannels() == 3 ? GL_RGB : GL_RGBA, textureParticlesFountain.getWidth(), textureParticlesFountain.getHeight(), 0,
		textureParticlesFountain.getChannels() == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, textureParticlesFountain.getData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else 
		std::cout << "Fallo la carga de textura" << std::endl;
	textureParticlesFountain.freeImage(); // Liberamos memoria
}

void ParticlesModel::initParticleBuffers(){
	glGenBuffers(1, &initVel);
	glGenBuffers(1, &startTime);

	int sizeVel = nParticles * 3 * sizeof(GL_FLOAT);
	int sizeTime = nParticles  * sizeof(GL_FLOAT);
	glBindBuffer(GL_ARRAY_BUFFER,initVel);
	glBufferData(GL_ARRAY_BUFFER, sizeVel, NULL, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER,startTime);
	glBufferData(GL_ARRAY_BUFFER, sizeTime, NULL, GL_STATIC_DRAW);

	glm::vec3 v(0.0f);
	float velocity, theta, phi;
	GLfloat *data = new GLfloat[nParticles*3];
	for (unsigned int i = 0; i < nParticles; i++)
	{
		theta = glm::mix(0.0f, glm::two_pi<float>(),(float)rand()/RAND_MAX);
		phi = glm::mix(0.0f, glm::two_pi<float>(),(float)rand()/RAND_MAX);
		
		v.x = sinf(theta) * cosf(phi);
		v.y = cosf(theta);
		v.z = sinf(theta) * sinf(phi);

		velocity = glm::mix(vmin, vmax, (float)rand()/RAND_MAX);
		v = glm::normalize(v) * velocity;
		data[3*i] = v.x;
		data[3*i+1] = v.y;
		data[3*i+2] = v.z;

	}
	glBindBuffer(GL_ARRAY_BUFFER, initVel);
	glBufferSubData(GL_ARRAY_BUFFER,0,sizeVel,data);
	delete []data;
	data = new GLfloat[nParticles];
	float time = 0.0;
	float rate = 0.00075f;
	float duration = 10.0f;
	for (unsigned int i = 0; i < nParticles; i++)
	{
		data[i] = time;
		time += rate;
	}
	glBindBuffer(GL_ARRAY_BUFFER, startTime);
	glBufferSubData(GL_ARRAY_BUFFER,0,sizeTime,data);
	delete []data;
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenVertexArrays(1,&VAOParticles);
	glBindVertexArray(VAOParticles);
	glBindBuffer(GL_ARRAY_BUFFER, initVel);
	glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE,0,NULL);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, startTime);
	glVertexAttribPointer(1,1,GL_FLOAT, GL_FALSE,0,NULL);
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

void ParticlesModel::setModelMatrix(glm::mat4& model){
    modelPoss = &model;
}
void ParticlesModel::setTerrain(Terrain &vterr){
    terrain = &vterr;
}
void ParticlesModel::setShader(){
    shaderE.initialize(vertex_shader, fragment_shader);
    initTexture();
    initParticleBuffers();
}
void ParticlesModel::setShader(std::string vs,std::string fs){
    shaderE.initialize(vs, fs);
    initTexture();
    initParticleBuffers();
}
void ParticlesModel::DrawParticles(){
    if (!showing)
    {
        currTimeParticles = TimeManager::Instance().GetTime();
        showing = true;
    }
    

}
void ParticlesModel::loop(glm::mat4 proj, glm::mat4 view){
    currTimeParticles = TimeManager::Instance().GetTime();
    if (currTimeParticles - lastTimeParticles < particleslife && showing)
    {
    shaderE.setMatrix4("projection", 1, false,
				glm::value_ptr(proj));
    shaderE.setMatrix4("view", 1, false,
            glm::value_ptr(view));


    glm::vec3 currPoss((*modelPoss)[3][0],(*modelPoss)[3][1],(*modelPoss)[3][2]); 
    // glm::vec3 currPoss(0.0); 
    glm::mat4 modelMatrixE = glm::mat4(1.0f);
    modelMatrixE = glm::translate(modelMatrixE, currPoss);
    modelMatrixE[3][1] = terrain->getHeightTerrain(modelMatrixE[3][0],modelMatrixE[3][2]);
    modelMatrixE = glm::scale(modelMatrixE, glm::vec3(5.0f));

    // glDepthMask(GL_FALSE);
    glPointSize(particlessize);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    shaderE.turnOn();
    shaderE.setFloat("Time", float(currTimeParticles- lastTimeParticles));
    shaderE.setFloat("ParticleLifetime", particleslife);
    shaderE.setInt("ParticleTex", 0);
    shaderE.setVectorFloat3("Gravity", glm::value_ptr(glm::vec3(0.0f, -gravity, 0.0f)));
    shaderE.setMatrix4("model",1,false, glm::value_ptr(modelMatrixE));

    glBindVertexArray(VAOParticles);
    glDrawArrays(GL_POINTS, 0, nParticles);

    // glDepthMask(GL_TRUE);
    shaderE.turnOff();
    glBindTexture(GL_TEXTURE_2D, 0);
    //std::cout << "Drawing Particles" << std::endl;
    }else {
        showing = false;
        lastTimeParticles = currTimeParticles;
    }
}