/**
 * @file Function2048.hpp
 * @author cpp-love ()
 * @brief 定义类Function2048的头文件
 * @details 定义了类Function2048以使用其来简化编写与玩家交互的代码
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
 * <tr><td>2025-05-10 <td>v0.1.1  <td>cpp-love <td>将Games::Function2048改名为Games::Function2048
 * </table>
 * ********************************************************************************
 */

#ifndef __Game_2048_HPP__
#define __Game_2048_HPP__

#include "GameBase.hpp" // 引入游戏基础头文件
#include <iostream>
#include <vector>
#include <bitset>
#include <random>

namespace Games {

    class Function2048 {
        // 2048游戏类
        public:
            // 定义分数和舞台的类型
            constexpr static size_t max_bitsize = 240; // 最大位大小
            using sco_bits = std::bitset<max_bitsize>; // 用来定义分数
            using num_bit = int; // 用来定义方块
            using mazedef = std::vector<num_bit>; // 用来定义舞台

        private:

            const size_t m_maze_size; // 舞台长宽
            mazedef m_maze; // 舞台
            static sco_bits s_max_score; // 最高分数
            sco_bits m_score; // 当前分数

            // 生成随机数
            std::mt19937 m_gen; // 随机数引擎
            std::uniform_int_distribution<> m_dis_pos; // 位置随机数
            std::bernoulli_distribution m_dis_num{0.1}; // 新方块大小随机数
            size_t m_pos_random() {return m_dis_pos(m_gen);} // 生成随机位置
            num_bit m_num_random() {return m_dis_num(m_gen) + 1;} // 生成 随机新方块大小

        public:
            constexpr static size_t min_size = 3; // 最小舞台大小
            constexpr static size_t max_size = 15; // 最大舞台大小

            // 初始化
            Function2048() = delete;
            explicit Function2048(const size_t siz)
                : m_maze_size(siz), m_maze(m_maze_size * m_maze_size, 0), m_score(0), m_gen(std::random_device()()), m_dis_pos(0, m_maze_size * m_maze_size - 1) {
                    create_new();
                    create_new();
                    if (m_maze_size < min_size || m_maze_size > max_size) {
                        throw std::out_of_range("in function Function2048::Function2048: the size is out of range!");
                    }
                }
            Function2048(const Function2048 &f)
                : m_maze_size(f.m_maze_size), m_maze(f.m_maze), m_score(f.m_score), m_gen(std::random_device()()), m_dis_pos(0, m_maze_size * m_maze_size - 1) {}
            Function2048(Function2048 &&f) = default;

            // gets
            size_t getsize() const {return m_maze_size;} // 获取舞台大小
            mazedef getmaze() const {return m_maze;} // 获取舞台
            sco_bits getscore() const {return m_score;} // 获取分数
            static sco_bits getmaxscore() {return s_max_score;} // 获取最高分数

            void move(const Direction2D dir);
            bool isdead();

        private:

            bool move_merge(size_t first_pos, size_t next_plus);
            void create_new();

            // 访问舞台
            num_bit &m_mazeat(size_t x, size_t y) {return m_maze[x * m_maze_size + y];}

    };

}

#endif // __Game_2048_HPP__