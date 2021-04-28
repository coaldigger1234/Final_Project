//
// Created by Owner on 4/19/2021.
//
#include "GameManager.h"
#include <iostream>                             // for standard input/output
using namespace std;                            // using the standard namespace
#include <random>
#include <ctime>

#include <SFML/Graphics.hpp>                    // include the SFML Graphics Library
#include "Asteroid.h"
#include "Player.h"
#include "Missile.h"

using namespace sf;



GameManager::GameManager() {
    running = true;
}

Vector2f GameManager::getDimensions() {
    return Vector2f(WIDTH, HEIGHT);
}

int GameManager::startGame() {
    srand(time(0));
    rand();
    drawWindow();
    CircleShape shotMissile;
    Player player;
    vector<Missile> missileVec;
    Clock clock;
    Asteroid setAst;
    vector<Player> currPlayerState;
    int numAsteroid = ( (double)rand() / RAND_MAX * 8 + 3 ) * ( ( WIDTH * HEIGHT ) / ( 640 * 640 ) );
    for (int fillAstVec = 0; fillAstVec < numAsteroid; ++fillAstVec) {
        Asteroid fillerAsteroid;
        asteroidVec.push_back(fillerAsteroid);
    }


    while(running){
        Font myFont;
        if (!myFont.loadFromFile("arial.ttf")) {
            cerr << "An error has occurred" << endl;
            return -1;
        }
        Event event;
        while( window.pollEvent(event) ) {      // ask the window if any events occurred
            if( event.type == Event::Closed ) { // if event type is a closed event
                // i.e. they clicked the X on the window
                window.close();                 // then close our window
                running = false;
            }
            if ( event.type == Event::KeyPressed) {
                switch (event.key.code) {
                    case sf::Keyboard::Space:
                        if (missileVec.size() > 2) {
                            missileVec.erase(missileVec.begin() + 0);
                            currPlayerState.erase(currPlayerState.begin() + 0);
                        }
                        Missile currMissile;
                        currPlayerState.push_back(player);
                        missileVec.push_back(currMissile);
                        missileVec.at(missileVec.size() - 1).isShot(player);
                        break;
                }
            }
            player.onEvent(event);
        }

        window.clear(Color::Black);

        //Handle Missile/Asteroid collision
        for (int k = 0; k < missileVec.size(); ++k) {
            for (int asterID = 0; asterID < asteroidVec.size(); ++asterID) {
                missileVec.at(k).hitsAsteroid(asteroidVec, asterID);
            }
            window.draw(missileVec.at(k).getShape());
        }

        //Handle Missile/Player collision
        for (int l = 0; l < missileVec.size(); ++l) {
            missileVec.at(l).updateMissile(currPlayerState.at(l));
            player.collision(asteroidVec, l);
        }

        double time = clock.restart().asMilliseconds();
        player.updatePlayer(time);

        window.draw(player);

        for (int i = 0; i < asteroidVec.size(); ++i) {
            window.draw(asteroidVec.at(i).getAsteroidShape());
        }

        for (int j = 0; j < asteroidVec.size(); ++j) {
            asteroidVec.at(j).updateAsteroid(time);
            player.collision(asteroidVec, j);
        }

        Text livesText;
        livesText.setFont(myFont);
        livesText.setString("Lives Left: " + to_string(player.getLives()));
        livesText.setCharacterSize(40);
        livesText.setFillColor(Color::White);
        window.draw(livesText);

        window.display();
    }
};

void GameManager::drawWindow() {
    if(window.isOpen()) {
        window.close();
    }
    window.create(VideoMode(WIDTH, HEIGHT), "SFML Asteroids Game", Style::Close);
    window.setKeyRepeatEnabled(true);
    window.setFramerateLimit(60);
}

vector<Asteroid> GameManager::getAsteroidVec() {
    return asteroidVec;
}

void GameManager::setAsteroidVec(vector<Asteroid> newAsteroidVec) {
    asteroidVec = newAsteroidVec;
}


