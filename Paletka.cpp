#include "Paletka.h"
#include <SFML/Window/Keyboard.hpp>

Paletka::Paletka(sf::Vector2f startPos, sf::Vector2f rozmiar, float predkoscX)
{
    velocity.x = predkoscX;
    velocity.y = 0.f;
    m_shape.setPosition(startPos);
    m_shape.setFillColor(sf::Color::Green);
    m_shape.setSize(rozmiar);
    m_shape.setOrigin({ rozmiar.x / 2.f, rozmiar.y / 2.f });
}

void Paletka::draw(sf::RenderTarget& window) {
    window.draw(m_shape);
}

void Paletka::ruch(sf::Time dt, float windowWidth) {
    float delta_x = 0.f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        delta_x -= velocity.x * dt.asSeconds();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        delta_x += velocity.x * dt.asSeconds();
    }

    m_shape.move({ delta_x, 0.f });

    float halfWidth = m_shape.getSize().x / 2.f;
    float currentY = m_shape.getPosition().y;

    if (m_shape.getPosition().x - halfWidth < 0.f) {
        m_shape.setPosition(sf::Vector2f(halfWidth, currentY));
    }

    if (m_shape.getPosition().x + halfWidth > windowWidth) {
        m_shape.setPosition(sf::Vector2f(windowWidth - halfWidth, currentY));
    }
}

void Paletka::setPosition(const sf::Vector2f& pos) {
    m_shape.setPosition(pos);
}