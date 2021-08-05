//
// Created by michal on 05.05.21.
//

#include "Game.h"
#include <cmath>

//Constructors
Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initBalls();
    this->calculateCenterOfGravity();
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
    this->numBalls = 15;
}

void Game::update()
{
    this->pollEvents();
    if (!this->endGame)
    {
        this->updateCollision();
        this->updateVelocity();
        this->calculateCenterOfGravity();
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

    // visualizes center of gravity! (assumes all balls have the same mass!)
    sf::CircleShape centerOfGravity_shape;
    centerOfGravity_shape.setRadius(3.f);
    centerOfGravity_shape.setFillColor(sf::Color::Magenta);
    centerOfGravity_shape.setPosition(this->centerOfGravity.x, this->centerOfGravity.y);
    this->window->draw(centerOfGravity_shape);
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


void Game::initBalls()
{
    for (int i = 0; i < this->numBalls; ++i)
    {
        this->balls.emplace_back(Ball(*this->window));
    }
}

void Game::updateVelocity()
{


    //For each ball, loop over all other balls
    //reset acceleration
    for (auto & ball : this->balls)
    {
        ball.resetAcceleration();
    }


    // Calculate the acceleration of ball i wrt to all other balls
    for (int i = 0; i < this->balls.size(); ++i)
    {
        for (int j = 0; j < this->balls.size(); ++j)
        {
            if (i != j)
            {
                this->balls[i].updateAcceleration(this->balls[j]);
            }
        }
    }
    // I Should have every balls acceleration
    // now for each ball, change it's velocity and move it accordingly
    for (auto & ball : this->balls)
    {
        ball.updateVelocity();
        ball.setMove();

    }
}

void Game::updateCollision()
{
    for (int i = 0; i < this->balls.size(); ++i)
    {
        for (int j = i + 1; j < this->balls.size(); ++j)
        {
            // if the dist between balls <= the sum of their radiuses, then they are overlapping!
            const sf::Vector2f collideVec = this->balls[i].getShape().getPosition() - this->balls[j].getShape().getPosition();
            const float dist = std::sqrt(collideVec.x*collideVec.x + collideVec.y*collideVec.y);
            const float minDist = this->balls[i].getShape().getRadius()+this->balls[j].getShape().getRadius();

            if (dist < minDist)
            {
                // set their velocities to be equal but opposite
                const sf::Vector2f collideAxe = collideVec / dist;
                this->balls[i].setRelativePosition(0.5f * (minDist - dist) * collideAxe);
                this->balls[j].setRelativePosition(-0.5f * (minDist - dist) * collideAxe);

                // Set
                const sf::Vector2f momentum1_init = static_cast<float>(this->balls[i].getMass()) * this->balls[i].getVelocity();
                const sf::Vector2f momentum2_init = static_cast<float>(this->balls[j].getMass()) * this->balls[j].getVelocity();

                const sf::Vector2f momentum = momentum1_init + momentum2_init;
                /*Calculates Velocities assuming perfectly elastic collisions
                 1) V_1_i + V_1_f = V_2_i + V_2_f
                 2) Conservation of momentum
                 Express V2_final in terms of V_1_final
                 Sub into conservation of momentum -> gets V2_final
                 Sub V2_final back into first Eq to get V1_final
                */
                const sf::Vector2f V_2xm_1 = this->balls[j].getVelocity() * static_cast<float>(this->balls[i].getMass());
                const sf::Vector2f V2_final = (momentum - V_2xm_1 + momentum1_init)/static_cast<float>(this->balls[i].getMass() + this->balls[j].getMass());
                const sf::Vector2f V1_final = V2_final + this->balls[j].getVelocity() - this->balls[i].getVelocity();

                // Scale to remove some energy from the system.
                this->balls[i].setVelocity(0.9f*V1_final);
                this->balls[j].setVelocity(0.9f*V2_final);
            }
        }
    }
}

void Game::calculateCenterOfGravity()
{
    sf::Vector2f tempCenterOfGravity{0.f, 0.f};
    for (const auto& ball : this->balls) {
        tempCenterOfGravity.x += ball.getShape().getPosition().x;
        tempCenterOfGravity.y += ball.getShape().getPosition().y;
    }
    tempCenterOfGravity.x = tempCenterOfGravity.x / this->balls.size();
    tempCenterOfGravity.y = tempCenterOfGravity.y / this->balls.size();
    this->centerOfGravity = tempCenterOfGravity;

}
