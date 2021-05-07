//
// Created by michal on 05.05.21.
//

#include "Game.h"

//Constructors
Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initBalls();

}

Game::~Game()
{
    delete this->window;
}

void Game::initWindow()
{
    this->videoMode = sf::VideoMode(800, 600);
    this->window = new sf::RenderWindow(this->videoMode, "<Gravity Simulation!/>",
                                        sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(60);
}

void Game::initVariables()
{
    this->endGame = false;
    this->numBalls = 4;
    // init balls here
}

void Game::update()
{
    this->pollEvents();
    if (!this->endGame)
    {
        this->updateCollision();
    }
}

void Game::render()
{
    this->window->clear();

    //Render stuff
    for (auto i : this->balls)  // C++ for each equivalent
    {
        i.render(*this->window);
    }

    this->window->display();
}

bool Game::running()
{
    return this->window->isOpen();
}

void Game::pollEvents()
{
    while(this->window->pollEvent(this->ev))
    {
        switch (this->ev.type)
        {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if (this->ev.key.code == sf::Keyboard::Escape)
                    this->window->close();
                break;
            default:
                break;
        }
    }
}


void Game::updateCollision()
{
    // Check for collisions, do math here!
}

void Game::initBalls()
{
    for (int i = 0; i < this->numBalls; ++i)
    {
        this->balls.emplace_back(Ball(*this->window, rand()%BallTypes::NUMTYPES));
    }
}
