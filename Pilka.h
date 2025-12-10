#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include "Paletka.h"

#pragma once

class Pilka {
private:
    sf::CircleShape m_shape;
    sf::Vector2f velocity;
    bool spadlaNaDno_ = false;

public:
    Pilka(sf::Vector2f startPos, float radius, sf::Vector2f startVel);
    void odbijX() { velocity.x = -velocity.x; }
    void odbijY() { velocity.y = -velocity.y; }
    void draw(sf::RenderTarget& window);
    void ruch(sf::Time dt, float windowWidth, float windowHeight);
    bool collidePaddle(const Paletka& p);

    void reset(const sf::Vector2f& pos, const sf::Vector2f& vel);
    sf::Vector2f getVelocity() const { return velocity; }

    const sf::CircleShape& getShapeForCapture() const { return m_shape; }

    sf::FloatRect getGlobalBounds() const { return m_shape.getGlobalBounds(); }
    float getX() const { return m_shape.getPosition().x; }
    float getY() const { return m_shape.getPosition().y; }
    float getVx() const { return velocity.x; }
    float getVy() const { return velocity.y; }
    float getRadius() const { return m_shape.getRadius(); }
    bool spadlaNaDno() const { return spadlaNaDno_; }
};