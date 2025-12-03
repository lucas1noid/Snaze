#pragma once
#include <string>

namespace sg {
    struct GameOptions {
        std::string levelPath;
        int fps = {};//n tem um padrao definido ainda
        int lives = 5;
        int food = 10;
        std::string playerType = "backtracking";
    };

    class ArgumentParser {
    public:
        static GameOptions parse(int argc, char* argv[]);
    };
}
