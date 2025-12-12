#include "../lib/ai_controller.hpp"

#include <vector>

sg::MoveDirection sg::RandomMoveController::provide_snake_dir(const sg::ControllerInput& ctx)
{
    std::vector<sg::MoveDirection> candidates;

    
    std::vector<sg::MoveDirection> validMoves
    {
        sg::MoveDirection(0, 1), 
        sg::MoveDirection(0, -1), 
        sg::MoveDirection(1, 0), 
        sg::MoveDirection(-1, 0)
    };
    
    for (sg::MoveDirection& dir : validMoves)
    {
        if ((dir + ctx.m_snake.move_direction()).equals(0, 0))
        {
            continue;
        }

        sg::Position newPos = ctx.m_snake.head_position() + dir;
        if (ctx.m_maze.validate_position(newPos) && ctx.m_snake.validate_position(newPos))
        {
            candidates.push_back(dir);
        }
    }

    if (candidates.size() <= 0)
    {
        return ctx.m_snake.move_direction();
    }

    std::mt19937 rng(m_dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0, candidates.size());

    int index = dist(rng)%candidates.size();
    return candidates[index];
}






sg::MoveDirection sg::BacktrackingMoveController::provide_snake_dir(const sg::ControllerInput& ctx)
{
    if (!m_movePath.empty())
    {
        sg::MoveDirection result = m_movePath.top();
        m_movePath.pop();
        return result;
    }

    m_foodPos = ctx.m_food;
    m_maze = &ctx.m_maze;
    m_visitedPosition.clear();

    if (calculate_path(ctx.m_snake))
    {
        if (!m_movePath.empty())
        {
            sg::MoveDirection result = m_movePath.top();
            m_movePath.pop();
            return result;
        }
    }

    return ctx.m_snake.move_direction();
}

bool sg::BacktrackingMoveController::calculate_path(sg::Snake currentSnake)
{
    for (sg::Position& f : m_foodPos)
    {
        if (currentSnake.head_position() == f)
        { 
            return true;
        }
    }

    const sg::Position& head = currentSnake.head_position();
    m_visitedPosition.insert(head);
    
    for (sg::MoveDirection& dir : m_validMoves)
    {
        if ((dir + currentSnake.move_direction()).equals(0, 0))
        {
            continue;
        }

        sg::Position potentialNextHead = head + dir;
        if (m_visitedPosition.count(potentialNextHead) > 0)
        {
            continue;
        }

        sg::Snake simulatedSnake = currentSnake; 

        simulatedSnake.set_move_direction(dir);
        simulatedSnake.update_position_by_move_direction();

        if (simulatedSnake.head_collided(*m_maze))
        {
            continue;
        }

        if (calculate_path(simulatedSnake))
        {
            m_movePath.push(dir);
            return true;
        }
    }

    return false;
}