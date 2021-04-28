//
// Created by Owner on 4/26/2021.
//
#include <vector>
#include "FragmentationExecution.h"

using namespace std;

void FragmentationExecution::pushBackAsteroidVec(Asteroid fillAsteroid, GameManager& game) {
    vector<Asteroid> asteroidFragments = fillAsteroid.fragmentation(fillAsteroid);
    vector<Asteroid> listofTotalAsteroids = game.getAsteroidVec();

    listofTotalAsteroids.push_back(asteroidFragments.at(0));
    listofTotalAsteroids.push_back(asteroidFragments.at(1));

    game.setAsteroidVec(listofTotalAsteroids);

}