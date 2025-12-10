#include "Menu.h"
#include <iostream>

const int MENU_ITEMS = 3;
const int NOWA_GRA_INDEX = 0;
const int WCZYTAJ_GRA_INDEX = 1;
const int WYJSCIE_INDEX = 2;

Menu::Menu(float width, float height) : m_selectedItemIndex(0) {

    m_font.loadFromFile("arial.ttf");
    std::vector<std::string> itemTexts = { "Nowa gra", "Wczytaj gre", "Wyjscie" };

    for (int i = 0; i < MENU_ITEMS; ++i) {
        sf::Text text;
        text.setFont(m_font); 
        text.setFillColor(sf::Color::White);
        text.setString(itemTexts[i]);
        text.setCharacterSize(36);

        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f,
            textRect.top + textRect.height / 2.0f);

        text.setPosition(width / 2.0f, height / 2.0f + i * 50);

        m_menuItems.push_back(text);
    }
    m_menuItems[m_selectedItemIndex].setFillColor(sf::Color::Yellow);
}

void Menu::moveUp() {
    if (m_selectedItemIndex > 0) {
        m_menuItems[m_selectedItemIndex].setFillColor(sf::Color::White);
        m_selectedItemIndex--;
        m_menuItems[m_selectedItemIndex].setFillColor(sf::Color::Yellow);
    }
}

void Menu::moveDown() {
    if (m_selectedItemIndex < MENU_ITEMS - 1) {
        m_menuItems[m_selectedItemIndex].setFillColor(sf::Color::White);
        m_selectedItemIndex++;
        m_menuItems[m_selectedItemIndex].setFillColor(sf::Color::Yellow);
    }
}

void Menu::draw(sf::RenderWindow& window) {
    for (int i = 0; i < MENU_ITEMS; ++i) {
        window.draw(m_menuItems[i]);
    }
}

int Menu::getSelectedItem() const {
    return m_selectedItemIndex;
}

void Menu::setStartOptionText(const std::string& text) {
    if (!m_menuItems.empty()) {
        m_menuItems[NOWA_GRA_INDEX].setString(text);

        sf::Text& item = m_menuItems[NOWA_GRA_INDEX];
        sf::FloatRect textRect = item.getLocalBounds();
        item.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    }
}