#include <fstream>
#include <iostream>
#include <string>

#include "board.hh"
#include "piece.hh"

std::string readFile(std::string filepath)
{
    std::string content;
    std::ifstream file(filepath);
    if (!file.is_open())
    {
        throw "Unable to open file";
    }

    std::string line;
    while (std::getline(file, line))
    {
        content += line + '\n';
    }
    file.close();
    return content;
}

int main(int argc, char **argv)
{
    bool defaultArgsCondition = (argc == 3);
    bool debugArgsCondition = (argc == 4 && std::string(argv[3]) == "--debug");
    bool debug = debugArgsCondition;
    if (!defaultArgsCondition && !debugArgsCondition)
    {
        std::cout
            << "Usage: " << argv[0]
            << " <input board filepath> <output solution filepath> (--debug)"
            << std::endl;
        return 1;
    }

    std::string inputPath = argv[1];
    std::string outputPath = argv[2];

    std::string inputBoardContent = readFile(inputPath);
    Board board = Board::fromString(inputBoardContent);
    if (debug)
    {
        std::cout << board << std::endl;
    }

    auto success = board.solve(4'000'000, // epochMax
                               2, // initialTemperature
                               0.9999, // decayRate
                               debug // verbose
    );
    if (debug)
    {
        std::cout << "\n---  RESULT  ---" << std::endl;
        std::cout << board << std::endl;
    }

    if (!success)
    {
        std::cerr << "Unable to solve the board (loss=" << board.loss() << ")"
                  << std::endl;
        return 1;
    }
    return 0;
}