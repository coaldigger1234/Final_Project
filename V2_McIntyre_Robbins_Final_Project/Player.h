//
// Created by Owner on 4/21/2021.
//

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
    void onEvent(const Event& event);
    int getLives();
    void collision(Asteroid deadlyAsteroid);
    ConvexShape getShape();
    Vector2f getSpeed();
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
