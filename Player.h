/* CSCI261 Final Project
 *
 * Authors: Geoffrey McIntyre (Sec E) and Cole Robbins (Sec C)
 *
 * Description: This code allows users to play asteroids using SFML
 */

#ifndef SFML_TEMPLATE_PLAYER_H
#define SFML_TEMPLATE_PLAYER_H

#include "SFML/Graphics.hpp"
#include "Asteroid.h"

using namespace sf;

class Player: public Drawable, public Transformable {
public:
    Player();
    void loadPlayer();
    void updatePlayer(float frametime);
    void draw(RenderTarget& target, RenderStates states) const;
    void onEvent(const Event& event, bool& firstKeyPressed);
    int getLives();
    void collision(vector<Asteroid>& asteroidVec, int asterID);
    ConvexShape getShape();
    Vector2f getSpeed();
    Vector2f setSpeed(Vector2f newSpeed);
    Vector2f getMagnitude();
private:
    int lives = 3;
    int MAX_SPEED = 10;
    Vector2f position;
    float xMagnitude;
    float yMagnitude;
    Vector2f speed;
    int rotMagnitude;
    int transMagnitude;
    int radius = 50;
    double angle;
    bool initiateCol = false;
    ConvexShape ship;
};


#endif //SFML_TEMPLATE_PLAYER_H
