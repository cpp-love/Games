/**
 * @file GameBase.cpp
 * @author cpp-love ()
 * @brief 游戏基础头文件的实现
 * @details 实现了游戏基础头文件中定义的函数
 * @version 0.1
 * @date 2025-05-10
 * 
 * @copyright Copyright 2025 cpp-love
 * 
 * ********************************************************************************
 * @par 修改日志:
 * <table>
 * <tr><th>Date       <th>Version <th>Author   <th>Description
 * <tr><td>2025-05-10 <td>v0.1    <td>cpp-love <td>创建此文件
 * </table>
 * ********************************************************************************
 */

#include "GameBase.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <iostream>
#include <cstdint>

namespace Games {
    const std::filesystem::path FontPath::Chinese("Fonts/SiYuanSongTi.otf");

    template<typename T>
    sf::Vector2<T> operator+(const sf::Vector2<T> &pos, const Direction2D &dir) {
        switch (dir) {
            case Direction2D::UP:
                return {pos.x, pos.y - 1};
            case Direction2D::LEFT:
                return {pos.x - 1, pos.y};
            case Direction2D::DOWN:
                return {pos.x, pos.y + 1};
            case Direction2D::RIGHT:
                return {pos.x + 1, pos.y};
        }
    }
    template<typename T>
    sf::Vector2<T> &operator+=(const sf::Vector2<T> &pos, const Direction2D &dir) {
        switch (dir) {
            case Direction2D::UP:
                pos.y -= 1;
                break;
            case Direction2D::LEFT:
                pos.x -= 1;
                break;
            case Direction2D::DOWN:
                pos.y += 1;
                break;
            case Direction2D::RIGHT:
                pos.x += 1;
                break;
        }
        return pos;
    }
    template<typename T>
    sf::Vector2<T> operator-(const sf::Vector2<T> &pos, const Direction2D &dir) {
        switch (dir) {
            case Direction2D::UP:
                return {pos.x, pos.y + 1};
            case Direction2D::LEFT:
                return {pos.x + 1, pos.y};
            case Direction2D::DOWN:
                return {pos.x, pos.y - 1};
            case Direction2D::RIGHT:
                return {pos.x - 1, pos.y};
        }
    }
    template<typename T>
    sf::Vector2<T> &operator-=(const sf::Vector2<T> &pos, const Direction2D &dir) {
        switch (dir) {
            case Direction2D::UP:
                pos.y += 1;
                break;
            case Direction2D::LEFT:
                pos.x += 1;
                break;
            case Direction2D::DOWN:
                pos.y -= 1;
                break;
            case Direction2D::RIGHT:
                pos.x -= 1;
                break;
        }
        return pos;
    }

    template<typename T>
    sf::Vector3<T> operator+(const sf::Vector3<T> &pos, const Direction3D &dir) {
        switch(dir) {
            case Direction3D::UP:
                return {pos.x, pos.y, pos.z + 1};
            case Direction3D::LEFT:
                return {pos.x - 1, pos.y, pos.z};
            case Direction3D::FORWARD:
                return {pos.x, pos.y - 1, pos.z};
            case Direction3D::DOWN:
                return {pos.x, pos.y, pos.z - 1};
            case Direction3D::RIGHT:
                return {pos.x + 1, pos.y, pos.z};
            case Direction3D::BACKWORD:
                return {pos.x, pos.y + 1, pos.z};
        }
    }
    template<typename T>
    sf::Vector3<T> operator+=(const sf::Vector3<T> &pos, const Direction3D &dir) {
        switch(dir) {
            case Direction3D::UP:
                pos.z += 1;
                break;
            case Direction3D::LEFT:
                pos.x -= 1;
                break;
            case Direction3D::FORWARD:
                pos.y -= 1;
                break;
            case Direction3D::DOWN:
                pos.z -= 1;
                break;
            case Direction3D::RIGHT:
                pos.x += 1;
                break;
            case Direction3D::BACKWORD:
                pos.y += 1;
                break;
        }
        return pos;
    }
    template<typename T>
    sf::Vector3<T> operator-(const sf::Vector3<T> &pos, const Direction3D &dir) {
        switch(dir) {
            case Direction3D::UP:
                return {pos.x, pos.y, pos.z - 1};
            case Direction3D::LEFT:
                return {pos.x + 1, pos.y, pos.z};
            case Direction3D::FORWARD:
                return {pos.x, pos.y + 1, pos.z};
            case Direction3D::DOWN:
                return {pos.x, pos.y, pos.z + 1};
            case Direction3D::RIGHT:
                return {pos.x - 1, pos.y, pos.z};
            case Direction3D::BACKWORD:
                return {pos.x, pos.y - 1, pos.z};
        }
    }
    template<typename T>
    sf::Vector3<T> operator-=(const sf::Vector3<T> &pos, const Direction3D &dir) {
        switch(dir) {
            case Direction3D::UP:
                pos.z -= 1;
                break;
            case Direction3D::LEFT:
                pos.x += 1;
                break;
            case Direction3D::FORWARD:
                pos.y += 1;
                break;
            case Direction3D::DOWN:
                pos.z += 1;
                break;
            case Direction3D::RIGHT:
                pos.x -= 1;
                break;
            case Direction3D::BACKWORD:
                pos.y -= 1;
                break;
        }
        return pos;
    }
}