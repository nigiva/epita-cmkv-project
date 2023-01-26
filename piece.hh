#pragma once
#include <iostream>
#include <string>

// A piece of the puzzle
class Piece
{
private:
    int north;
    int east;
    int south;
    int west;
    bool isAnchored;

public:
    // Constructor
    // * `north` is the number stored on the north side of the piece
    // * `east` is the number stored on the east side of the piece
    // * `south` is the number stored on the south side of the piece
    // * `west` is the number stored on the west side of the piece
    // * `isAnchored` is true if the piece is anchored and cannot be moved
    Piece(int north, int east, int south, int west, bool isAnchored)
        : north(north)
        , east(east)
        , south(south)
        , west(west)
        , isAnchored(isAnchored)
    {}

    // Getter of the north side of the piece
    int getNorth() const
    {
        return this->north;
    }

    // Getter of the east side of the piece
    int getEast() const
    {
        return this->east;
    }

    // Getter of the south side of the piece
    int getSouth() const
    {
        return this->south;
    }

    // Getter of the west side of the piece
    int getWest() const
    {
        return this->west;
    }

    // Getter of the isAnchored attribute
    bool getIsAnchored() const
    {
        return this->isAnchored;
    }

    // Create a piece from a piece representation (e.g. "1234" or "1234 @")
    // * `s` is the piece representation
    // * return the piece
    //
    // It can handle the following representations:
    // * "1234" : a piece with the numbers 1, 2, 3 and 4 on the sides
    // * "1234 @" : a anchored piece with the numbers 1, 2, 3 and 4 on the sides
    // * "1234@" : a anchored piece with the numbers 1, 2, 3 and 4 on the sides
    // * "1234\r\n" : a piece with the numbers 1, 2, 3 and 4 on the sides
    static Piece fromString(std::string s);

    // Convert a piece to a piece representation (e.g. "1234")
    // * return the piece representation
    // This representation does not contain the isAnchored attribute "@"
    std::string toString() const;
};

// Print a piece representation to an output stream
//
// +-----+
// |  0  |
// | 2 1 |
// |  3  |
// +-----+
std::ostream &operator<<(std::ostream &os, const Piece &p);
