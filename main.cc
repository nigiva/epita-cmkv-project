#include <fstream>
#include <iostream>
#include <string>

#include "board.hh"
#include "piece.hh"

// Read the board from the input file
// * `filepath` is the path to the input file
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

// Write the board to the output file
// * `filepath` is the path to the output file
// * `content` is the content to write in the output file
void writeFile(std::string filepath, std::string content)
{
    std::ofstream file(filepath);
    if (!file.is_open())
    {
        throw "Unable to open file";
    }

    file << content;
    file.close();
}

// Main function
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

    auto success = board.solve(10'000'000, // epochMax
                               2, // initialTemperature
                               0.9999, // coldFactor
                               0.999, // heatFactor
                               10, // stuckCounterMax
                               debug // verbose
    );

    if (debug)
    {
        std::cout << "\n---  RESULT  ---" << std::endl;
        std::cout << board << std::endl;
    }

    std::string outputBoardContent = board.toString();
    writeFile(outputPath, outputBoardContent);

    return success ? 0 : 1;
}