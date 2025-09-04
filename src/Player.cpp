#include "Player.h"

Player::Player(float x, float y)
    : onGround(false),
      maxJumps(MAX_JUMP),
      jumpsLeft(MAX_JUMP),
      jumpBufferCounter(0.f),
      coyoteCounter(0.f) 
{
    shape.setSize({x, y});
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(x, y);
    velocity = {0.f, 0.f};
}

void Player::handleMovementInput() {
    velocity.x = 0;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        velocity.x = -SPEED;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        velocity.x = SPEED;
}

void Player::queueJump() {
    jumpBufferCounter = JUMP_BUFFER_TIME;
}

void Player::update(float dt, const std::vector<sf::RectangleShape>& platforms) {
    // Gravity
    velocity.y += GRAVITY * dt;

    // Timers
    if (jumpBufferCounter > 0.f) jumpBufferCounter -= dt;
    if (coyoteCounter > 0.f)     coyoteCounter -= dt;

    // Horizontal move
    shape.move(velocity.x * dt, 0);

    // Vertical move
    shape.move(0, velocity.y * dt);

    // Reset ground state
    onGround = false;

    // Collision
    for (auto& plat : platforms) {
        if (shape.getGlobalBounds().intersects(plat.getGlobalBounds())) {
            // Falling onto platform
            if (velocity.y > 0 &&
                shape.getPosition().y + shape.getSize().y <= plat.getPosition().y + COLLISION_TOLERANCE) {
                shape.setPosition(shape.getPosition().x,
                                  plat.getPosition().y - shape.getSize().y);
                velocity.y = 0;
                onGround = true;
            }
        }
    }

    // Update coyote + jumps
    if (onGround) {
        coyoteCounter = COYOTE_TIME;
        jumpsLeft = MAX_JUMP;
    }

    // Perform jump if buffered and allowed
    if (jumpBufferCounter > 0.f && (jumpsLeft > 0 || coyoteCounter > 0.f)) {
        velocity.y = -JUMP_STRENGTH;
        jumpsLeft--;
        jumpBufferCounter = 0.f;
        coyoteCounter = 0.f;
    }
}

void Player::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}

sf::FloatRect Player::getBounds() const {
    return shape.getGlobalBounds();
}

void Player::resetPosition(float x, float y) {
    shape.setPosition(x, y);
    velocity = {0.f, 0.f};
    onGround = false;
    jumpsLeft = maxJumps;
    jumpBufferCounter = 0.f;
    coyoteCounter = 0.f;
}
