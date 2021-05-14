//
// Created by michal on 05.05.21.
//

#ifndef GRAVITYSIMULATION_GAME
#define GRAVITYSIMULATION_GAME

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>


//#include "Player.h"
#include "Ball.h"

#include <iostream>
#include <cmath>

class Game
{
private:
    sf::VideoMode videoMode;
    sf::RenderWindow* window{};
    bool endGame{};
    sf::Event ev{};

    int numBalls{};
    std::vector<Ball> balls;



    void initVariables();
    void initBalls();
    void initWindow();
public:
    //Constructors and Destructors
    Game();
    ~Game();

    //Accessors
    bool running();

    //Modifiers

    //Functions
    void updateVelocity();
    void updateCollision();
    void update();
    void render();
    void pollEvents();
};


#endif //GRAVITYSIMULATION_GAME
