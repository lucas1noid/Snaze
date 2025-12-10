#pragma once
#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <vector> // vector to hold th snake body
#include "common.hpp" // Position and move direction
#include "level.hpp"

/// @brief sg (Snake Game) is the default project namespace.
namespace sg 
{

    class Snake
    {
        public:
        inline const sg::Position& head_position() const { return m_headPosition; }
        
        [[nodiscard]]
        inline const std::vector<sg::Position>& snake_body() const { return m_snakeBody; }

        void add_body();

        void head_position(unsigned short y, unsigned short x);
        void head_position(const sg::Position& newPosition);

        [[nodiscard]]
        inline const sg::MoveDirection& move_direction() const { return m_headMoveDirection; }

        void move_direction(short y = 0, short x = 0);
        void move_direction(const sg::MoveDirection& newMoveDirection);

        void update_position_by_move_direction();

        [[nodiscard]] char get_head_char() const;

        [[nodiscard]] bool validate_position(const sg::Position& pos) const;

        bool is_dead(const sg::Maze& maze) const;

        private:
        bool m_creatingBodyFlag = false;
        sg::Position m_headPosition;
        sg::MoveDirection m_headMoveDirection;
        std::vector<sg::Position> m_snakeBody;

    }; // Class Snake

} // Namespace sg

#endif // SNAKE_HPP