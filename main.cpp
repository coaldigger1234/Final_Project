/* CSCI261 Final Project
 *
 * Authors: Geoffrey McIntyre (Sec E) and Cole Robbins (Sec C)
 *
 * Description: This code allows users to play asteroids using SFML
 */

#include <random>

#include "GameManager.h"

int main() {
    //Runs Game manager
    GameManager gameManager;
    gameManager.startGame();
    return 0;

    return EXIT_SUCCESS;                        // report our program exited successfully
}