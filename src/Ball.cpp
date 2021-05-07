//
// Created by michal on 06.05.21.
//

#include "Ball.h"

Ball::Ball(const sf::RenderWindow& window, int type)
    : type(type)
{
    this->initShape(window);
}

Ball::~Ball()
{

}

void Ball::initShape(const sf::RenderWindow& window)
{
    sf::Color color;

    switch (this->type)
    {
        case DEFAULT:
            color = sf::Color(rand()%255+1, rand()%255+1, rand()%255+1, 255);
            break;
        case DAMAGING:
            color = sf::Color(255, 0, 0, 255);
            this->shape.setOutlineColor(sf::Color::White);
            this->shape.setOutlineThickness(2.f);
            break;
        case HEALING:
            color = sf::Color(0, 255, 0, 255);
            this->shape.setOutlineColor(sf::Color::White);
            this->shape.setOutlineThickness(2.f);
            break;
    }
    this->shape.setRadius(static_cast<float>(rand()%10+10));
    this->shape.setFillColor(color);
    this->shape.setPosition(
            static_cast<float>(rand() % window.getSize().x),
            static_cast<float>(rand() % window.getSize().y)
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
