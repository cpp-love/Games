/**
 * @file Function2048.cpp
 * @author cpp-love ()
 * @brief 类Function2048成员方法的实现
 * @details 实现了类Function2048的成员方法即2048核心逻辑
 * @version 0.1.1
 * @date 2025-05-10
 * 
 * @copyright Copyright 2025 cpp-love
 * 
 * ********************************************************************************
 * @par 修改日志:
 * <table>
 * <tr><th>Date       <th>Version <th>Author   <th>Description
 * <tr><td>2025-05-01 <td>v0.1    <td>cpp-love <td>创建此文件
 * <tr><td>2025-05-10 <td>v0.1.1  <td>cpp-love <td>
 * -# 将Games::Function2048改名为Games::Function2048
 * -# 修复了Games::Function2048::create_new()的bug
 * -# 修复了Games::Function2048::move()的bug
 * </table>
 * ********************************************************************************
 */

#include "Game2048/Function/Function2048.hpp"
#include <iostream>
#include <cmath>
#include <vector>
#include <bitset>
#include <random>
#include <functional>

namespace Games {

    void Function2048::move(const Direction2D dir) {
        // 移动
        
        bool ishange = false; // 用来判断是否需要新建方块
        for (size_t i = 0; i < m_maze_size; ++i) {
            switch (dir) {
                case Direction2D::UP: // 上
                    ishange |= move_merge(i, m_maze_size); // 上
                    break;

                case Direction2D::LEFT: // 左
                    ishange |= move_merge(m_maze_size * i, 1); // 左
                    break;

                case Direction2D::DOWN: // 下
                    ishange |= move_merge(m_maze_size * (m_maze_size - 1) + i, -m_maze_size); // 下
                    break;

                case Direction2D::RIGHT: // 右
                    ishange |= move_merge(m_maze_size * (i + 1) - 1, -1); // 右
                    break;
            }
        }
        
        if (ishange) {
            create_new(); // 新建方块
        }

        // 更新最高分数
        for (size_t i = max_bitsize; true; --i) {
            if (m_score[i] > s_max_score[i]) {
                s_max_score = m_score;
                break;
            }
            if (0 == i) break;
        }
    }

    bool Function2048::isdead() {
        // 是否无法移动

        for (size_t i = 0; i < m_maze_size; ++i) {
            for (size_t j = 0; j < m_maze_size; ++j) {
                // 可以移动
                if (0 == m_mazeat(i, j)) return false;

                // 可以合成
                if ((i + 1 < m_maze_size && m_mazeat(i, j) == m_mazeat(i + 1, j)) ||
                    (j + 1 < m_maze_size && m_mazeat(i, j) == m_mazeat(i, j + 1))) {
                    return false;
                }
            }
        }
        return true; // 无法移动
    }

    bool Function2048::move_merge(size_t first_pos, size_t offset) {
        // 移动合成并返回是否改变

        // 函数内访问舞台
        auto m_mazeat_infunc = [&m_maze = this->m_maze, &first_pos, &offset](size_t pos) -> num_bit& {
            return m_maze[first_pos + pos * offset];
        };

        bool ischange = false; // 用来检查是否改变
        size_t write_pos = 0; // 用来写入的位置
        size_t read_pos = 1; // 用来读取的位置
        size_t compare_pos = 0; // 用来比较的位置
        while (true) {
            if (read_pos > m_maze_size) break; // 读写完毕
            if (read_pos == m_maze_size) {// 读写最后一个并退出
                if (0 != m_mazeat_infunc(compare_pos)) {
                    if (write_pos != compare_pos) {
                        ischange = true;
                        m_mazeat_infunc(write_pos) = m_mazeat_infunc(compare_pos); // 移动
                    }
                    ++write_pos; // 更新写入位置
                }
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
                for (size_t i = m_mazeat_infunc(read_pos); true; ++i) {
                    if (!m_score[i]) {
                        m_score.set(i);
                        break;
                    }
                    m_score.reset(i);
                }

                ++write_pos; // 更新写入位置
                compare_pos = read_pos + 1; // 更新比较位置
                read_pos += 2; // 更新读取位置
                continue;
            }
            // 读到不同的方块
            if (0 != m_mazeat_infunc(compare_pos)) {
                if (write_pos != compare_pos) {
                    ischange = true;
                    m_mazeat_infunc(write_pos) = m_mazeat_infunc(compare_pos); // 移动
                }
                ++write_pos; // 更新写入位置
            }
            compare_pos = read_pos; // 更新比较位置
            ++read_pos; // 更新读取位置
        }

        while (write_pos < m_maze_size) { // 清空后面的方块
            m_mazeat_infunc(write_pos) = 0;
            ++write_pos;
        }
        return ischange;
    }

    void Function2048::create_new() {
        // 新建方块

        size_t x = m_pos_random(); // 用来确定位置
        while (0 != m_maze[x]) {
            x = m_pos_random();
        }

        m_maze[x] = m_num_random(); // 生成方块
    }

    Function2048::sco_bits Function2048::s_max_score = 0; // 初始化最高分数

}