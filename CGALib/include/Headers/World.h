#pragma once

#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#include <cstdlib>

//glew include
#include <GL/glew.h>
#include <GLFW/glfw3.h>

//GLM include
#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Headers/Texture.h"
#include "Headers/Terrain.h"

// Include loader Model class
#include "Headers/Model.h"

#include "GameManager.h"

#define MAXRANGE 0
#define MINRANGE 2
#define NUMBER_OF_LANES 3;

using namespace std;


class Obstacle {
private:
    Model* obstacle;
    string filepath;
    glm::mat4 matrixModelObstacle;
    Shader* shader;
    glm::vec3 position;
    bool rendered = false;
    int random_x_obstacle = 0;
    vector<int> positions_x_init = { 0,15,20 };
    //vector<int> positions_x_init = {-15,0,15};
public:
    Obstacle() {}

    Obstacle(Model* m, const string& _filepath, Shader* _shader, glm::vec3 _position = glm::vec3(0.0f, 0.0f, 90.0f)) {
        obstacle = m;
        this->filepath = _filepath;
        this->shader = _shader;
        this->position = _position;
        this->matrixModelObstacle = glm::mat4(1.0);
        std::cout << "File: " << this->filepath << std::endl;
    }

    void buildObstacle(Model* m, const string& _filepath, Shader* _shader, glm::vec3 _position = glm::vec3(0.0f, 0.0f, 90.0f)) {
        obstacle = m;
        this->filepath = _filepath;
        this->shader = _shader;
        this->position = _position;
        this->matrixModelObstacle = glm::mat4(1.0);
        std::cout << "File: " << this->filepath << std::endl;
    }

    // Obstacle(Model _obstacle, const string & _filepath, Shader shader, glm::vec3 _position = glm::vec3(0.0f)){
    //     std::swap(this->obstacle, _obstacle);
    //     Obstacle(_filepath,shader,_position);
    // }

    Obstacle(Obstacle&& other) {
        // this->obstacle = std::move(other.obstacle);
        obstacle = other.obstacle;
        std::cout << "Obstacle && other" << std::endl;
        this->filepath = std::move(other.filepath);
        this->shader = std::move(other.shader);
        this->position = std::move(other.position);
    }

    Obstacle(const Obstacle& other) {
        // this->obstacle = std::move(other.obstacle);
        obstacle = other.obstacle;
        std::cout << "const Obstacle & other" << std::endl;
        this->filepath = std::move(other.filepath);
        this->shader = std::move(other.shader);
        this->position = std::move(other.position);
    }


    void initObstacle() {
        try {
            if (this->filepath.size() < 1)
                throw std::runtime_error("Error, no hay file path");

            std::cout << "init model file: " << this->filepath << std::endl;
            this->obstacle->loadModel(this->filepath);
            this->obstacle->setShader(shader);
            this->matrixModelObstacle = glm::mat4(1.0);
            //renderObstacle();
        }
        catch (const std::exception& e) {
            throw std::runtime_error(e.what());
        }
    }

    void set_position(glm::vec3 _position = glm::vec3(0.0f, 0.0f, -100.0f)) {
        this->position = _position;
    }

    void fix_matrix(glm::mat4 &_matrixModelObstacle,Terrain& terrain){
        auto ejey = glm::normalize(terrain.getNormalTerrain(_matrixModelObstacle[3][0], _matrixModelObstacle[3][2]));
        auto ejex = glm::vec3(_matrixModelObstacle[0]);
        auto ejez = glm::normalize(glm::cross(ejex, ejey));
        ejex = glm::normalize(glm::cross(ejey, ejez));

        _matrixModelObstacle[0] = glm::vec4(ejex, 0.0f);
        _matrixModelObstacle[1] = glm::vec4(ejey, 0.0f);
        _matrixModelObstacle[2] = glm::vec4(ejez, 0.0f);

        _matrixModelObstacle[3][1] = terrain.getHeightTerrain(_matrixModelObstacle[3][0], _matrixModelObstacle[3][2]);
    }

    void renderObstacle(Terrain & terrain) {
        glActiveTexture(GL_TEXTURE0);
        auto _matrixModelObstacle = glm::translate(this->matrixModelObstacle, this->position);

        fix_matrix(_matrixModelObstacle,terrain);

        this->obstacle->render(_matrixModelObstacle);

    }

    void renderObstacle(glm::vec3 _position) {
        glActiveTexture(GL_TEXTURE0);
        auto _matrixModelObstacle = glm::translate(this->matrixModelObstacle, _position);

        this->obstacle->render(_matrixModelObstacle);
    }

    
    //void renderObstacle(glm::mat4 _position) {
    //    glActiveTexture(GL_TEXTURE0);
    //    //this->matrixModelObstacle = glm::translate(this->matrixModelObstacle, _position);
    //    //this->matrixModelObstacle = glm::scale(this->matrixModelObstacle,glm::vec3(5.0f));
    //    this->obstacle->render(_position);
    //}


