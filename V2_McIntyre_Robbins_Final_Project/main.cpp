/* CSCI261 Final Project
 *
 * Authors: Geoffery McIntyre (Sec E) and Cole Robbins (Sec C)
 *
 * Description: This code allows users to play asteroids using SFML
 */


#include "GameManager.h"
#include <ctime>
#include <random>
                           // using the sf namespace
int main() {
    GameManager gameManager;
    gameManager.startGame();
    return 0;

    return EXIT_SUCCESS;                        // report our program exited successfully
}