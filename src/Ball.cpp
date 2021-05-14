//
// Created by michal on 06.05.21.
//

#include "Ball.h"

#include <cmath>
#include <complex>


Ball::Ball(const sf::RenderWindow& window)
    : type(type)
{
    this->initVariables();
    this->initShape(window);
}

Ball::~Ball()
{

}

void Ball::initShape(const sf::RenderWindow& window)
{
    this->shape.setRadius(static_cast<float>(this->mass*2));
    this->shape.setOutlineColor(sf::Color::White);
    this->shape.setOutlineThickness(2.f);
    this->shape.setFillColor(sf::Color::Green);
    this->shape.setPosition(
            static_cast<float>(window.getSize().x*0.1f + rand() % window.getSize().x*0.8f),
            static_cast<float>(window.getSize().y*0.1f + rand() % window.getSize().y*0.8f)
            );
}

void Ball::render(sf::RenderTarget& target)
{
    target.draw(this->shape);
}

void Ball::update()
{

}

const sf::CircleShape &Ball::getShape() const
{
    return this->shape;
}

const int &Ball::getType() const
{
    return this->type;
}

void Ball::initVariables()
{
    this->mass = rand()%10 + 2;
//    this->mass = 10;
    this->acceleration = sf::Vector2f(0.f, 0.f);
    // random initial velocity?
//    this->velocity = sf::Vector2f(static_cast<float>(rand()%2), static_cast<float>(rand()%2));
    this->velocity = sf::Vector2f(0.f, 0.f);

}

void Ball::updateAcceleration(Ball ball)
    //gets passed one other ball to calculate force wrt
{
    float GRAVITATIONAL_CONSTANT = 2;
    float numerator = static_cast<float>(GRAVITATIONAL_CONSTANT * this->mass * ball.mass);

    // order very important here!
    float d_x {ball.shape.getPosition().x-this->shape.getPosition().x};
    float d_y {ball.shape.getPosition().y-this->shape.getPosition().y};

    // distance R^2
    float r_squared = pow(d_x, 2) + pow(d_y, 2);

    //Force = G * m1*m2 / R^2
    float F = ((r_squared < pow(this->shape.getRadius(), 2)) ? 0 : numerator / r_squared);

    // Complex number, easy to calculate angle in radians
    std::complex<float> z1(d_x, d_y);
    // outputs radians
    float angle = std::arg(z1);

    // takes in radians
    float f_x = F * std::cos(angle);
    float f_y = F * std::sin(angle);

    // a = F/m
    float a_x = f_x / static_cast<float>(this->mass);
    float a_y = f_y / static_cast<float>(this->mass);

    this->acceleration += sf::Vector2f (a_x, a_y);
}

void Ball::updateVelocity()
{
    // Constant controls max speed, our speed of light!
    if (Ball::vectorMagnitude(this->velocity + this->acceleration) <= 1000){
        this->velocity += this->acceleration;
    }
}

void Ball::setMove()
{
    this->shape.move(this->velocity);
}

void Ball::resetAcceleration()
{
    this->acceleration = sf::Vector2f(0.f, 0.f);
}

float Ball::vectorMagnitude(sf::Vector2f vector)
{
    return static_cast<float>(pow(pow(vector.x, 2) + pow(vector.y, 2), 0.5f));
}

void Ball::setRelativePosition(sf::Vector2f pos)
{
    this->shape.setPosition(this->shape.getPosition() + pos);
}

sf::Vector2f Ball::getVelocity() const
{
    return this->velocity;
}

int Ball::getMass() const
{
    return this->mass;
}

void Ball::setVelocity(sf::Vector2f vel)
{
    this->velocity = vel;
}
