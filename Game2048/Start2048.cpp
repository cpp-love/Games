/**
 * @file Start2048.cpp
 * @author cpp-love ()
 * @brief 实现玩家游玩2048游戏
 * @details 通过SFML第三方库来实现与玩家进行交互，包括获取键盘输入，显示方块及分数等
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

/**@mainpage
 * <table>
 * <tr><th>Project     <td>2048 Game
 * <tr><th>Author      <td>cpp-love
 * </table>
 * 
 * @section    项目详细描述
 * -# 实现2048游戏核心逻辑(在类Games::Function2048中)
 * -# 实现与玩家交互来游玩2048游戏
 * 
 * @todo {
 *   -渲染方块的移动合成动画
 *   -渲染分数的变化动画
 *   -渲染游戏开始、结束的动画
 *   -存储游戏记录及最高分
 *   -加入音频
 *   -Games::Function2048::isdead()方法优化
 *   -Games::Function2048::move()方法优化
 *   -Games::Function2048::create_new()方法优化
 *   -全范围doxygen注释
 *   -选择网格大小
 *   -游戏结束后重新开始
 * }
 * 
 * @bug
 * -# 
 * -# 
 * 
 * @warning {
 *     
 * }
 * @section    注意事项
 * -# 编译需要配置SFML库
 * -# 编译后运行需要将SFML的.dll文件复制到.exe文件的同级目录里
 * 
 * ********************************************************************************
 * @section    版本历史
 * <table>
 * <tr><td>Date        <th>Version <td>Author    <td>Description
 * <tr><td>2025-05-10  <th>v0.1    <td>cpp-love  <td>
 * -# 创建初始项目
 *    (GameBase.hpp                +
 *     GameBase.cpp                +
 *     Game2048/Function2048.hpp   +
 *     Game2048/Function2048.cpp   +
 *     Game2048/Start2048.cpp)
 * 
 * </table>
 * ********************************************************************************
*/

#include "Game2048/Function/Function2048.hpp"
#include <SFML/Graphics.hpp> ///< 引入SFML图形库
#include <SFML/Window.hpp>   ///< 引入SFML窗口库
#include <SFML/System.hpp>   ///< 引入SFML系统库
#include <iostream>

constexpr size_t maze_size = 4; ///< 定义2048游戏的网格大小
constexpr float tile_size = 100.f; ///< 定义2048游戏的方块大小
constexpr float tile_offset = 10.f; ///< 定义2048游戏的方块间隔
constexpr sf::Vector2f start_pos = {100, 100}; ///< 定义2048游戏的起始位置

using Texts = std::vector<std::vector<sf::Text>>; ///< 定义文本类型
using Tiles = std::vector<std::vector<sf::RectangleShape>>; ///< 定义方块类型

sf::Color getColor(Games::Function2048::num_bit value) {
    while (value > 11) {
        value -= 11;
    }
    switch(value) {
        case 1:    return sf::Color(238, 228, 218);
        case 2:    return sf::Color(237, 224, 200);
        case 3:    return sf::Color(242, 177, 121);
        case 4:   return sf::Color(245, 149, 99);
        case 5:   return sf::Color(246, 124, 95);
        case 6:   return sf::Color(246, 94, 59);
        case 7:  return sf::Color(237, 207, 114);
        case 8:  return sf::Color(237, 204, 97);
        case 9:  return sf::Color(237, 200, 80);
        case 10: return sf::Color(237, 197, 63);
        case 11: return sf::Color(237, 194, 46);
        default:   return sf::Color(205, 193, 180);
    }
}

void init_2048(Texts &texts, Tiles &tiles, sf::Text &score, sf::Text &max_score) {
    for (size_t i = 0; i < maze_size; ++i) {
        for (size_t j = 0; j < maze_size; ++j) {
            const sf::Vector2f tile_pos = {start_pos.x + j * (tile_size + tile_offset), start_pos.x + i * (tile_size + tile_offset)};
            texts[i][j].setString("");
            texts[i][j].setCharacterSize(36); ///< 设置字体大小
            texts[i][j].setPosition(tile_pos + sf::Vector2f{tile_size / 2, tile_size / 2}); ///< 设置文本位置
            tiles[i][j].setSize({tile_size, tile_size}); ///< 设置方块大小
            tiles[i][j].setPosition(tile_pos); ///< 设置方块位置
        }
    }
    score.setString(L"分数: 0"); ///< 设置分数文本
    score.setCharacterSize(24); ///< 设置分数字体大小
    score.setPosition({start_pos.x, start_pos.y - 50}); ///< 设置分数文本位置
    max_score.setString(L"最高分数: 0"); ///< 设置最高分数文本
    max_score.setCharacterSize(24); ///< 设置最高分数字体大小
    max_score.setPosition({start_pos.x + 200, start_pos.y - 50}); ///< 设置最高分数文本位置
}

