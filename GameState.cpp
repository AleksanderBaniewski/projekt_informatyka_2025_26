#include "GameState.h"
#include <iostream>

void GameState::capture(const Paletka& p, const Pilka& b, const std::vector<Cegla>& cegly) {
    paddlePosition = p.getPosition();
    ballPosition = b.getShapeForCapture().getPosition();
    ballVelocity = b.getVelocity();

    blocks.clear();
    for (const auto& cegla : cegly) {
        if (cegla.getPunktyZycia() > 0) {
            blocks.push_back({ cegla.getPosition().x, cegla.getPosition().y, cegla.getPunktyZycia() });
        }
    }
}

bool GameState::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) return false;

    file << "PADDLE " << paddlePosition.x << " " << paddlePosition.y << "\n";
    file << "BALL " << ballPosition.x << " " << ballPosition.y << " "
        << ballVelocity.x << " " << ballVelocity.y << "\n";

    file << "BLOCKS_COUNT " << blocks.size() << "\n";

    for (const auto& block : blocks) {
        file << block.x << " " << block.y << " " << block.hp << "\n";
    }

    file.close();
    return true;
}

bool GameState::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    std::string label;
    int blocksCount;

    if (!(file >> label >> paddlePosition.x >> paddlePosition.y) || label != "PADDLE") return false;
    if (!(file >> label >> ballPosition.x >> ballPosition.y >> ballVelocity.x >> ballVelocity.y) || label != "BALL") return false;
    if (!(file >> label >> blocksCount) || label != "BLOCKS_COUNT") return false;

    blocks.clear();
    for (int i = 0; i < blocksCount; ++i) {
        BlockData data;
        if (!(file >> data.x >> data.y >> data.hp)) {
            blocks.clear();
            return false;
        }
        blocks.push_back(data);
    }

    file.close();
    return true;
}

void GameState::apply(Paletka& p, Pilka& b, std::vector<Cegla>& cegly) const {
    p.setPosition(paddlePosition);
    b.reset(ballPosition, ballVelocity);

    cegly.clear();

    sf::Vector2f blockSize(GAMESTATE_BLOCK_X, GAMESTATE_BLOCK_Y);

    for (const auto& data : blocks) {
        cegly.emplace_back(sf::Vector2f(data.x, data.y), blockSize, data.hp);
    }
}