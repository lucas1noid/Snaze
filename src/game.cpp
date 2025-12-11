#include "../lib/game.hpp"
#include "../lib/tcolor.hpp"
#include "../lib/input_reader.hpp"

#include <iostream>
#include <chrono>
#include <thread>
#include <cstdlib>

sg::Game::Game(const std::vector<sg::Maze>& mazes, const GameOptions& options)
: m_allMazes(mazes),
  m_currentMazeIndex(0),
  m_lives(options.lives),
  m_totalFoodToEat(options.food),
  m_fruitsEaten(0)
{
    //transforma fps em tempo de frame
    int fps = (options.fps > 0) ? options.fps : 1;
    m_frameDuration = std::chrono::milliseconds(1000 / fps);
    
}

std::vector<sg::Position> sg::Game::get_valid_positions() const
{
    std::vector<sg::Position> result;

    if (m_currentMazeIndex > m_allMazes.size())
    {
        return result;
    }

    for (unsigned short y{0}; y < get_current_maze().get_y_size(); ++y)
    {
        for (unsigned short x{0}; x < get_current_maze().get_x_size(); ++x)
        {
            Position currentPosition(y, x);

            if (!validate_position(currentPosition))
            {
                continue;
            }

            result.push_back(currentPosition);
        }
    }

    return result;
}

bool sg::Game::validate_position(const sg::Position& position) const
{
    if (!get_current_maze().validate_position(position))
    {
        return false;
    }

    if (!m_currentSnake.validate_position(position))
    {
        return false;
    }

    for (const sg::Position& f : m_fruits)
    {
        if (f == position)
        {
            return false;
        }
    }

    return true;
}

bool sg::Game::set_maze(std::size_t index)
{
    if (index >= m_allMazes.size())
    {
        return false;
    }
    
    m_currentMazeIndex = index;
    return true;
}

void sg::Game::next_maze()
{
    set_maze(m_currentMazeIndex + 1);
}

void sg::Game::welcome_screen()
{
    bool validChoice = false;
    char choice;

    while (!validChoice)
    {
        std::cout << "\033[2J\033[1;1H";

        std::cout << TColor::colorize("--------------------------------------------------\n", TColor::BLUE, TColor::BOLD);
        std::cout << TColor::colorize("|              S N A Z E   G A M E               |\n", TColor::BLUE, TColor::BOLD);
        std::cout << TColor::colorize("--------------------------------------------------\n\n", TColor::BLUE, TColor::BOLD);

        std::cout << "   Escolha o modo de jogo:\n\n";

        std::cout << "   [" << TColor::colorize("1", TColor::YELLOW, TColor::BOLD) << "] - " 
                  << TColor::colorize("Jogador", TColor::GREEN) << "\n";
        std::cout << "       Controle a cobra com W, A, S, D.\n\n";

        std::cout << "   [" << TColor::colorize("2", TColor::YELLOW, TColor::BOLD) << "] - " 
                  << TColor::colorize("IA", TColor::MAGENTA) << "\n";
        std::cout << "       Assista a IA jogar sozinha, tentando ganhar! ou lutando para sobreviver...\n\n";

        std::cout << "   Digite sua opcao: ";

        std::cin >> choice;

        if (choice == '1')
        {
            m_playerType = PlayerType::HUMAN;
            validChoice = true;
        }
        else if (choice == '2')
        {
            m_playerType = PlayerType::AI;
            validChoice = true;
        }
        else
        {
            std::cout << TColor::colorize("\n   Opcao invalida! Tente novamente.\n", TColor::RED);
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            
            std::cin.ignore(1000, '\n');
            std::cin.clear();
        }
    }

    //feedback antes de comecar
    std::cout << "\n   Iniciando jogo no modo: " 
              << (m_playerType == PlayerType::HUMAN ? "HUMANO" : "IA") 
              << "...\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

void sg::Game::start()
{
    if (m_allMazes.size() <= 0)
    {
        return;
    }

    welcome_screen();

    set_maze(0);
    m_currentSnake = sg::Snake();
    m_currentSnake.head_position(get_current_maze().get_start_position());

    std::vector<sg::Position> validPos = get_valid_positions();

    sg::Position fruitPos = validPos[std::rand()%validPos.size()];
    m_fruits.push_back(fruitPos);

    update(); 
}

void sg::Game::update()
{
    sg::KeyboardController keyboard;

    while (1)
    {
        render();
        
        char key = keyboard.readKey();
        if (key != 0) 
        {
            if (key == 'w') m_currentSnake.move_direction(-1, 0);
            if (key == 's') m_currentSnake.move_direction(1, 0);
            if (key == 'a') m_currentSnake.move_direction(0, -1);
            if (key == 'd') m_currentSnake.move_direction(0, 1);
            if (key == '1') m_currentSnake.add_body();
            if (key == 't') m_currentSnake.move_direction(0, 0);

            if (key == 'q') break; // Sair do jogo
        }

        m_currentSnake.update_position_by_move_direction();

        if (m_currentSnake.is_dead(get_current_maze()))
        {
            
            std::cout << "Tu morreu lixo!\n";
            break;
        }

        for (std::size_t fIndex{0}; fIndex < m_fruits.size(); ++fIndex)
        {
            if (m_fruits[fIndex] == m_currentSnake.head_position())
            {
                m_currentSnake.add_body();
                m_fruitsEaten++;
                m_fruits.erase(m_fruits.begin() + fIndex);

                std::vector<sg::Position> pos = get_valid_positions();
                m_fruits.push_back(pos[std::rand()%pos.size()]);
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(170));
    }

}

void sg::Game::render() const
{
    if (m_currentMazeIndex >= m_allMazes.size())
    {
        return;
    }

    std::cout << "\033[2J\033[1;1H";

    for (size_t y{0}; y < get_current_maze().get_y_size(); ++y)
    {
        for (size_t x{0}; x < get_current_maze().get_x_size(); ++x)
        {
            Position currentPos = Position(y, x);
            bool charPrinted = false;
            for (const sg::Position& fruit : m_fruits)
            {
                if (fruit == currentPos)
                {
                    std::cout << TColor::colorize('@', TColor::RED, TColor::BOLD);
                    charPrinted = true;
                    break;
                }
            }

            if (charPrinted)
            {
                continue;
            }

            for (const sg::Position& snakeBody : m_currentSnake.snake_body())
            {
                if (snakeBody == currentPos)
                {
                    std::cout << TColor::colorize('O', TColor::GREEN, TColor::BOLD);
                    charPrinted = true;
                    break;
                }
            }

            if (charPrinted)
            {
                continue;
            }

            if (m_currentSnake.head_position() == currentPos)
            {
                std::cout << TColor::colorize(m_currentSnake.get_head_char(), TColor::GREEN, TColor::BOLD);
                continue;
            }

            std::cout << get_current_maze().position_char(currentPos);
        }

        std::cout << '\n';
    }

    std::cout << "--------------------------------------------------\n";
    std::cout << " Lives: " << std::to_string(m_lives)
              << " | Fruits Eaten: " << m_fruitsEaten << "/" << m_totalFoodToEat
              << " | Snake Size: " << m_currentSnake.snake_body().size() << '\n';
    std::cout << "Move direction: [" << m_currentSnake.move_direction() << "]\n";
    std::cout << "Head position: [" << m_currentSnake.head_position() << "]\n";
}