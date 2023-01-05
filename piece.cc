#include "piece.hh"

static Piece from_string(string s) {
    if (s.size != 4 || s.size != 6) {
        throw "Invalid string length";
    }

    Integer north = atoi(s[0]);
    Integer west = atoi(s[1]);
    Integer est = atoi(s[2]);
    Integer south = atoi(s[3]);
    bool isAnchored = false;

    if (s.size == 6) {
        if (s[4] != ' ' && s[5] != '@') {
            throw "Invalid string format";
        }

        isAnchored = true;
    }

    return Piece(north, east, south, west, isAnchored);
}