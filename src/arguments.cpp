#include "../lib/arguments.hpp"
#include <iostream>
#include <string>

namespace sg {

ArgumentsReader::ArgumentsReader(){};
    
void ArgumentsReader::parse(int argc, char* argv[], GameOptions& options){
    if(argc < 2){
        printUsage();
        exit(0);
    }
    for(int i = 1; i < argc; ++i){
        std::string arg = argv[i];
        if(arg == "--help"){
            printUsage();
            exit(0);
        } else if(arg == "--fps" && i + 1 < argc){
            options.fps = std::stoi(argv[++i]);
        } else if(arg == "--lives" && i + 1 < argc){
            options.lives = std::stoi(argv[++i]);
        } else if(arg == "--food" && i + 1 < argc){
            options.food = std::stoi(argv[++i]);
        } else if(arg == "--playertype" && i + 1 < argc){
            options.playerType = argv[++i];
        } else {
            options.levelPath = arg;
        }
    }
}

void ArgumentsReader::printUsage() const {
        std::cout << "Usage: snaze [<options>] <input_level_file>\n"
                  << "  Game simulation options:\n"
                  << "    --help               Print this help text.\n"
                  << "    --fps <num>          Number of frames (board) presented per second.\n"
                  << "    --lives <num>        Number of lives the snake shall have. Default = 5.\n"
                  << "    --food <num>         Number of food pellets for the entire simulation. Default = 10.\n"
                  << "    --playertype <type>  Type of snake intelligence: random, backtracking. Default = backtracking\n";
    }
}