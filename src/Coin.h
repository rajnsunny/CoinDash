#pragma once
#include <SFML/Graphics.hpp>

class Coin {
private:
    sf::CircleShape shape;
    bool collected;
    int value;

public:
    Coin(float x, float y, int val);

    void draw(sf::RenderWindow& window);
    void update(float dt);

    // For collision
    sf::FloatRect getBounds() const { return shape.getGlobalBounds(); }

    const sf::CircleShape& getShape() const { return shape; }

    bool isCollected() const { return collected; }
    void collect() { collected = true; }
    int getValue() const { return value; } 
    void setColor(const sf::Color& col) { shape.setFillColor(col); }

};
