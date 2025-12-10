/**!
 *  This program implements the Snake simulation.
 *  @author Selan R. dos Santos
 */


#include <iostream>
#include <chrono>
#include <thread>

//#include "simulation.hpp"
//#include "arguments.hpp"
#include "common.hpp"
#include "level.hpp"
#include "tcolor.hpp"
#include "snake.hpp"
#include "input_reader.hpp"
#include "game.hpp"

int main(int argc, char* argv[]) {
  // SnazeSimulation is a singleton.
  
  //SnazeSimulation::initialize(argc, argv);
  // ArgumentsReader args;
  // args.parse(argc, argv);

  // // The Game Loop.
  // while (not SnazeSimulation::is_over()) {
  //   SnazeSimulation::process_events();
  //   SnazeSimulation::update();
  //   SnazeSimulation::render();
  // }

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

