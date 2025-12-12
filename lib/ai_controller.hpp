#pragma once
#ifndef AI_CONTROLLER_HPP
#define AI_CONTROLLER_HPP

#include "controller.hpp"
#include <random>
#include <stack>
#include <set>

namespace sg
{
    
    class RandomMoveController : public sg::SnakeController
    {
        public:
        sg::MoveDirection provide_snake_dir(const sg::ControllerInput&) override;
        
        private:
        std::random_device m_dev;
    };

    class BacktrackingMoveController : public sg::SnakeController
    {
        public:
        sg::MoveDirection provide_snake_dir(const sg::ControllerInput&) override;
        
        private:
        bool calculate_path(sg::Snake currentSnake);
        std::set<sg::Position> m_visitedPosition{};
        std::stack<sg::MoveDirection> m_movePath{};
        const sg::Maze* m_maze;
        std::vector<sg::Position> m_foodPos{};

        std::vector<sg::MoveDirection> m_validMoves
        {
            sg::MoveDirection(0, 1), 
            sg::MoveDirection(0, -1), 
            sg::MoveDirection(1, 0), 
            sg::MoveDirection(-1, 0)
        };
    };

};


#endif // AI_CONTROLLER_HPP
