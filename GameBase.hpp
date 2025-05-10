/**
 * @file game_base.hpp
 * @author cpp-love ()
 * @brief 游戏基础头文件
 * @details 声明了游戏中使用的基础运算符重载和枚举类型，包括方向等
 * @version 0.1.1
 * @date 2025-05-10
 * 
 * @copyright Copyright 2025 cpp-love
 * 
 * ********************************************************************************
 * @par 修改日志:
 * <table>
 * <tr><th>Date       <th>Version <th>Author   <th>Description
 * <tr><td>2025-04-12 <td>v0.1    <td>cpp-love <td>创建此文件
 * <tr><td>2025-05-10 <td>v0.1.1  <td>cpp-love <td>
 * -# 使用模板类sf::Vector2以及sf::Vector3替代类Games::Position
 * -# 使用类Games::Direction2D以及Games::Direction3D替代类Games::Direction
 * -# 添加了游戏基础运算符重载
 * -# 添加了类Games::FontPath
 * </table>
 * ********************************************************************************
 */

#ifndef __GAMEBASE_HPP__
#define __GAMEBASE_HPP__


#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>
#include <iostream>
#include <cstdint>
#include <filesystem>

namespace Games {

    class FontPath {
        public:
            static const std::filesystem::path Chinese;
    };

    enum class Direction2D : uint8_t {UP = 1 << 0, LEFT = 1 << 1, DOWN = 1 << 2, RIGHT = 1 << 3}; // 用来定义方向
    enum class Direction3D : uint8_t {UP = 1 << 0, LEFT = 1 << 1, FORWARD = 1 << 2, DOWN = 1 << 4, RIGHT = 1 << 5, BACKWORD = 1 << 6};

    template<typename T>
    sf::Vector2<T> operator+(const sf::Vector2<T> &pos, const Direction2D &dir);
    template<typename T>
    sf::Vector2<T> &operator+=(const sf::Vector2<T> &pos, const Direction2D &dir);
    template<typename T>
    sf::Vector2<T> operator-(const sf::Vector2<T> &pos, const Direction2D &dir);
    template<typename T>
    sf::Vector2<T> &operator-=(const sf::Vector2<T> &pos, const Direction2D &dir);

    template<typename T>
    sf::Vector3<T> operator+(const sf::Vector3<T> &pos, const Direction3D &dir);
    template<typename T>
    sf::Vector3<T> operator+=(const sf::Vector3<T> &pos, const Direction3D &dir);
    template<typename T>
    sf::Vector3<T> operator-(const sf::Vector3<T> &pos, const Direction3D &dir);
    template<typename T>
    sf::Vector3<T> operator-=(const sf::Vector3<T> &pos, const Direction3D &dir);
}

#endif // __GAMEBASE_HPP__