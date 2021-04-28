//
// Created by Owner on 4/26/2021.
//

#include "Missile.h"
#include <iostream>
#include <cmath>
#include "GameManager.h"
#include "FragmentationExecution.h"

using namespace std;

CircleShape Missile::getShape() {
    return _missile;
}

void Missile::isShot(Player player) {
    ConvexShape ship = player.getShape();
    _missile.setRadius(5);
    _missile.setFillColor(Color::White);
    _missile.setPosition(ship.getPosition());
}

void Missile::updateMissile(Player player) {
    double velocity = 20;
    _speed = Vector2f(player.getMagnitude().x * velocity + player.getSpeed().x, player.getMagnitude().y * velocity + player.getSpeed().y);
    _missile.move(_speed);
}

vector<CircleShape> Missile::getMissileVector() {
    return _missileVec;
}

void Missile::hitsAsteroid(vector<Asteroid>& asteroidVec, int& asterInc) {
    double missilePosX = _missile.getPosition().x;
    double missilePosY = _missile.getPosition().y;
    double astPosX = asteroidVec.at(asterInc).getAsteroidShape().getPosition().x;
    double astPosY = asteroidVec.at(asterInc).getAsteroidShape().getPosition().y;
    GameManager game;

    double distanceShipToAsteroid = sqrt( pow( missilePosX - astPosX, 2 ) + pow( missilePosY - astPosY , 2 ));
    if ( ( missilePosX > 0 || missilePosX < game.getDimensions().x ) && ( missilePosY > 0 || missilePosY < game.getDimensions().y )) {
        if ( (asteroidVec.at(asterInc).getAsteroidShape().getOutlineColor() == Color::White ) && ( _missile.getFillColor() == Color::White ) )  {
            if (distanceShipToAsteroid <= ( _missile.getRadius() + asteroidVec.at(asterInc).getRadius() ) ) {
                //asteroidVec.at(asterInc).changeColor();
                _missile.setFillColor(Color(0, 0, 0, 0));
                //asteroid.setNumAsteroid(asteroid.getNumAsteroid() + 1);
                asteroidVec.at(asterInc).fragmentation(asteroidVec, asterInc);
                asteroidVec.erase(asteroidVec.begin() + asterInc);
                cout << asterInc << endl;
                asterInc -= 1;
                //missileVec.pop_back();
            }
        }
    }
}


