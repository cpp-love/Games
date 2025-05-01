// Created by C++.emplace(mine) on 2025/4/12.

#ifndef __Game_2048_HPP__
#define __Game_2048_HPP__

#include "game_base.hpp" // 引入游戏基础头文件
#include <iostream>
#include <vector>
#include <bitset>
#include <random>

namespace Game {

    class Game2048 {
        // 2048游戏类

        constexpr static size_t max_bitsize = 240; // 最大位大小
        using sco_bits = std::bitset<max_bitsize>; // 用来定义分数
        using num_bit = int; // 用来定义方块
        using mazedef = std::vector<num_bit>; // 用来定义舞台

        private:

            const size_t m_mazesize; // 舞台长宽
            mazedef m_maze; // 舞台
            static sco_bits s_max_score; // 最高分数
            sco_bits m_score; // 当前分数

            // 生成随机数
            std::mt19937 m_gen; // 随机数引擎
            std::uniform_int_distribution<> m_dis_pos; // 位置随机数
            std::bernoulli_distribution m_dis_num{0.9}; // 新方块大小随机数
            size_t m_pos_random() {return m_dis_pos(m_gen);} // 生成随机位置
            num_bit m_num_random() {return m_dis_num(m_gen);} // 生成 随机新方块大小

        public:
            constexpr static size_t min_size = 3; // 最小舞台大小
            constexpr static size_t max_size = 15; // 最大舞台大小

            // 初始化
            Game2048() = delete;
            explicit Game2048(const size_t siz)
                : m_mazesize(siz), m_maze(m_mazesize * m_mazesize, 0), m_score(0), m_gen(std::random_device()()), m_dis_pos(0, m_mazesize * m_mazesize - 1) {
                    create_new();
                    create_new();
                    if (m_mazesize < min_size || m_mazesize > max_size) {
                        throw std::out_of_range("in function Game2048::Game2048: the size is out of range!");
                    }
                }
            Game2048(const Game2048 &f)
                : m_mazesize(f.m_mazesize), m_maze(f.m_maze), m_score(f.m_score), m_gen(std::random_device()()), m_dis_pos(0, m_mazesize * m_mazesize - 1) {}
            Game2048(Game2048 &&f) = default;

            void move(const Direction dir);
            bool isdead();

        private:

            bool move_merge(size_t first_pos, size_t next_plus);
            void create_new();

            // 访问舞台
            num_bit &m_mazeat(size_t x, size_t y) {return m_maze[x * m_mazesize + y];}

    };

}

#endif // __Game_2048_HPP__