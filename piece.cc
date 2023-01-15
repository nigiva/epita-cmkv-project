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

Piece Piece::from_string(std::string s)
{
    if (s.size() != 4 && s.size() != 6)
    {
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