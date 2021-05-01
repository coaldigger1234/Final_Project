//
// Created by Owner on 4/19/2021.
//

#ifndef SFML_TEMPLATE_ASTEROID_H
#define SFML_TEMPLATE_ASTEROID_H

#include <vector>
#include "SFML/Graphics.hpp"
// #include "GameManager.h"
class GameManager;
using namespace sf;
using namespace std;

class Asteroid {
public:
    Asteroid();
    Asteroid(double velocity, int size, double rotation, Vector2f position);
    void draw(RenderTarget& target, RenderStates states) const;
    void updateAsteroid(double frametime);
    void createAsteroid();
    ConvexShape getAsteroidShape();
    double getRadius();
    void changeColor();
    void setNumAsteroid(int number);
    int getNumAsteroid();
    void fragmentation(vector<Asteroid>& asteroidVec, int asterID);
private:
    double _velocity;
    double _size;
    double _angle;
    Vector2f _speed;
    Vector2f _position;
    double _radius;
    static int numAsteroid;
    void loadAsteroid();
    void collision(double x, double y);
    void destroyAsteroid();
    void randomVelAndDir();
    ConvexShape asteroidShape;
};


#endif //SFML_TEMPLATE_ASTEROID_H
