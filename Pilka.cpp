#include "Pilka.h"
#include <cmath> 
#include <iostream>

Pilka::Pilka(sf::Vector2f startPos, float radius, sf::Vector2f startVel) : velocity(startVel)
{
    m_shape.setPosition(startPos);
    m_shape.setFillColor(sf::Color::White);
    m_shape.setRadius(radius);
    m_shape.setOrigin({ radius, radius });
}

void Pilka::draw(sf::RenderTarget& window) {
    window.draw(m_shape);
}

void Pilka::ruch(sf::Time dt, float windowWidth, float windowHeight) {
    m_shape.move(velocity * dt.asSeconds());

    float xb = m_shape.getPosition().x;
    float yb = m_shape.getPosition().y;
    float rb = m_shape.getRadius();

    if (xb - rb <= 0.f) { odbijX(); m_shape.setPosition(rb, yb); }
    else if (xb + rb >= windowWidth) { odbijX(); m_shape.setPosition(windowWidth - rb, yb); }

    if (yb - rb <= 0.f) { odbijY(); m_shape.setPosition(xb, rb); }

    if (yb - rb > windowHeight) {
        spadlaNaDno_ = true;
        velocity.y = 0;
        velocity.x = 0;
    }
}

bool Pilka::collidePaddle(const Paletka& p) {
    float palX = p.getPosition().x;
    float palY = p.getPosition().y;
    float palW = p.getSize().x;
    float palH = p.getSize().y;
    float pilkaX = getX();
    float pilkaY = getY();
    float radius = getRadius();

    float paddleTop = palY - palH / 2.f;

    bool horizontalOverlap = (pilkaX + radius) >= (palX - palW / 2.f) &&
        (pilkaX - radius) <= (palX + palW / 2.f);

    bool verticalCollision = (pilkaY + radius) >= paddleTop &&
        (pilkaY - radius) < paddleTop;

    if (horizontalOverlap && verticalCollision) {
        if (velocity.y > 0) {
            velocity.y = -std::abs(velocity.y);
            m_shape.setPosition(pilkaX, paddleTop - radius);
            return true;
        }
    }
    return false;
}

void Pilka::reset(const sf::Vector2f& pos, const sf::Vector2f& vel) {
    m_shape.setPosition(pos);
    velocity = vel;
    spadlaNaDno_ = false;
}