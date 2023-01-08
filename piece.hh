#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

class Piece {
    private:
        Integer north;
        Integer east;
        Integer south;
        Integer west;
        bool isAnchored;

    public:
        Piece(Integer north, Integer east, Integer south, Integer west, boolean isAnchored) {
            this->north = north;
            this->east = east;
            this->south = south;
            this->west = west;
            this->isAnchored = isAnchored;
        }

        Integer getNorth() {
            return this->north;
        }

        Integer getEast() {
            return this->east;
        }

        Integer getSouth() {
            return this->south;
        }

        Integer getWest() {
            return this->west;
        }

        std::ostream &operator<<(std::ostream &os, const Piece &piece) {
            os << "+-----+\n";
            os << "|  " << piece.getNorth() << "  |\n";
            os << "| "  << piece.getWest() << " " << piece.getEast() << " |\n";
            os << "|  " << piece.getSouth() << "  |\n";
            os << "+-----+";
            return os;
        }
}

/**
 * Creates a piece from a string representation.
 */
static Piece from_string(string s);