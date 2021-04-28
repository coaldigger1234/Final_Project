//
// Created by Owner on 4/26/2021.
//

#ifndef SFML_TEMPLATE_MISSILE_H
#define SFML_TEMPLATE_MISSILE_H

#include "SFML/Graphics.hpp"
#include "Player.h"
#include <vector>
using namespace sf;
using namespace std;

class Missile {
public:
    CircleShape getShape();
    void isShot(Player ship);
    vector<CircleShape> getMissileVector();
    void updateMissile(Player player);
    void hitsAsteroid(vector<Asteroid>& asteroidVec, int asterInc);
private:
    CircleShape _missile;
    Vector2f _speed;
    vector<CircleShape> _missileVec;
};


#endif //SFML_TEMPLATE_MISSILE_H
