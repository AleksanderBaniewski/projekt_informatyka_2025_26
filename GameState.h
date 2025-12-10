#include <SFML/Graphics.hpp>
#include <vector>
#include <fstream>
#include <string>
#include "Paletka.h"
#include "Pilka.h"
#include "Cegla.h"

#pragma once

extern const float WIDTH;
extern const float HEIGHT;

const int GAMESTATE_KOLUMN = 6;
const float GAMESTATE_PRZERWA = 2.f;
const float GAMESTATE_BLOCK_X = (WIDTH - (GAMESTATE_KOLUMN + 1) * GAMESTATE_PRZERWA) / GAMESTATE_KOLUMN;
const float GAMESTATE_BLOCK_Y = 25.f;

struct BlockData {
    float x, y;
    int hp;
};

class GameState {
private:
    sf::Vector2f paddlePosition;
    sf::Vector2f ballPosition;
    sf::Vector2f ballVelocity;
    std::vector<BlockData> blocks;

public:
    void capture(const Paletka& p, const Pilka& b, const std::vector<Cegla>& cegly);
    bool saveToFile(const std::string& filename);
    bool loadFromFile(const std::string& filename);
    void apply(Paletka& p, Pilka& b, std::vector<Cegla>& cegly) const;
};