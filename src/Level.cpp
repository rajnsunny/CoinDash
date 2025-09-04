#include "Level.h"

Level::Level(int w, int h, int platformCount, int coinChance)
    : width(w), height(h)
{
    platforms.clear();
    coins.clear();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> xDist(0, w - 100);     // platform x position
    std::uniform_int_distribution<> yDist(50, h - 50);     // platform y position
    std::uniform_int_distribution<> chanceDist(1, 100);    // chance for coin
    std::uniform_int_distribution<> valueDist(1, 100);     // coin value chance

    // generate platforms
    for (int i = 0; i < platformCount; ++i) {
        sf::RectangleShape plat;
        plat.setSize({100.f, 20.f});
        plat.setFillColor(sf::Color::Blue);
        plat.setPosition(xDist(gen), yDist(gen));
        platforms.push_back(plat);

        // maybe put a coin on it
        if (chanceDist(gen) <= coinChance) {
            float x = plat.getPosition().x + plat.getSize().x / 2.f - 10.f;
            float y = plat.getPosition().y - 20.f;

            // decide coin value
            int roll = valueDist(gen);
            int value = 1;
            sf::Color color = sf::Color::Yellow; // default for 1

            if (roll > 90) {
                value = 10;
                color = sf::Color(255, 0, 0); // red for 10
            } else if (roll > 70) {
                value = 5;
                color = sf::Color(255, 165, 0); // orange for 5
            }

            Coin c(x, y, value);
            c.setColor(color);
            coins.push_back(c);
        }
    }

    // ground platform at bottom
    sf::RectangleShape ground;
    ground.setSize({(float)w, 20.f});
    ground.setFillColor(sf::Color::Blue);
    ground.setPosition(0, h - 20.f);
    platforms.push_back(ground);
}

void Level::draw(sf::RenderWindow& window) {
    for (auto& plat : platforms) {
        window.draw(plat);
    }
    for (auto& coin : coins) {
        coin.draw(window);
    }
}
