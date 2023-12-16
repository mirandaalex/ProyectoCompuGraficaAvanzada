/*
 * Model.h
 *
 *  Created on: 14/09/2023
 *      Author: Alex
 */

#ifndef ScoreMan_H
#define ScoreMan_H

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

#include <iostream>
#include <fstream>
#include <string>
#include "Headers/FontTypeRendering.h"

class ScoreManager {
private:
    std::string playerName;
    
    int score;
    glm::vec2 position;
    const std::string defaultFileName = "scores.txt"; // Nombre de archivo por defecto
    FontTypeRendering::FontTypeRendering *modelText;
public:
    // Constructor que inicializa playerName y score con valores predeterminados
    ScoreManager(int screenWidth, int screenHeight, glm::vec2 _position = glm::vec2(1,1)) : playerName("Player"), score(0),position(_position){
      modelText = new FontTypeRendering::FontTypeRendering(screenWidth, screenHeight);
      modelText->Initialize();
    }

    // Método para leer el mejor jugador desde un archivo de texto
    void readBestPlayer(const std::string& filename = "") {
        // Si no se proporciona un nombre de archivo, se utiliza el predeterminado
        std::string actualFilename = (filename.empty()) ? defaultFileName : filename;

        std::ifstream file(actualFilename);
        if (file.is_open()) {
            file >> playerName >> score;
            file.close();
        } else {
            std::cerr << "Error al abrir el archivo " << actualFilename << std::endl;
        }
    }

    // Métodos de acceso (getters)
    std::string getPlayerName() const {
        return playerName;
    }

    int getScore() const {
        return score;
    }

    std::string getPlayerInfo() const {
        return playerName + ": " + std::to_string(score);
    }

    // Métodos de modificación (setters)
    void setPlayerName(const std::string& name) {
        playerName = name;
    }

    void setScore(int newScore) {
        score = newScore;
    }

    void sumScore(int newScore) {
        score += newScore;
    }

    void sumScore() {
        score ++;
    } 

    // Método para guardar los nuevos datos en un archivo de texto
    void saveToFile(const std::string& filename = "") const {
        // Si no se proporciona un nombre de archivo, se utiliza el predeterminado
        std::string actualFilename = (filename.empty()) ? defaultFileName : filename;

        std::ofstream file(actualFilename);
        if (file.is_open()) {
            file << playerName << " " << score;
            file.close();
        } else {
            std::cerr << "Error al abrir el archivo " << actualFilename << " para escritura." << std::endl;
        }
    }

  void renderScore(){
    modelText->render(getPlayerInfo().c_str(),position.x,position.y);
  }

};

#endif 