#include "piece.hh"


Piece Piece::from_string(std::string s)
{
    if (s.size() != 4 || s.size() != 6)
    {
        throw "Invalid string length";
    }

    int north = s[0] - '0';
    int east = s[1] - '0';
    int south = s[2] - '0';
    int west = s[3] - '0';
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
    os << "+-----+\n";
    os << "|  " << p.getNorth() << "  |\n";
    os << "| " << p.getWest() << " " << p.getEast() << " |\n";
    os << "|  " << p.getSouth() << "  |\n";
    os << "+-----+";
    return os;
}