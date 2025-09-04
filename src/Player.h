#pragma once
#include <SFML/Graphics.hpp>
#include "Utils.hpp"

class Player {
private:
    sf::RectangleShape shape;
    sf::Vector2f velocity;
    bool onGround;

    // Jump mechanics
    int maxJumps;
    int jumpsLeft;

    // Timing helpers
    float jumpBufferCounter;  // countdown for buffered input -- STATE VARIABLE
    float coyoteCounter;      // countdown for coyote time    -- STATE VARIABLE

public:
    Player(float x, float y);

    void handleMovementInput();      // left/right
    void queueJump();                // called on KeyPressed
    void update(float dt, const std::vector<sf::RectangleShape>& platforms);
    void draw(sf::RenderWindow& window) const;

    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const { return shape.getPosition(); }

    void resetPosition(float x, float y);
};
