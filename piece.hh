#pragma once
#include <iostream>
#include <string>

class Piece
{
private:
    int north;
    int east;
    int south;
    int west;
    bool isAnchored;

public:
    Piece(int north, int east, int south, int west, bool isAnchored)
        : north(north)
        , east(east)
        , south(south)
        , west(west)
        , isAnchored(isAnchored)
    {}

    int getNorth() const
    {
        return this->north;
    }

    int getEast() const
    {
        return this->east;
    }

    int getSouth() const
    {
        return this->south;
    }

    int getWest() const
    {
        return this->west;
    }

    bool getIsAnchored() const
    {
        return this->isAnchored;
    }

    /**
     * Creates a piece from a string representation.
     */
    static Piece fromString(std::string s);
    std::string toString() const;
};

std::ostream &operator<<(std::ostream &os, const Piece &p);
