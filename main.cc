#include <fstream>
#include <iostream>
#include <string>

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
    Piece p = Piece::from_string("1234 @");
    std::cout << p << std::endl;
    return 0;
}