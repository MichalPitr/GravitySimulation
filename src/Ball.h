//
// Created by michal on 06.05.21.
//

#ifndef GRAVITYSIMULATION_BALL
#define GRAVITYSIMULATION_BALL

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>


class Ball
{
private:
    sf::CircleShape shape;
    int type;
    int mass{};
    sf::Vector2f velocity;
    sf::Vector2f acceleration;

    void initVariables();
    void initShape(const sf::RenderWindow& window);

public:
    Ball(const sf::RenderWindow& window);
    virtual ~Ball();

    //Accessor
    const sf::CircleShape& getShape() const;
    const int& getType() const;
    sf::Vector2f getVelocity() const;
    int getMass() const;

    //setters
    void setRelativePosition(sf::Vector2f pos);
    void setVelocity(sf::Vector2f velocity);
    //functions

    void update();
    void updateAcceleration(Ball ball);
    void resetAcceleration();
    void updateVelocity();
    static float vectorMagnitude(sf::Vector2f vector);
    void setMove();
    void render(sf::RenderTarget& target);
};


#endif //GRAVITYSIMULATION_BALL
