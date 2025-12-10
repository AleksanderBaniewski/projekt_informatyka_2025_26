#include <SFML/Graphics.hpp>
#include <array>

#pragma once

class Cegla : public sf::RectangleShape {
private:
    int punktyZycia;
    bool jestZniszczony;
    static const std::array<sf::Color, 4> colorLUT;

public:
    Cegla(sf::Vector2f startPo, sf::Vector2f rozmiar, int L);
    void aktualizujKolor();
    void trafienie();
    void draw(sf::RenderTarget& target) const;

    bool isDestroyed() const { return jestZniszczony; }
    int getPunktyZycia() const { return punktyZycia; }
};