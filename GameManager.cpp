/* CSCI261 Final Project
 *
 * Authors: Geoffrey McIntyre (Sec E) and Cole Robbins (Sec C)
 *
 * Description: This code allows users to play asteroids using SFML
 */

#include <iostream> // for standard input/output
#include <fstream>
#include <ctime>
#include <string>

#include "GameManager.h"
#include "Player.h"
#include "Missile.h"

using namespace sf; // using the sf namespace
using namespace std; // using the standard namespace

//Default Constructor
GameManager::GameManager() {
    running = true;
    hasWon = false;
    isAlive = true;
}

//Gets window dimensions
Vector2f GameManager::getDimensions() {
    return Vector2f(WIDTH, HEIGHT);
}

//Code that manages the game while running
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
    Font myFont;
    bool firstKeyHasPressed = false;

    //Opens and reads winning streak score file
    ifstream inFS("score.txt");

    if(inFS.fail()){
        //If file fails to open (doesn't exist) make a new file
        ofstream outFS("score.txt");
        cout << "No file found. File created" << endl;
        outFS << 0;
        outFS.close();
        highscore = 0;
    }

    //Save highscore value
    inFS >> highscore;
    inFS.close();

    //Randomizes number of asteroids based on the window size
    int numAsteroid = ( (double)rand() / RAND_MAX * 8 + 3 ) * ( ( WIDTH * HEIGHT ) / ( 920 * 920 ) );

    //Add three invisible asteroids for placeholders to keep vector sizing errors from happening
    Asteroid placeholderAst;
    placeholderAst.changeColor();
    asteroidVec.push_back(placeholderAst);
    asteroidVec.push_back(placeholderAst);
    asteroidVec.push_back(placeholderAst);

    //Generate the asteroid vector
    for (int fillAstVec = 0; fillAstVec < numAsteroid; ++fillAstVec) {
        Asteroid fillerAsteroid;
        asteroidVec.push_back(fillerAsteroid);
    }

    while(running) {

        //Load font
        if (!myFont.loadFromFile("arial.ttf")) {
            cerr << "An error has occurred" << endl;
            return -1;
        }

        //Wait for events
        Event event;
        while (window.pollEvent(event)) {      // ask the window if any events occurred
            if (event.type == Event::Closed) { // if event type is a closed event
                // i.e. they clicked the X on the window
                //If in the winning state when window closes
                if(hasWon) {
                    ofstream outFS("score.txt");
                    if(outFS.fail()){
                        return -1;
                    }
                    outFS << highscore + 1;
                    outFS.close();// then close our window
                }
                //if in the losing state when window closes
                if(!isAlive){
                    ofstream outFS("score.txt");
                    if(outFS.fail()){
                        return -1;
                    }
                    outFS << 0;
                    outFS.close();// then close our window
                }
                window.close();
                running = false;
            }
            //While alive, check for keyboard input
            if (isAlive) {
                if (event.type == Event::KeyPressed) {
                    switch (event.key.code) {
                        case sf::Keyboard::Space: //Draw missiles when spacebar is pressed
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
            }
            player.onEvent(event, firstKeyHasPressed);
        }

        //Update the game objects while player is alive
        if(isAlive) {
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

            // This if statements sets the initial ship speed to zero
            if (!firstKeyHasPressed) {
                player.setSpeed(Vector2f(0, 0));
            }

            window.draw(player);

            //Draw the asteroids
            for (int i = 0; i < asteroidVec.size(); ++i) {
                window.draw(asteroidVec.at(i).getAsteroidShape());
            }

            //Handle player collisions with Asteroid
            for (int j = 0; j < asteroidVec.size(); ++j) {
                asteroidVec.at(j).updateAsteroid(time);
                player.collision(asteroidVec, j);
            }

            //Display lives on screen
            Text livesText;
            livesText.setFont(myFont);
            livesText.setString("Lives Left: " + to_string(player.getLives()));
            livesText.setCharacterSize(40);
            livesText.setFillColor(Color::White);

            window.draw(livesText);

            Text winText;
            winText.setPosition(Vector2f(WIDTH / 3, HEIGHT / 3));
            winText.setFont(myFont);
            winText.setString("You Win!");
            winText.setCharacterSize(50);
            winText.setFillColor(Color::White);

            if (asteroidVec.size() - 3 == 0) {
                int streak;
                hasWon = true;
                ifstream displayStreak("score.txt");
                if (!displayStreak.is_open()) {
                    cerr << "File was unable to be opened." << endl;
                    return -1;
                }
                displayStreak >> streak;
                winText.setString("\t\t You Win! \nWinning Streak: " + to_string(++streak));
                window.draw(winText);
                displayStreak.close();
            }

            window.display();

            //Break the loop if player runs out of lives
            if (player.getLives() <= 0) {
                isAlive = false;
            }

        } else {
            //Draw Losing screen
            window.clear();

            Text loseText;
            loseText.setPosition(Vector2f(WIDTH/6,HEIGHT/3));
            loseText.setFont(myFont);
            loseText.setString("\t \t Game Over!\nYour winning streak has ended!");
            loseText.setCharacterSize(50);
            loseText.setFillColor(Color::White);

            window.draw(loseText);

            window.display();
        }
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


