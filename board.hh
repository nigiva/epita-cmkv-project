#pragma once
#include <iostream>
#include <optional>
#include <string>
#include <vector>

#include "piece.hh"

class Coords
{
public:
    size_t x;
    size_t y;
    Coords(size_t x, size_t y)
        : x(x)
        , y(y)
    {}
    bool operator==(const Coords &other) const
    {
        return x == other.x && y == other.y;
    }
};

class Board
{
private:
    size_t size;
    std::vector<std::vector<std::optional<Piece>>> board;
    size_t numPieces;
    size_t numEdges;
    std::optional<Coords> fromLastRandomSwap;
    std::optional<Coords> toLastRandomSwap;

public:
    Board(size_t size);
    Board(std::vector<Piece> pieces);
    static Board fromString(std::string input);
    static std::string getBoardSeperator(size_t size);
    static std::string getBoardOnePieceLine(std::vector<size_t> numberList);
    static std::string
    getBoardTwoPieceLine(std::vector<size_t> firstNumberList,
                         std::vector<size_t> secondNumberList);
    void print() const;
    void setPiece(size_t x, size_t y, Piece piece);
};

std::ostream &operator<<(std::ostream &os, const Board &board);
