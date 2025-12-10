#include "../lib/snake.hpp"

void sg::Snake::head_position(unsigned short y, unsigned short x)
{
    m_headPosition.m_y = y;
    m_headPosition.m_x = x;
}

void sg::Snake::head_position(const sg::Position& newPosition)
{
    head_position(newPosition.m_y, newPosition.m_x);
}

void sg::Snake::move_direction(short y, short x)
{
    m_headMoveDirection.m_y = y;
    m_headMoveDirection.m_x = x;
}

void sg::Snake::move_direction(const sg::MoveDirection& newMoveDir)
{
    move_direction(newMoveDir.m_y, newMoveDir.m_x);
}

void sg::Snake::update_position_by_move_direction()
{
    if (m_headMoveDirection.equals(0, 0))
    {
        return;
    }

    if (m_creatingBodyFlag) 
    {
        m_snakeBody.insert(m_snakeBody.cbegin(), m_headPosition);
        m_creatingBodyFlag=false;
    }
    else
    {
        std::size_t bodySize = m_snakeBody.size();
        if (bodySize > 0)
        {
            for (std::size_t part{bodySize-1}; part > 0; --part)
            {
                m_snakeBody[part] = m_snakeBody[part-1]; 
            }
            m_snakeBody[0] = m_headPosition;
        }
    }
    

    m_headPosition.m_y += m_headMoveDirection.m_y;
    m_headPosition.m_x += m_headMoveDirection.m_x;
}

void sg::Snake::add_body()
{
    m_creatingBodyFlag = true;
}

char sg::Snake::get_head_char() const
{
    short x = m_headMoveDirection.m_x;
    short y = m_headMoveDirection.m_y;

    if (y == 0)
    {
        return x >= 0 ? '>' : '<'; 
    }

    return y >= 0 ? 'v' : '^';
}

bool sg::Snake::validate_position(const sg::Position& pos) const
{
    if (m_headPosition == pos)
    {
        return false;
    }

    for (const sg::Position& bodyPart : m_snakeBody)
    {
        if (bodyPart == pos)
        {
            return false;
        }
    }

    return true;
}

bool sg::Snake::is_dead(const sg::Maze& maze) const
{
    for (const sg::Position& body : m_snakeBody)
    {
        if (m_headPosition == body)
        {
            return true;
        }
    }

    if (!maze.validate_position(m_headPosition))
    {
        return true;
    }

    return false;
}