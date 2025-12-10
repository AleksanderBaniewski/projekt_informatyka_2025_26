#include "Game.h"
#include <iostream>

const float WIDTH = 640.f;
const float HEIGHT = 480.f;
const float PADDLE_Y = 440.f;

const int ILOSC_KOLUMN = 6;
const int ILOSC_WIERSZY = 7;
const float ROZMIAR_BLOKU_Y = 25.f;
const float PRZERWA = 2.f;
const float OFFSET_TOP = 50.f;
const float ROZMIAR_BLOKU_X = (WIDTH - (ILOSC_KOLUMN + 1) * PRZERWA) / ILOSC_KOLUMN;

void Game::generateLevel() {
    m_bloki.clear();
    for (int y = 0; y < ILOSC_WIERSZY; ++y) {
        for (int x = 0; x < ILOSC_KOLUMN; ++x) {
            int L = (y < 1) ? 3 : (y < 3) ? 2 : 1;

            float posX = PRZERWA + (ROZMIAR_BLOKU_X / 2.f) + x * (ROZMIAR_BLOKU_X + PRZERWA);
            float posY = OFFSET_TOP + (ROZMIAR_BLOKU_Y / 2.f) + y * (ROZMIAR_BLOKU_Y + PRZERWA);

            m_bloki.emplace_back(sf::Vector2f(posX, posY),
                sf::Vector2f(ROZMIAR_BLOKU_X, ROZMIAR_BLOKU_Y), L);
        }
    }
}

Game::Game() :
    m_window(sf::VideoMode({(unsigned)WIDTH,(unsigned)HEIGHT }), "Arkanoid"),
    m_menu(WIDTH, HEIGHT),
    m_paletka({ WIDTH / 2.f, PADDLE_Y }, { 150.f, 10.f }, 350.f),
    m_pilka({ WIDTH / 2.f, HEIGHT / 2.f }, 10.f, { 200.f, 200.f })
{
    m_window.setFramerateLimit(60);
    generateLevel();
}

void Game::processEvents() {
    sf::Event event;
    while (m_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            m_currentState = GAME_STATE_EXITING;
        }

        if (m_currentState == GAME_STATE_MENU) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    m_menu.moveUp();
                }
                else if (event.key.code == sf::Keyboard::Down) {
                    m_menu.moveDown();
                }
                else if (event.key.code == sf::Keyboard::Enter) {
                    if (m_menu.getSelectedItem() == NOWA_GRA_INDEX) {
                        m_currentState = GAME_STATE_PLAYING;
                        m_gameStartedOnce = true;
                    }
                    else if (m_menu.getSelectedItem() == WCZYTAJ_GRA_INDEX) {
                        if (m_gameStateSnapshot.loadFromFile("zapis.txt")) {
                            applyState(m_gameStateSnapshot);
                            m_currentState = GAME_STATE_PLAYING;
                            m_gameStartedOnce = true;
                            std::cout << "Gra wczytana pomyslnie!\n";
                        }
                    }
                    else if (m_menu.getSelectedItem() == WYJSCIE_INDEX) {
                        m_currentState = GAME_STATE_EXITING;
                    }
                }
            }
        }
        else if (m_currentState == GAME_STATE_PLAYING) {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5) {
                captureState(m_gameStateSnapshot);
                if (m_gameStateSnapshot.saveToFile("zapis.txt")) {
                    std::cout << "Gra zapisana pomyslnie!\n";
                }
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                m_currentState = GAME_STATE_MENU;
            }
        }
    }
}

void Game::update(sf::Time dt) {
    if (m_currentState == GAME_STATE_PLAYING) {
        m_paletka.ruch(dt, WIDTH);
        m_pilka.ruch(dt, WIDTH, HEIGHT);

        if (m_pilka.collidePaddle(m_paletka)) {}
        sf::FloatRect pilkaBounds = m_pilka.getGlobalBounds();
        for (auto& blok : m_bloki) {
            if (blok.isDestroyed()) continue;

            if (pilkaBounds.intersects(blok.getGlobalBounds())) {
                blok.trafienie();
                m_pilka.odbijY();
                break;
            }
        }
        if (isGameOver()) {
            m_currentState = GAME_STATE_GAMEOVER;
            std::cout << "MISS! KONIEC GRY\n";
        }
    }

    if (m_currentState == GAME_STATE_MENU) {
        m_menu.setStartOptionText(m_gameStartedOnce ? "Kontynuuj" : "Nowa gra");
    }
}

void Game::render() {
    m_window.clear(sf::Color(20, 20, 30));
    if (m_currentState == GAME_STATE_MENU) {
        m_menu.draw(m_window);
    }
    else if (m_currentState == GAME_STATE_PLAYING || m_currentState == GAME_STATE_GAMEOVER) {
        for (auto& blok : m_bloki) {
            blok.draw(m_window);
        }
        m_paletka.draw(m_window);
        m_pilka.draw(m_window);
    }
    m_window.display();
}

void Game::run() {
    while (m_window.isOpen() && m_currentState != GAME_STATE_EXITING) {
        sf::Time dt = m_deltaClock.restart();
        processEvents();
        update(dt);
        render();
    }
}

void Game::captureState(GameState& state) {
    state.capture(m_paletka, m_pilka, m_bloki);
}

void Game::applyState(const GameState& state) {
    state.apply(m_paletka, m_pilka, m_bloki);
}

bool Game::isGameOver() const {
    return m_pilka.spadlaNaDno();
}