void update_2048(Texts &texts, Tiles &tiles, const Games::Function2048 &game_2048, sf::Text &score, sf::Text &max_score) {
    const auto maze = game_2048.getmaze();
    for (size_t i = 0; i < maze_size; ++i) {
        for (size_t j = 0; j < maze_size; ++j) {
            ///< 更新文本内容
            if (maze[i * maze_size + j] == 0) {
                texts[i][j].setString("");
            } else {
                texts[i][j].setString(std::to_string(static_cast<int>(std::pow(2, maze[i * maze_size + j]))));
            }
            sf::FloatRect text_bounds = texts[i][j].getLocalBounds();
            texts[i][j].setOrigin({text_bounds.position.x + text_bounds.size.x / 2, text_bounds.position.y + text_bounds.size.y / 2}); ///< 设置文本原点为中心
            tiles[i][j].setFillColor(getColor(maze[i * maze_size + j])); ///< 更新方块颜色
        }
    }
    score.setString(L"分数: " + std::to_wstring(game_2048.getscore().to_ullong())); ///< 更新分数文本
    max_score.setString(L"最高分数: " + std::to_wstring(Games::Function2048::getmaxscore().to_ullong())); ///< 更新最高分数文本
}

// void printmaze(const Games::Function2048 &game_2048) {
//     const auto maze = game_2048.getmaze();
//     for (size_t i = 0; i < maze.size(); ++i) {
//         std::cout << maze[i] << " ";
//         if ((i + 1) % (maze.size() / maze_size) == 0) {
//             std::cout << std::endl;
//         }
//     }
// }

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "2048 Games"); ///< 创建窗口
    window.setFramerateLimit(60); ///< 设置帧率限制

    sf::Font font;
    ///< 加载字体文件（确保路径正确！）
    if (!font.openFromFile(Games::FontPath::Chinese)) {
        ///< 加载失败处理
        std::cerr << "in main : cannot open the file : " << Games::FontPath::Chinese << "!"<< std::endl;
        return -1;
    }

    sf::Text score(font), max_score(font); ///< 创建分数和最高分数文本
    Texts texts(maze_size, std::vector<sf::Text>(maze_size, sf::Text(font)));
    Tiles tiles(maze_size, std::vector<sf::RectangleShape>(maze_size));
    init_2048(texts, tiles, score, max_score); ///< 初始化2048游戏的文本和方块

    Games::Function2048 game_2048(4);
    update_2048(texts, tiles, game_2048, score, max_score); ///< 更新2048游戏的文本和方块

    while (window.isOpen()) {
        while (const std::optional<sf::Event> event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            } else if (const sf::Event::KeyPressed* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                switch (keyPressed->scancode) {
                    case sf::Keyboard::Scancode::Up:
                    case sf::Keyboard::Scancode::W:
                        game_2048.move(Games::Direction2D::UP); ///< 上移
                        break;
                    case sf::Keyboard::Scancode::Down:
                    case sf::Keyboard::Scancode::S:
                        game_2048.move(Games::Direction2D::DOWN); ///< 下移
                        break;
                    case sf::Keyboard::Scancode::Left:
                    case sf::Keyboard::Scancode::A:
                        game_2048.move(Games::Direction2D::LEFT); ///< 左移
                        break;
                    case sf::Keyboard::Scancode::Right:
                    case sf::Keyboard::Scancode::D:
                        game_2048.move(Games::Direction2D::RIGHT); ///< 右移
                        break;
                    default:
                        break;
                }
                if (game_2048.isdead()) {
                    std::cout << "Game Over!" << std::endl; ///< 游戏结束提示
                    window.close();
                } else {
                    update_2048(texts, tiles, game_2048, score, max_score); ///< 更新文本和方块
                }
            }
        }

        window.clear(sf::Color(187, 173, 160)); ///< 清空窗口
        for (const auto& tile : tiles) {
            for (const auto& t : tile) {
                window.draw(t); ///< 绘制方块
            }
        }
        for (const auto& text : texts) {
            for (const auto& t : text) {
                window.draw(t); ///< 绘制文本
            }
        }
        window.draw(score); ///< 绘制分数文本
        window.draw(max_score); ///< 绘制最高分数文本
        window.display(); ///< 显示窗口内容
    }
    return 0;
}