#include "Game.h"

Game::Game(int w, int h) 
    : window(sf::VideoMode(w, h), "Platformer with Levels"), 
      player(PLAYER_SIZE,PLAYER_SIZE),width(w), height(h), levelNumber(1){

    window.setKeyRepeatEnabled(false);

    if (!font.loadFromFile("assets/fonts/DejaVuSans.ttf")) {
        std::cerr << "Font not found!\n";
        exit(1);
    }

    uiText.setFont(font);
    uiText.setCharacterSize(20);
    uiText.setFillColor(sf::Color::White);
    uiText.setPosition(10, 10);

    loadLevel();
}

void Game::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        processEvents();
        update(dt);
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) 
            window.close();

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) {
            player.queueJump();   //only once per press
        }
    }
}


void Game::update(float dt) {

    player.handleMovementInput();     // left/right
    player.update(dt, currentLevel->getPlatforms());


    // Coin collection
    for (auto& coin : currentLevel->getCoins()) {
        if (!coin.isCollected() && player.getBounds().intersects(coin.getBounds())) {
            coin.collect();
            coinsCollected += coin.getValue();
            coinsCollectedThisRun += coin.getValue();
        }
    }

    // --- Poll async next level ---
    if (nextLevelFuture.valid() &&
        nextLevelFuture.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
        nextLevelReady = true;
    }

    // Check if player touches exit button
    if (player.getBounds().intersects(exitButton.getGlobalBounds())) {
        if (coinsCollectedThisRun >= minCoinsRequiredThisLevel) {
            levelNumber++;
            if(nextLevelReady) {
                auto preloadStart = std::chrono::high_resolution_clock::now();
                delete currentLevel;
                Level* lvl = nextLevelFuture.get(); 
                initLevel(lvl);
                nextLevelReady = false;
                auto preloadEnd = std::chrono::high_resolution_clock::now();

                auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(preloadEnd - preloadStart).count();
                std::cout << "[ASYNC] Level " << levelNumber << " was preloaded in " << ms << " ms\n";
                // start preloading the NEXT one
                startLoadingNextLevel();
            } else {
                loadLevel();
            }
        } else {
            // reset whole game
            levelNumber = 1;
            coinsCollected = 0;
            loadLevel();
        }
    }

    uiText.setString(
        "Level: " + std::to_string(levelNumber) +
        "\nTotal Coins: " + std::to_string(coinsCollected) +
        "\nLevel Coins: " + std::to_string(coinsCollectedThisRun) +
        "\nNeed: " + std::to_string(minCoinsRequiredThisLevel)
    );

}

void Game::render() {
    window.clear();
    currentLevel->draw(window);
    player.draw(window);
    window.draw(uiText);
    window.draw(exitButton);
    window.display();
}

[[deprecated("use loadLevel instead")]]
void Game::nextLevel() {
    delete currentLevel;
    levelNumber++;
    currentLevel = new Level(width, height, 4 + levelNumber, 40); // harder each level

    // Spawn player above the first platform of new level
    const auto &platforms = currentLevel->getPlatforms();
    if (!platforms.empty()) {
        const sf::RectangleShape &firstPlat = platforms[0];
        float playerHeight = player.getBounds().height;
        float spawnX = firstPlat.getPosition().x + 20.f; // a bit from left edge
        float spawnY = firstPlat.getPosition().y - playerHeight - 5.f; // above the platform
        player.resetPosition(spawnX, spawnY);
    } else {
        // fallback if no platforms
        player.resetPosition(100.f, 100.f);
    }
}

void Game::startLoadingNextLevel(){
    unsigned int numPlatforms = 4 + levelNumber + 1;
    unsigned int coinChance = 50;

    // Async task for generating the level
    nextLevelFuture = std::async(std::launch::async, [=]() {
        return new Level(width, height, numPlatforms, coinChance);
    });
}

void Game::loadLevel() {

    auto start = std::chrono::high_resolution_clock::now();


    // cleanup old
    if (currentLevel) {
        delete currentLevel;
        currentLevel = nullptr;
    }


    // create new Level with more platforms/coins as level increases
    unsigned int numPlatforms = 4 + levelNumber;
    unsigned int coinChance = 50; // % chance of coin on a platform
    Level* lvl = new Level(width, height, numPlatforms, coinChance);

    initLevel(lvl);  

    auto end = std::chrono::high_resolution_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "[SYNC] Level " << levelNumber << " generated in " << ms << " ms\n";


    startLoadingNextLevel();     //async preload

}

void Game::initLevel(Level* lvl) {
    currentLevel = lvl;

    // reset per-level counters
    coinsCollectedThisRun = 0;

    // compute how many coins exist in this level
    unsigned int coinsThisLevel = std::accumulate(
        currentLevel->getCoins().begin(),
        currentLevel->getCoins().end(),
        0u,
        [](unsigned int sum, const Coin &c){
            return sum + c.getValue();
        }
    );

    // choose a random % required for this level
    float minBase = 0.4f; // 40%
    float maxBase = 0.6f; // 60%
    float minPercent = std::min(1.0f, minBase + 0.05f * (levelNumber-1)); // +5% per level
    float maxPercent = std::min(1.0f, maxBase + 0.05f * (levelNumber-1));

    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(minPercent, maxPercent);
    float percent = dist(gen);

    minCoinsRequiredThisLevel = static_cast<unsigned int>(coinsThisLevel * percent);

    // place the player back at the start
    player.resetPosition(100.f, 100.f);

    // create the exit button at bottom-right
    exitButton.setSize({80.f, 40.f});
    exitButton.setFillColor(sf::Color::Blue);
    exitButton.setPosition(width - exitButton.getSize().x - 10.f,
                           height - exitButton.getSize().y - 10.f);

}


