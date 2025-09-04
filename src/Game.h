#pragma once
#include <SFML/Graphics.hpp>
#include <numeric>
#include <chrono>
#include <future>
#include "Player.h"
#include "Level.h"
#include "Utils.hpp"

class Game {
public:
    Game(int width, int height);
    ~Game() { delete currentLevel; }
    void run();
    


private:
    void processEvents();
    void update(float dt);
    void render();
    void nextLevel();
    void initLevel(Level* lvl);
    void loadLevel();
    void startLoadingNextLevel();

    sf::RenderWindow window;
    sf::Font font;
    sf::Text uiText;
    sf::RectangleShape exitButton;

    Player player;
    Level* currentLevel{nullptr};
    std::future<Level*> nextLevelFuture;
    bool nextLevelReady = false;

    int width, height;
    int levelNumber{1};
    int coinsCollected = 0;  
    unsigned int minCoinsRequiredThisLevel = 0;
    unsigned int coinsCollectedThisRun = 0;

};
