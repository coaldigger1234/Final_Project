/* CSCI261 Final Project
 *
 * Authors: Geoffrey McIntyre (Sec E) and Cole Robbins (Sec C)
 *
 * Description: This code allows users to play asteroids using SFML
 */

#include <cmath>
#include <iostream>

#include "GameManager.h"

using namespace sf; // using the sf namespace
using namespace std; // using the standard namespace

//Default Constructor
Asteroid::Asteroid() {
    createAsteroid();
}

//Create a custom asteroid
Asteroid::Asteroid(double velocity, int size, double rotation, Vector2f position ) {
    GameManager game;
    _velocity = velocity;
    _size = size;
    _radius = 40 * _size;
    asteroidShape.setRotation(rotation);
    _angle = asteroidShape.getRotation();
    asteroidShape.setPosition(position);
    asteroidShape.setFillColor(Color(0, 0, 0, 0));
    asteroidShape.setOutlineColor(Color(255, 255, 255));
    asteroidShape.setOutlineThickness(2);
    asteroidShape.setPointCount(7);
    asteroidShape.setPoint(0, Vector2f(-40.0f * _size, 20.0f * _size));
    asteroidShape.setPoint(1, Vector2f(30.0f * _size, 30.0f * _size));
    asteroidShape.setPoint(2, Vector2f(20.0f * _size, 0.0f * _size));
    asteroidShape.setPoint(3, Vector2f(30.0f * _size, -30.0f * _size));
    asteroidShape.setPoint(4, Vector2f(-30.0f * _size, -40.0f * _size));
    asteroidShape.setPoint(5, Vector2f(-20.0f * _size, -20.0f * _size));
    asteroidShape.setPoint(6, Vector2f(-40.0f * _size, 0.0f * _size));
}

//Create an Asteroid
void Asteroid::createAsteroid() {
    GameManager game;
    _velocity = (double)rand() / RAND_MAX * 7 + 2;
    _size = (double)rand() / RAND_MAX * 2 + .25;
    _radius = 35 * _size;
    asteroidShape.setRotation((double)rand() / RAND_MAX * 360 + 1);
    _angle = asteroidShape.getRotation();
    asteroidShape.setPosition(game.WIDTH * (double)rand() / RAND_MAX, game.HEIGHT * rand() / RAND_MAX);
    asteroidShape.setFillColor(Color(0, 0, 0, 0));
    asteroidShape.setOutlineColor(Color(0, 255, 0, 0));
    asteroidShape.setOutlineThickness(2);
    asteroidShape.setPointCount(7);
    asteroidShape.setPoint(0, Vector2f(-40.0f * _size, 20.0f * _size));
    asteroidShape.setPoint(1, Vector2f(30.0f * _size, 30.0f * _size));
    asteroidShape.setPoint(2, Vector2f(20.0f * _size, 0.0f * _size));
    asteroidShape.setPoint(3, Vector2f(30.0f * _size, -30.0f * _size));
    asteroidShape.setPoint(4, Vector2f(-30.0f * _size, -40.0f * _size));
    asteroidShape.setPoint(5, Vector2f(-20.0f * _size, -20.0f * _size));
    asteroidShape.setPoint(6, Vector2f(-40.0f * _size, 0.0f * _size));
}

//Update asteroid position/rotation
void Asteroid::updateAsteroid(double frametime) {
    const double CONVERT_TO_RAD = 0.0174533;
    _angle = asteroidShape.getRotation();
    double xMag = cos(_angle * CONVERT_TO_RAD);
    double yMag = sin(_angle * CONVERT_TO_RAD);
    GameManager game;

    _speed.x = xMag * _velocity;
    _speed.y = yMag * _velocity;

    _position = asteroidShape.getPosition();

    //Handle asteroid window wrapping
    if (_position.x < 0 - _radius) {
        _position.x = game.getDimensions().x +  _radius;
        if (asteroidShape.getOutlineColor() == Color(0, 255, 0, 0)) {
            asteroidShape.setOutlineColor(Color::White);
        }
        randomVelAndDir();
    }
    if (_position.x > game.getDimensions().x + _radius) {
        _position.x = 0 - _radius;
        if (asteroidShape.getOutlineColor() == Color(0, 255, 0, 0)) {
            asteroidShape.setOutlineColor(Color::White);
        }
        randomVelAndDir();
    }
    if (_position.y < 0 - _radius) {
        _position.y = game.getDimensions().y +  _radius;
        if (asteroidShape.getOutlineColor() == Color(0, 255, 0, 0)) {
            asteroidShape.setOutlineColor(Color::White);
        }
        randomVelAndDir();
    }
    if (_position.y > game.getDimensions().y + _radius) {
        _position.y = 0 - _radius;
        if (asteroidShape.getOutlineColor() == Color(0, 255, 0, 0)) {
            asteroidShape.setOutlineColor(Color::White);
        }
        randomVelAndDir();
    }

    asteroidShape.setPosition(_position);
    asteroidShape.move(_speed);

}

//Fetch asteroid shape
ConvexShape Asteroid::getAsteroidShape() {
    return asteroidShape;
}

//Returns a random vel/direction for the asteroid
void Asteroid::randomVelAndDir() {
    if (asteroidShape.getRotation() > 180) {
        asteroidShape.setRotation( (double)rand() * 179 + 180);
    } else {
        asteroidShape.setRotation( (double)rand() * 179 + 1);
    }

    _velocity = (double)rand() / RAND_MAX * 7 + 2;
}

//Fetch asteroid radius
double Asteroid::getRadius() {
    return _radius;
}

//Change asteroid outline color
void Asteroid::changeColor() {
    asteroidShape.setOutlineColor(Color(0, 0, 0,0));
}

//Destroy the asteroid
void Asteroid::fragmentation(vector<Asteroid>& asteroidVec, int asterID) {
    asteroidVec.erase(asteroidVec.begin() + asterID);

}