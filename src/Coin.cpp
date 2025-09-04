#include "Coin.h"

Coin::Coin(float x, float y, int val) : collected(false),value(val) {
    shape.setRadius(10.f);
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(x, y);
}

void Coin::draw(sf::RenderWindow& window) {
    if (!collected)
        window.draw(shape);
}

void Coin::update(float dt) {
    // Could animate coins later (like rotation/glow)
}
