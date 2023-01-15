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
    {
        this->north = north;
        this->east = east;
        this->south = south;
        this->west = west;
        this->isAnchored = isAnchored;
    }

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
};

std::ostream &operator<<(std::ostream &os, const Piece &p);
