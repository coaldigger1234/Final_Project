//
// Created by Owner on 4/19/2021.
//

#ifndef SFML_TEMPLATE_GAMEMANAGER_H
#define SFML_TEMPLATE_GAMEMANAGER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Asteroid.h"

using namespace sf;
using namespace std;

class GameManager {
public:
    GameManager();
    int startGame();
    void quit();
    const int WIDTH = 2000;
    const int HEIGHT = 1500;
    Vector2f getDimensions();
    vector<Asteroid> getAsteroidVec();
    void setAsteroidVec(vector<Asteroid> newAsteroidVec);
private:
    void drawWindow();
    RenderWindow window;
    bool running;
    vector<Asteroid> asteroidVec;

};


#endif //SFML_TEMPLATE_GAMEMANAGER_H
