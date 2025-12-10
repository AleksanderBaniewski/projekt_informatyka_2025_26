#include <SFML/Graphics.hpp>
#include <vector>
#include <string> 

#pragma once

extern const int MENU_ITEMS;
extern const int NOWA_GRA_INDEX;
extern const int WCZYTAJ_GRA_INDEX;
extern const int WYJSCIE_INDEX;

class Menu {
private:
    int m_selectedItemIndex;
    sf::Font m_font;
    std::vector<sf::Text> m_menuItems;

public:
    Menu(float width, float height);
    void moveUp();
    void moveDown();
    void draw(sf::RenderWindow& window);
    int getSelectedItem() const;
    void setStartOptionText(const std::string& text);
};