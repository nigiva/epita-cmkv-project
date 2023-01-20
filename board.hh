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
    std::optional<std::pair<Coords, Coords>> lastRandomSwap;
    std::vector<Coords> movablePieceCoordsList;

public:
    Board(size_t size);
    Board(std::vector<Piece> pieces);
    static Board fromString(std::string input);
    static std::string getBoardSeperator(size_t size);
    static std::string getBoardOnePieceLine(std::vector<size_t> numberList);
    static std::string
    getBoardTwoPieceLine(std::vector<size_t> firstNumberList,
                         std::vector<bool> anchorList,
                         std::vector<size_t> secondNumberList);
    void print() const;
    void setPiece(size_t x, size_t y, Piece piece);
    std::optional<Piece> getPiece(long long int x, long long int y) const;
    size_t getSize() const;

    std::vector<Coords> getMovablePieceCoordsList() const;
    std::pair<Coords, Coords> get2RandomMovablePieceCoords() const;
    void randomSwap();
    void reverseLastRandomSwap();
    void swap(const Coords &coords1, const Coords &coords2);
    float loss() const;
    Board copy() const;
    bool solve(size_t epochMax, float initialTemperature, float decayRate,
               bool verbose);
};

std::ostream &operator<<(std::ostream &os, const Board &board);
float normalizedRandom();
float randomFloat(float min, float max);
