#pragma once
#include <cstdlib>
#include <iostream>

#define debug(x) std::cout<<x<<"\n"

static constexpr float GRAVITY = 800.f;
static constexpr float SPEED = 200.f;
static constexpr float JUMP_STRENGTH = 300.f;
static constexpr int WINDOW_WIDTH = 800;
static constexpr int WINDOW_HEIGHT = 600;
static constexpr float PLAYER_SIZE = 40.f;
static constexpr int MAX_JUMP = 5;
static constexpr float JUMP_BUFFER_TIME = 0.1f; // seconds
static constexpr float COYOTE_TIME = 0.1f;      //seconds
constexpr float COLLISION_TOLERANCE = 20.f;  


inline int randomInt(int min, int max) {
    return min + std::rand() % ((max - min) + 1);
}

