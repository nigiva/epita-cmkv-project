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
    if (argc != 3)
    {
        std::cout << "Usage: " << argv[0]
                  << " <input board filepath> <output solution filepath>"
                  << std::endl;
        return 1;
    }

    std::string inputPath = argv[1];
    std::string outputPath = argv[2];

    std::string inputBoardContent = readFile(inputPath);
    Board board = Board::fromString(inputBoardContent);
    std::cout << board << std::endl;
    return 0;
}