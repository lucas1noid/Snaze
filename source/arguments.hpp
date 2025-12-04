#pragma once
#include <string>
#include <vector>

namespace sg {
    struct GameOptions {
        std::string levelPath;
        int fps = {};//n tem um padrao definido ainda
        int lives = 5;
        int food = 10;
        std::string playerType = "backtracking";
    };

class ArgumentsReader {
public:
    ArgumentsReader();

    void parse(int argc, char* argv[]);

    void printUsage() const;

private:
    GameOptions options;
};
}
