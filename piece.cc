#include "piece.hh"

#include <stdexcept>

int charToInt(char c)
{
    if (c < '0' || c > '9')
    {
        throw std::invalid_argument(
            "Invalid char, must be between 0 and 9 to convert to int");
    }
    return c - '0';
}

Piece Piece::fromString(std::string s)
{
    // Remove invisible char
    // Somefile editors add a \r at the end of the line
    // Example: data/input/s4-02.txt
    auto invisibleCharPosition = s.find("\r");
    if (invisibleCharPosition != std::string::npos)
    {
        s.erase(invisibleCharPosition, 1);
    }

    // Normaly the string should be 4 or 6 chars long
    // But in some cases, the string is 5 chars long
    // because the space between the 4th and 5th char is missing
    // Example: data/input/s2-02.txt
    if (s.size() == 5 && s[4] == '@')
    {
        s.insert(4, 1, ' ');
    }

    if (s.size() != 4 && s.size() != 6)
    {
        std::cerr << "Invalid string length: " << s.size() << " line : `" << s
                  << "`" << std::endl;
        throw std::invalid_argument("Invalid string length");
    }

    int north = charToInt(s[0]);
    int west = charToInt(s[1]);
    int east = charToInt(s[2]);
    int south = charToInt(s[3]);

    bool isAnchored = false;

    if (s.size() == 6)
    {
        if (s[4] != ' ' && s[5] != '@')
        {
            throw "Invalid string format";
        }

        isAnchored = true;
    }

    return Piece(north, east, south, west, isAnchored);
}

std::string Piece::toString() const
{
    std::string s;
    s += std::to_string(north);
    s += std::to_string(west);
    s += std::to_string(east);
    s += std::to_string(south);
    return s;
}

/** std:cout << Piece */
std::ostream &operator<<(std::ostream &os, const Piece &p)
{
    char anchor = p.getIsAnchored() ? '@' : ' ';

    os << "+-----+\n";
    os << "|  " << p.getNorth() << "  |\n";
    os << "| " << p.getWest() << anchor << p.getEast() << " |\n";
    os << "|  " << p.getSouth() << "  |\n";
    os << "+-----+";
    return os;
}