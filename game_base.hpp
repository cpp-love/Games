// Created by C++.emplace(mine) on 2025/4/12.

#ifndef __GAME_BASE_HPP__
#define __GAME_BASE_HPP__

#include <iostream>
#include <cstdint>

namespace Game {

    enum class Direction : uint8_t {UP = 1 << 0, LEFT = 1 << 1, DOWN = 1 << 2, RIGHT = 1 << 3}; // 用来定义方向
    struct Position {size_t x, y;}; // 用来定义位置
}

#endif // __GAME_BASE_HPP__