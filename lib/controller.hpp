#pragma once
#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "common.hpp"
#include "snake.hpp"
#include "level.hpp"

namespace sg 
{
    struct ControllerInput
    {
        inline ControllerInput(const sg::Maze& maze, const sg::Snake& snake, const std::vector<sg::Position>& foodPosition)
        : m_maze(maze), m_snake(snake), m_food(foodPosition) {}
        
        const sg::Maze& m_maze;
        const sg::Snake& m_snake;
        const std::vector<sg::Position>& m_food;
    };

    class SnakeController
    {
        public:
        virtual ~SnakeController() = default;
        virtual sg::MoveDirection provide_snake_dir(const ControllerInput& state) = 0;
    };
}

#endif // CONTROLLER_HPP
