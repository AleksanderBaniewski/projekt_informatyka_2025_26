#include <SFML/Graphics.hpp>
#include <vector>
#include "Paletka.h"
#include "Pilka.h"
#include "Cegla.h" 
#include "GameState.h" 
#include "Menu.h" 

#pragma once

extern const float WIDTH;
extern const float HEIGHT;
extern const float PADDLE_Y;

const int GAME_STATE_MENU = 0;
const int GAME_STATE_PLAYING = 1;
const int GAME_STATE_GAMEOVER = 2;
const int GAME_STATE_EXITING = 3;


class Game {
private:
    sf::RenderWindow m_window;
    sf::Clock m_deltaClock;

    Paletka m_paletka;
    Pilka m_pilka;
    std::vector<Cegla> m_bloki;

    int m_currentState = GAME_STATE_MENU;

    Menu m_menu;
    GameState m_gameStateSnapshot;
    bool m_gameStartedOnce = false;

    void generateLevel();
    void processEvents();
    void update(sf::Time dt);
    void render();

public:
    Game();
    void run();

    void captureState(GameState& state);
    void applyState(const GameState& state);
    bool isGameOver() const;
};