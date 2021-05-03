/* CSCI261 Final Project
 *
 * Authors: Geoffrey McIntyre (Sec E) and Cole Robbins (Sec C)
 *
 * Description: This code allows users to play asteroids using SFML
 */

#include <cmath>

#include "GameManager.h"
#include "Missile.h"

using namespace std; // using the standard namespace

//Returns missile object
CircleShape Missile::getShape() {
    return _missile;
}

//Spawns a missile when shooting
void Missile::isShot(Player player) {
    ConvexShape ship = player.getShape();
    _missile.setRadius(5);
    _missile.setFillColor(Color::White);
    _missile.setPosition(ship.getPosition());
}

//Updates missile position
void Missile::updateMissile(Player player) {
    double velocity = 20;
    _speed = Vector2f(player.getMagnitude().x * velocity + player.getSpeed().x, player.getMagnitude().y * velocity + player.getSpeed().y);
    _missile.move(_speed);
}

//Returns vector of missiles
vector<CircleShape> Missile::getMissileVector() {
    return _missileVec;
}

//Handles Asteroid Collision
void Missile::hitsAsteroid(vector<Asteroid>& asteroidVec, int asterID) {
    double missilePosX = _missile.getPosition().x;
    double missilePosY = _missile.getPosition().y;
    double astPosX = asteroidVec.at(asterID).getAsteroidShape().getPosition().x;
    double astPosY = asteroidVec.at(asterID).getAsteroidShape().getPosition().y;
    GameManager game;

    //If distance between missile/asteroid is less than their radii, and they are both visible, hide missile and destroy asteroid.
    double distanceMissileToAsteroid = sqrt( pow( missilePosX - astPosX, 2 ) + pow( missilePosY - astPosY , 2 ));
    if ( ( missilePosX > 0 || missilePosX < game.getDimensions().x ) && ( missilePosY > 0 || missilePosY < game.getDimensions().y )) {
        if ( (asteroidVec.at(asterID).getAsteroidShape().getOutlineColor() == Color::White ) && ( _missile.getFillColor() == Color::White ) )  {
            if (distanceMissileToAsteroid <= ( _missile.getRadius() + asteroidVec.at(asterID).getRadius() ) ) {
                _missile.setFillColor(Color(0, 0, 0, 0));
                asteroidVec.at(asterID).fragmentation(asteroidVec, asterID);
            }
        }
    }
}


