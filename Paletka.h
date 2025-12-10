#include <SFML/Graphics.hpp>

#pragma once

class Paletka {
private:
    sf::RectangleShape m_shape;
    sf::Vector2f velocity;

public:
    Paletka(sf::Vector2f startPos, sf::Vector2f rozmiar, float predkoscX);
    void draw(sf::RenderTarget& window);
    void ruch(sf::Time dt, float windowWidth);

    void setPosition(const sf::Vector2f& pos);

    sf::FloatRect getGlobalBounds() const { return m_shape.getGlobalBounds(); }
    sf::Vector2f getPosition() const { return m_shape.getPosition(); }
    sf::Vector2f getSize() const { return m_shape.getSize(); }
};