#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include "Utils.hpp"
#include "Coin.h"



class Level {
public:
    Level(int width, int height, int platformCount, int coinChance);

    void draw(sf::RenderWindow& window);
    const std::vector<sf::RectangleShape>& getPlatforms() const { return platforms; }
    const std::vector<Coin>& getCoins() const { return coins; }
    std::vector<Coin>& getCoins() { return coins; }


private:
    int width, height;
    std::vector<sf::RectangleShape> platforms;
    std::vector<Coin> coins;
};
