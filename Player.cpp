/* CSCI261 Final Project
 *
 * Authors: Geoffrey McIntyre (Sec E) and Cole Robbins (Sec C)
 *
 * Description: This code allows users to play asteroids using SFML
 */

#include <cmath>

#include "GameManager.h"
#include "Player.h"

using namespace sf;

//Default Constructor
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

//Draw the player
void Player::draw(RenderTarget& target, RenderStates states) const {
    states.transform *= getTransform();
    target.draw(ship, states);
}

//Update player position/rotation
void Player::updatePlayer(float frametime) {
    double rotateSpeed = 0.4;
    double accelSpeed = 0.2;
    const double CONVERT_TO_RAD = 0.0174533;
    GameManager game;

    //Handle ship rotation
    if (rotMagnitude != 0) {
        ship.rotate(rotMagnitude * rotateSpeed * frametime);
    }

    //Handle ship translation
    if (transMagnitude != 0) {
        float rotation = ship.getRotation();
        //Calculate cartesian vector values based off of rotation
        xMagnitude = cos(rotation * CONVERT_TO_RAD);
        yMagnitude = sin(rotation * CONVERT_TO_RAD);

        //Calculate angular speed
        speed.x += transMagnitude * accelSpeed * frametime * xMagnitude / 10;
        speed.y += transMagnitude * accelSpeed * frametime * yMagnitude / 10;

        //Limit max velocity
        if (pow(speed.x, 2) > pow(MAX_SPEED, 2))
            if(speed.x > 0) {
                speed.x = MAX_SPEED;
            } else {
                speed.x = -MAX_SPEED;
            }

        //Limit max velocity
        if (pow(speed.y, 2) > pow(MAX_SPEED, 2))
            if(speed.y > 0) {
                speed.y = MAX_SPEED;
            } else {
                speed.y = -MAX_SPEED;
            }
    }

    position = ship.getPosition();

    //Handle ship window wrapping
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

//Handle keyboard inputs
void Player::onEvent(const Event &event, bool& firstKeyPressed) {
    transMagnitude = 0;
    rotMagnitude = 0;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        transMagnitude = 1;
        firstKeyPressed = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        transMagnitude = -1;
        firstKeyPressed = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        rotMagnitude = -1;
        firstKeyPressed = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        rotMagnitude = 1;
        firstKeyPressed = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        transMagnitude = 1;
        firstKeyPressed = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        transMagnitude = -1;
        firstKeyPressed = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        rotMagnitude = -1;
        firstKeyPressed = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        rotMagnitude = 1;
        firstKeyPressed = true;
    }
}

//Handle asteroid collisions
void Player::collision(vector<Asteroid>& asteroidVec, int asterID) {
    double shipPosX = ship.getPosition().x;
    double shipPosY = ship.getPosition().y;
    double astPosX = asteroidVec.at(asterID).getAsteroidShape().getPosition().x;
    double astPosY = asteroidVec.at(asterID).getAsteroidShape().getPosition().y;
    GameManager game;

    //If ship is within the asteroid radius, and both are visible, deduct lives and destroy the asteroid.
    double distanceShipToAsteroid = sqrt( pow( shipPosX - astPosX , 2 ) + pow( shipPosY - astPosY , 2 ));
    if ( ( shipPosX > 0 || shipPosX < game.getDimensions().x ) && ( shipPosY > 0 || shipPosY < game.getDimensions().y )) {
        if (asteroidVec.at(asterID).getAsteroidShape().getOutlineColor() == Color::White) {
            if (distanceShipToAsteroid <= ( radius + asteroidVec.at(asterID).getRadius() ) ) {
                asteroidVec.at(asterID).fragmentation(asteroidVec, asterID);
                if(lives > 0) {
                    lives--;
                }
            }
        }
    }
}

//Fetch lives
int Player::getLives() {
    return lives;
}

//Fetch ship shape
ConvexShape Player::getShape() {
    return ship;
}

//Fetch player speed
Vector2f Player::getSpeed() {
    return speed;
}

//set player speed
Vector2f Player::setSpeed(Vector2f newSpeed) {
    speed = newSpeed;
}

//Fetch player magnitude
Vector2f Player::getMagnitude() {
    float rotation = ship.getRotation();
    const double CONVERT_TO_RAD = 0.0174533;
    xMagnitude = cos(rotation * CONVERT_TO_RAD);
    yMagnitude = sin(rotation * CONVERT_TO_RAD);
    return Vector2f(xMagnitude, yMagnitude);
}
