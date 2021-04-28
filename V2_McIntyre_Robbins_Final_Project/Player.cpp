//
// Created by Owner on 4/21/2021.
//

#include "Player.h"
#include "SFML/Graphics.hpp"
#include "GameManager.h"
#include <iostream>
#include <cmath>

using namespace sf;

Player::Player() {
    int radius = 25;

    ship.setPointCount(4);
    ship.setPoint(0, Vector2f(0.0f, 0.0f));
    ship.setPoint(1, Vector2f(50.0f, 25.0f));
    ship.setPoint(2, Vector2f(0.0f, 50.0f));
    ship.setPoint(3, Vector2f(7.5f, 25.0f));
    ship.setOrigin(25,25);

    ship.setPosition(460.0f, 460.0f);

    ship.setOutlineColor(Color::White);
    ship.setFillColor(Color::Black);
    ship.setOutlineThickness(3);

    speed.x = 0;
    speed.y = 0;

}

void Player::draw(RenderTarget& target, RenderStates states) const {
    states.transform *= getTransform();
    target.draw(ship, states);
}

void Player::updatePlayer(float frametime) {
    double rotateSpeed = 0.4;
    double accelSpeed = 0.2;
    double incrementSpeed = 0;
    const double CONVERT_TO_RAD = 0.0174533;
    double totalSpeed;
    GameManager game;

    if (rotMagnitude != 0) {
        ship.rotate(rotMagnitude * rotateSpeed * frametime);
    }

    if (transMagnitude != 0) {
        float rotation = ship.getRotation();
        xMagnitude = cos(rotation * CONVERT_TO_RAD);
        yMagnitude = sin(rotation * CONVERT_TO_RAD);

        speed.x += transMagnitude * accelSpeed * frametime * xMagnitude / 10;
        speed.y += transMagnitude * accelSpeed * frametime * yMagnitude / 10;


        if (pow(speed.x, 2) > pow(MAX_SPEED, 2))
                if(speed.x > 0) {
                    speed.x = MAX_SPEED;
                } else {
                    speed.x = -MAX_SPEED;
                }

        if (pow(speed.y, 2) > pow(MAX_SPEED, 2))
            if(speed.y > 0) {
                speed.y = MAX_SPEED;
            } else {
                speed.y = -MAX_SPEED;
            }
    }

    position = ship.getPosition();

    if (position.x < 0) {
        position.x = game.getDimensions().x;
    }
    if (position.x > game.getDimensions().x) {
        position.x = 0;
    }
    if (position.y < 0) {
        position.y = game.getDimensions().y;
    }
    if (position.y > game.getDimensions().y) {
        position.y = 0;
    }

    ship.setPosition(position);

    ship.move(speed);

}

void Player::onEvent(const Event &event) {
    transMagnitude = 0;
    rotMagnitude = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        transMagnitude = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        transMagnitude = -1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        rotMagnitude = -1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        rotMagnitude = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        transMagnitude = 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        transMagnitude = -1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        rotMagnitude = -1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        rotMagnitude = 1;
    }
}

void Player::collision(vector<Asteroid>& asteroidVec, int asterID) {
    double shipPosX = ship.getPosition().x;
    double shipPosY = ship.getPosition().y;
    double astPosX = asteroidVec.at(asterID).getAsteroidShape().getPosition().x;
    double astPosY = asteroidVec.at(asterID).getAsteroidShape().getPosition().y;
    GameManager game;

    double distanceShipToAsteroid = sqrt( pow( shipPosX - astPosX , 2 ) + pow( shipPosY - astPosY , 2 ));
    if ( ( shipPosX > 0 || shipPosX < game.getDimensions().x ) && ( shipPosY > 0 || shipPosY < game.getDimensions().y )) {
        if (asteroidVec.at(asterID).getAsteroidShape().getOutlineColor() == Color::White) {
            if (distanceShipToAsteroid <= ( radius + asteroidVec.at(asterID).getRadius() ) ) {
                //initiateCol = true;
                asteroidVec.at(asterID).fragmentation(asteroidVec, asterID);
                if(lives > 0) {
                    lives--;
                }
            }
        }
    }
    /*if (( distanceShipToAsteroid > ( radius + deadlyAsteroid.getRadius() ) ) && initiateCol) {
        initiateCol = false;
        --lives;
    }*/
}

int Player::getLives() {
    return lives;
}

ConvexShape Player::getShape() {
    return ship;
}

Vector2f Player::getSpeed() {
    return speed;
}

Vector2f Player::getMagnitude() {
    float rotation = ship.getRotation();
    const double CONVERT_TO_RAD = 0.0174533;
    xMagnitude = cos(rotation * CONVERT_TO_RAD);
    yMagnitude = sin(rotation * CONVERT_TO_RAD);
    return Vector2f(xMagnitude, yMagnitude);
}
