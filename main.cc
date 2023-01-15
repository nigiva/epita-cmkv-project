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

int main()
{
    Piece p = Piece::fromString("1234 @");
    std::cout << p << std::endl;

    Board b(5);
    std::cout << b.getBoardSeperator(5) << std::endl;
    b.print();
    std::cout << "-------------" << std::endl;
    std::string content = readFile("data/input/s2-02.txt");
    std::cout << content << std::endl;
    std::cout << "-------------" << std::endl;
    Board b2 = Board::fromString(content);
    b2.print();
    return 0;
}