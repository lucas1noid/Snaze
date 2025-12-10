/**!
 *  This program implements the Snake simulation.
 *  @author Selan R. dos Santos feat. noid e migs
 */


#include <iostream>
#include <chrono>
#include <thread>

//#include "simulation.hpp"
//#include "arguments.hpp"
#include "../lib/common.hpp"
#include "../lib/level.hpp"
#include "../lib/tcolor.hpp"
#include "../lib/snake.hpp"
#include "../lib/input_reader.hpp"
#include "../lib/game.hpp"

int main(int argc, char* argv[]) {

  if (argc != 2)
  {
    std::cout << "invalid arguments\n";
    return 1;
  }

  std::string arg(argv[1]);
  std::vector<sg::Maze> teste = sg::parse_maze_input_file(arg);

  if (teste.size() <= 0)
  {
    std::cout << "Any maze loaded! Exiting...";
    return 1;
  }

  sg::Game game(teste);
  game.start();

  return 0;
}

