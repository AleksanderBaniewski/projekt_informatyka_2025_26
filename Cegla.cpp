#include "Cegla.h"
#include <algorithm>
#include <iostream>

const std::array<sf::Color, 4> Cegla::colorLUT = {
    sf::Color::Transparent,
    sf::Color::Red,
    sf::Color::Yellow,
    sf::Color::Blue
};

Cegla::Cegla(sf::Vector2f startPo, sf::Vector2f rozmiar, int L)
    : sf::RectangleShape(rozmiar),
    punktyZycia(L),
    jestZniszczony(false)
{
    this->setPosition(startPo);
    this->setOrigin(rozmiar.x / 2.f, rozmiar.y / 2.f);
    this->setOutlineThickness(2.f);
    this->setOutlineColor(sf::Color::Black);
    aktualizujKolor();
}

void Cegla::trafienie() {
    if (jestZniszczony)
        return;

    punktyZycia--;
    aktualizujKolor();

    if (punktyZycia <= 0) {
        jestZniszczony = true;
    }
}

void Cegla::aktualizujKolor() {
    int index = std::max(0, std::min(punktyZycia, 3));
    this->setFillColor(colorLUT[index]);
}

void Cegla::draw(sf::RenderTarget& target) const {
    if (!jestZniszczony) {
        target.draw(*this);
    }
}