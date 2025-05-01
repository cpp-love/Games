// Created by C++.emplace(mine) on 2025/4/12.

#include "Game2048/Game2048.hpp"
#include <iostream>
#include <cmath>
#include <vector>
#include <bitset>
#include <random>
#include <functional>

namespace Game {

    void Game2048::move (const Direction dir) {
        // 移动
        
        bool ishange = false; // 用来判断是否需要新建方块
        for (size_t i = 0; i < Game2048::m_mazesize; ++i) {
            switch (dir) {
                case Direction::UP: // 上
                    ishange |= move_merge(Game2048::m_mazesize * (Game2048::m_mazesize - 1) + i, -Game2048::m_mazesize); // 上
                    break;

                case Direction::LEFT: // 左
                    ishange |= move_merge(Game2048::m_mazesize * i, 1); // 左
                    break;

                case Direction::DOWN: // 下
                    ishange |= move_merge(i, Game2048::m_mazesize); // 下
                    break;

                case Direction::RIGHT: // 右
                    ishange |= move_merge(Game2048::m_mazesize * (i + 1) - 1, -1); // 右
                    break;
            }
        }
        
        if (ishange) {
            create_new(); // 新建方块
        }

        Game2048::s_max_score = std::max(Game2048::s_max_score, m_score); // 处理分数超过最高分数
    }

    bool Game2048::isdead() {
        // 是否无法移动

        for (size_t i = 0; i < Game2048::m_mazesize; ++i) {
            for (size_t j = 0; j < Game2048::m_mazesize; ++j) {
                // 可以移动
                if (0 == m_mazeat(i, j)) return false;

                // 可以合成
                if ((i + 1 < Game2048::m_mazesize && m_mazeat(i, j) == m_mazeat(i + 1, j)) ||
                    (j + 1 < Game2048::m_mazesize && m_mazeat(i, j) == m_mazeat(i, j + 1))) {
                    return false;
                }
            }
        }
        return true; // 无法移动
    }

    bool Game2048::move_merge(size_t first_pos, size_t next_plus) {
        // 移动合成并返回是否改变

        // 函数内访问舞台
        std::function<num_bit&(size_t)> m_mazeat_infunc = [&m_maze = this->m_maze, &first_pos, &next_plus](size_t pos) -> num_bit& {
            return m_maze[first_pos + pos * next_plus];
        };

        bool ischange = false; // 用来检查是否改变
        size_t write_pos = 0; // 用来写入的位置
        size_t read_pos = 1; // 用来读取的位置
        size_t compare_pos = 0; // 用来比较的位置
        while (true) {
            if (read_pos > Game2048::m_mazesize) break; // 读写完毕
            if (read_pos == Game2048::m_mazesize) {// 读写最后一个并退出
                m_mazeat_infunc(write_pos) = m_mazeat_infunc(compare_pos);
                ++write_pos; // 更新写入位置
                break;
            }
            if (0 == m_mazeat_infunc(read_pos)) { // 读到空格
                ++read_pos; // 更新读取位置
                continue;
            }
            if (m_mazeat_infunc(read_pos) == m_mazeat_infunc(compare_pos)) { // 读到相同的方块
                ischange = true;
                m_mazeat_infunc(write_pos) = m_mazeat_infunc(read_pos) + 1; // 合成
                // 加分
                if (m_score[m_mazeat_infunc(write_pos)]) {
                    m_score.reset(m_mazeat_infunc(write_pos));
                    m_score.set(m_mazeat_infunc(write_pos) + 1);
                } else {
                    m_score.set(m_mazeat_infunc(write_pos));
                }
                // 更新最大分数
                for (size_t i = max_bitsize; true; --i) {
                    if (m_score[i] > s_max_score[i]) {
                        s_max_score = m_score;
                        break;
                    }
                    if (0 == m_score[i]) {
                        break;
                    }
                }
                ++write_pos; // 更新写入位置
                compare_pos = read_pos + 1; // 更新比较位置
                read_pos += 2; // 更新读取位置
                continue;
            }
            // 读到不同的方块
            ischange = true;
            m_mazeat_infunc(write_pos) = m_mazeat_infunc(compare_pos); // 移动
            ++write_pos; // 更新写入位置
            compare_pos = read_pos; // 更新比较位置
            ++read_pos; // 更新读取位置
        }

        while (write_pos < Game2048::m_mazesize) { // 清空后面的方块
            m_mazeat_infunc(write_pos) = 0;
            ++write_pos;
        }

        return ischange;
    }

    void Game2048::create_new() {
        // 新建方块

        size_t x = m_pos_random(); // 用来确定位置
        while (0 == m_maze[x]) {
            x = m_pos_random();
        }

        m_maze[x] = m_num_random(); // 生成方块
    }

}