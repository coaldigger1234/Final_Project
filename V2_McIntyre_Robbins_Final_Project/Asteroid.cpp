//
// Created by Owner on 4/19/2021.
//

#include "Asteroid.h"
#include <random>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include "GameManager.h"
using namespace sf;
using namespace std;

Asteroid::Asteroid() {
    createAsteroid();
}

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

void Asteroid::createAsteroid() {
    GameManager game;
    _velocity = (double)rand() / RAND_MAX * 7 + 2;
    _size = (double)rand() / RAND_MAX * 2 + .25;
    _radius = 40 * _size;
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

    //cout << _size << endl;

}

void Asteroid::updateAsteroid(double frametime) {
    const double CONVERT_TO_RAD = 0.0174533;
    _angle = asteroidShape.getRotation();
    double xMag = cos(_angle * CONVERT_TO_RAD);
    double yMag = sin(_angle * CONVERT_TO_RAD);
    GameManager game;

    _speed.x = xMag * _velocity;
    _speed.y = yMag * _velocity;

    _position = asteroidShape.getPosition();

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

//void Asteroid::draw(RenderTarget& target, RenderStates states) const {
//    states.transform *= asteroidShape.getTransform();
//    target.draw(asteroidShape, states);
//}

ConvexShape Asteroid::getAsteroidShape() {
    return asteroidShape;
}

void Asteroid::randomVelAndDir() {
    if (asteroidShape.getRotation() > 180) {
        asteroidShape.setRotation( (double)rand() * 179 + 180);
    } else {
        asteroidShape.setRotation( (double)rand() * 179 + 1);
    }

    _velocity = (double)rand() / RAND_MAX * 7 + 2;
}

double Asteroid::getRadius() {
    return _radius;
}

void Asteroid::changeColor() {
    asteroidShape.setOutlineColor(Color(0, 0, 0,0));
}

//void Asteroid::setNumAsteroid(int number) {
//    numAsteroid = number;
//}

//int Asteroid::getNumAsteroid() {
//    return numAsteroid;
//}

void Asteroid::fragmentation(vector<Asteroid>& asteroidVec, int asterID) {
    /*if(asteroidVec.at(asterID)._size > 0.25) {
        vector<Asteroid> newAsteroids;

        double rotation = asteroidVec.at(asterID).getAsteroidShape().getRotation();
        Vector2f position = asteroidVec.at(asterID).getAsteroidShape().getPosition();

        Asteroid asteroid1(.5 * asteroidVec.at(asterID)._velocity, .5 * asteroidVec.at(asterID)._size, rotation - 270, position);
        Asteroid asteroid2(.5 * asteroidVec.at(asterID)._velocity, .5 * asteroidVec.at(asterID)._size, rotation + 90, position);

        //asteroid1.getAsteroidShape().setOutlineColor(Color::White);
        //asteroid2.getAsteroidShape().setOutlineColor(Color::White);

        if (rotation > 270) {
            asteroid1.getAsteroidShape().setRotation(rotation - 270);
            asteroid2.getAsteroidShape().setRotation(rotation - 90);
        } else if (rotation < 90) {
            asteroid1.getAsteroidShape().setRotation(rotation + 90);
            asteroid2.getAsteroidShape().setRotation(rotation + 270);
        } else {
            asteroid1.getAsteroidShape().setRotation(rotation + 90);
            asteroid2.getAsteroidShape().setRotation(rotation - 90);
        }

        asteroidVec.push_back(asteroid1);
        asteroidVec.push_back(asteroid2);
    }*/
    asteroidVec.erase(asteroidVec.begin() + asterID);

}