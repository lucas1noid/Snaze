#pragma once
#ifndef GAME_HPP
#define GAME_HPP

#include "snake.hpp"
#include "level.hpp"

namespace sg
{

    class Game
    {
        public:
        explicit Game(const std::vector<sg::Maze>& mazes)
        : m_currentSnake(), m_fruits(), m_currentMazeIndex(0), m_allMazes(mazes){}

        [[nodiscard]] std::vector<sg::Position> get_valid_positions() const;
        [[nodiscard]] inline const std::vector<sg::Position>& get_fruits_positions() const { return m_fruits; }

        [[nodiscard]] bool validate_position(const sg::Position& position) const;

        [[nodiscard]] inline const sg::Maze& get_current_maze() const { return m_allMazes[m_currentMazeIndex]; }

        void start();
        void update();
        bool set_maze(std::size_t mazeIndex);
        void next_maze();

        private:
        sg::Snake m_currentSnake;
        std::vector<sg::Position> m_fruits;

        std::size_t m_currentMazeIndex{0};
        std::vector<sg::Maze> m_allMazes;

        void render() const;

    }; // Class SnakeGame

} // Namespace sg

#endif // GAME_HPP