    int random_number(int init, int end){
        if (end == 0)
            return 0;
        if (init == 0);
            return (rand() % end);   
            
        return init + (rand() % end);
    }

    // void generate_position(int& state_obstacle, float& _random_x_obstacle, float& movement_obstacles, float & difficulty) {
    //     switch (state_obstacle) {
    //     case 0:
    //         _random_x_obstacle = random_number(MINRANGE , MAXRANGE);
    //         movement_obstacles = -100.0f;
    //         rendered = false;
    //         state_obstacle = 1;

    //         break;
    //     case 1:
    //         if (movement_obstacles > 100.0f) {
    //             rendered = false;
    //             state_obstacle = 0;
    //         }
    //         else {
    //             rendered = true;
    //             movement_obstacles += (difficulty) * 10;
    //             state_obstacle = 1;
    //         }

    //         break;
    //     }
        
    //     set_position(glm::vec3(_random_x_obstacle, 0.0f, movement_obstacles));
    // }

    void generate_position(int& state_obstacle, float& _random_x_obstacle, float& movement_obstacles, float & difficulty) {
        switch (state_obstacle) {
        case 0:
            random_x_obstacle = positions_x_init[random_number(MINRANGE , MAXRANGE)];
            movement_obstacles = -100.0f;
            rendered = false;
            state_obstacle = 1;

            break;
        case 1:
            if (movement_obstacles > 100.0f) {
                rendered = false;
                state_obstacle = 0;
            }
            else {
                rendered = true;
                movement_obstacles += (difficulty) * 10;
                state_obstacle = 1;
            }

            break;
        }
        
        set_position(glm::vec3(random_x_obstacle, 0.0f, movement_obstacles));
    }

    void destroy(Model& obstacle) {
        obstacle.destroy();
    }

    void destroy() {
        this->obstacle->destroy();
    }

    string getData() {
        return this->filepath;
    }
    // ~Obstacle(){
    // }
    bool is_rendered(){
        return this->rendered;
    }

    void set_rendered(bool _rendered){
        rendered = _rendered;
    }
};

// ModelObstacle

template<typename TObstacle>
class Trapper {
private:
    int index_obstacle = 0;
    vector<TObstacle> obstacles;
    vector<bool> obstacle_visibles = {false,false,false};
    
public:
    Trapper(vector<TObstacle> _obstacles) {
        this->obstacles = std::move(_obstacles);
    }


    void initTrapper(Model* m, const string& file_path, Shader* shader, glm::vec3 position = glm::vec3(0.0f, 0.0f, 40.0f)) {
        for (auto& obstacle : obstacles) {
            obstacle.buildObstacle(m, file_path, shader, position);
            obstacle.initObstacle();
        }
    }

    void initTrapper(const vector<Model*> & ms, const vector<string> & file_paths, Shader* shader, glm::vec3 position = glm::vec3(0.0f, 0.0f, 40.0f)) {
        int index = 0;
        for (auto& obstacle : obstacles) {
            std::cout << "Obstacle: " << index << " file: " << file_paths[index] << std::endl;
            obstacle.buildObstacle(ms[index], file_paths[index], shader, position);
            obstacle.initObstacle();
            index++;
        }
    }

    int random_number(int init, int end) {
        return init + (rand() % end);
    }

    void set_positions(float x, float y, float z) {
        int element = 0;
        for (auto& obstacle : obstacles) {
            std::cout << "Element=> " << element << " x: " << x << " y: " << y << " z: " << z << std::endl;;
            element++;
            obstacle.set_position(glm::vec3(x, y, z)); // checar aqui
        }
    }

    void randomize_visible(){
        for(auto & obstacle_visible : obstacle_visibles){
            obstacle_visible = (bool) random_number(0,1);
        }
    }

    void renderObstacles(Terrain& terrain) {
        
        if(!obstacles[index_obstacle].is_rendered()){
            index_obstacle = random_number(0, obstacles.size() - 1);
        }

        obstacles[index_obstacle].renderObstacle(terrain);
        obstacles[index_obstacle].set_rendered(false);
    }


    void generate_positions(int& state_obstacle, float& random_x_obstacle, float& movement_obstacles, float & difficulty) {
        for(auto & obstacle : obstacles){
            obstacle.generate_position(state_obstacle, random_x_obstacle, movement_obstacles, difficulty);
        }
    }


    void destroy() {
        for (auto& obstacle : obstacles) {
            obstacle.destroy();
        }
    }

};


