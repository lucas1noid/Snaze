/**!
 *  This program implements the Snake simulation.
 *  @author Selan R. dos Santos
 */

#include "common.hpp"
#include "simulation.hpp"
#include "arguments.hpp"
using namespace sg;

int main(int argc, char* argv[]) {
  // SnazeSimulation is a singleton.
  
  //SnazeSimulation::initialize(argc, argv);
  ArgumentsReader args;
  args.parse(argc, argv);

  // The Game Loop.
  while (not SnazeSimulation::is_over()) {
    SnazeSimulation::process_events();
    SnazeSimulation::update();
    SnazeSimulation::render();
  }
  return 0;
}

