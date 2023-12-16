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
    int maxScore;
    int score;
    float x;
    float y;
    const std::string defaultFileName = "scores.txt"; // Nombre de archivo por defecto
    FontTypeRendering::FontTypeRendering *modelText;
  public:
    // Constructor que inicializa playerName y score con valores predeterminados
    ScoreManager(float x,float y){
      this->score = 0;
      this->playerName ="Player";
      this->x = x;
      this->y = y;
    }

    // Método para leer el mejor jugador desde un archivo de texto
    bool readBestPlayer(const std::string& filename = "../Proyecto/src/data_player.txt") {
        // Si no se proporciona un nombre de archivo, se utiliza el predeterminado
        std::string actualFilename = (filename.empty()) ? defaultFileName : filename;

        std::ifstream file(actualFilename);
        if (file.is_open()) {
            file >> playerName >> maxScore;
            file.close();
            return true;
        } else {
            std::cerr << "Error al abrir el archivo " << actualFilename << std::endl;
            return false;
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
        return playerName + ": " + std::to_string(score) + " Max escore: " + std::to_string(maxScore);
    }

    // Métodos de modificación (setters)
    void setPlayerName(const std::string& name) {
        playerName = name;
    }


    void setScore(int newScore) {
        score = newScore;
    }

    void init(int screenWidth, int screenHeight){
      modelText = new FontTypeRendering::FontTypeRendering(screenWidth, screenHeight);
      modelText->Initialize();
      if(!readBestPlayer()){
        setPlayerName("Player 1");
        setScore(0);
        maxScore = 0;
      }
    }

    void sumScore(int newScore) {
        score += newScore;
    }

    void sumScore() {
        score ++;
    } 

    // Método para guardar los nuevos datos en un archivo de texto
    void saveToFile(const std::string& filename = "../Proyecto/src/data_player.txt") const {
        // Si no se proporciona un nombre de archivo, se utiliza el predeterminado
        std::string actualFilename = (filename.empty()) ? defaultFileName : filename;

        std::ofstream file(actualFilename);
        if (file.is_open()) {
            file << playerName << " " << ( (score > maxScore) ? score : maxScore );
            file.close();
        } else {
            std::cerr << "Error al abrir el archivo " << actualFilename << " para escritura." << std::endl;
        }
    }

    void renderScore(){
      modelText->render(getPlayerInfo().c_str(),x,y);
      saveToFile();
    }

    void reset(){
      if(!readBestPlayer()){
        setPlayerName("Player 1");
        setScore(0);
        maxScore = 0;
      }
    }
};

#endif 