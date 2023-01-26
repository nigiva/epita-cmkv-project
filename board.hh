#pragma once
#include <iostream>
#include <optional>
#include <string>
#include <vector>

#include "piece.hh"

// Coordinates of a piece on the board
class Coords
{
public:
    size_t x;
    size_t y;

    // Constructor
    // * `x` is the x coordinate of the piece
    // * `y` is the y coordinate of the piece
    Coords(size_t x, size_t y)
        : x(x)
        , y(y)
    {}

    // Compare two coordinates
    // * `other` is the other coordinates to compare
    // Return true if the coordinates are equal
    bool operator==(const Coords &other) const
    {
        return x == other.x && y == other.y;
    }
};

// A board of the puzzle
class Board
{
private:
    size_t size;
    std::vector<std::vector<std::optional<Piece>>> board;
    size_t numPieces;
    size_t numEdges;
    std::optional<std::pair<Coords, Coords>> lastRandomSwap;
    std::vector<Coords> movablePieceCoordsList;
    std::optional<float> lastLoss;
    std::optional<float> backupLoss;
    bool lossIsComputed;

    // Methods to print the board

    // Get the string representation of the line separator of the board
    // * `size` is the size of the board
    // Return the string representation of the line separator of the board
    // (e.g. "+---+---+---+---+") for a 4x4 board (size = 4)
    static std::string getBoardSeperator(size_t size);

    // Get the string representation of a line with one piece
    // * `numberList` is the list of numbers on the line
    //
    // For example, for the this line of piece :
    // +-----+-----+-----+-----+
    // |  0  |  1  |  7  |  2  |
    // | 2 1 | 1 9 | 9@5 | 5 9 |
    // |  3  |  1  |  1  |  0  |
    // +-----+-----+-----+-----+
    // the `numberList` is [0, 1, 7, 2] for the first line
    // and [3, 1, 1, 0] for the third line.
    static std::string getBoardOnePieceLine(std::vector<size_t> numberList);

    // Get the string representation of a line with two pieces
    // * `firstNumberList` is the list of numbers on the first piece
    // * `anchorList` is the list of anchors on the line
    // * `secondNumberList` is the list of numbers on the second piece
    //
    // For example, for the this line of piece :
    // +-----+-----+-----+-----+
    // |  0  |  1  |  7  |  2  |
    // | 2 1 | 1 9 | 9@5 | 5 9 |
    // |  3  |  1  |  1  |  0  |
    // +-----+-----+-----+-----+
    // the `firstNumberList` is [2, 1, 9, 5] for the second line
    // the `anchorList` is [false, false, true, false] for the second line
    // the `secondNumberList` is [1, 9, 5, 9] for the second line
    static std::string
    getBoardTwoPieceLine(std::vector<size_t> firstNumberList,
                         std::vector<bool> anchorList,
                         std::vector<size_t> secondNumberList);

    // Methods to compute the loss

    // Get the loss of the board
    // This method recompute from scratch the loss of the board
    // in parcouring all the pieces
    float globalLoss() const;

    // Get the loss of a part of the board
    // This method compute only the loss of the last swap of pieces
    float localLoss();

    // Get the loss of a piece
    // * `coords` is the coordinates of the piece
    // * `piece` is the piece
    // Return the loss of the piece (the sum of the loss of each edge)
    // Warning: this method does not consider the loss of the neighbors
    float pieceLoss(const Coords &coords, const Piece &piece) const;

    // Get the loss of a piece and the impact of the loss of the neighbors
    // * `firstCoords` is the coordinates of the piece where the loss is
    // computed
    // * `secondCoords` is the coordinates of the other piece (this function
    // does not compute the loss of this piece)

    // If the two pieces are *not* neighbors, the loss of the first piece is
    // computed and we add the loss of the impacted edges of the neighbors. If
    // the two pieces are neighbors, the loss of the first piece is computed and
    // we add the loss of the impacted edges of the neighbors.
    //   But we also remove the loss of the impacted edges counted twice
    //   (because the both pieces are neighbors)
    float pieceCrossLoss(const Coords &firstCoords,
                         const Coords &secondCoords) const;

    // Methods to move pieces randomly

    // Get the list of the coordinates of the pieces that can be moved
    // This ignores the pieces with the parameter `isAnchored` set to true
    std::vector<Coords> getMovablePieceCoordsList() const;

    // Get two random coordinates of pieces that can be moved
    std::pair<Coords, Coords> get2RandomMovablePieceCoords() const;

public:
    // Constructor
    // * `size` is the size of the board
    Board(size_t size);

    // Constructor
    // * `pieces` is the list of pieces to put on the board
    Board(std::vector<Piece> pieces);

    // Get the board from a string representation
    // * `input` is the string representation of the board
    //
    // For example, the following representation :
    // 0213
    // 1191
    // 2591 @
    // 3950
    // gives the following board :
    // +-----+-----+
    // |  0  |  1  |
    // | 2 1 | 1 9 |
    // |  3  |  1  |
    // +-----+-----+
    // |  2  |  3  |
    // | 5@9 | 9 5 |
    // |  1  |  0  |
    // +-----+-----+
    static Board fromString(std::string input);

    // Get the string representation of the board
    // This method does not consider the parameter `isAnchored` of the pieces
    // So, the characters '@' are not printed but the pieces are printed as if
    // they were not anchored
    //
    // For example, the following board :
    // +-----+-----+
    // |  0  |  1  |
    // | 2 1 | 1 9 |
    // |  3  |  1  |
    // +-----+-----+
    // |  2  |  3  |
    // | 5@9 | 9 5 |
    // |  1  |  0  |
    // +-----+-----+
    // gives the following representation :
    // 0213
    // 1191
    // 2591
    // 3950
    std::string toString() const;

    friend std::ostream &operator<<(std::ostream &os, const Board &board);

    // Debug method to print the board
    // DEPRECATED
    void print() const;

    // Set the piece at the given coordinates
    // * `x` is the x coordinate
    // * `y` is the y coordinate
    // * `piece` is the piece to put at the given coordinates
    void setPiece(size_t x, size_t y, Piece piece);

    // Get the piece at the given coordinates
    // * `x` is the x coordinate
    // * `y` is the y coordinate
    // Return the piece at the given coordinates
    // If there is no piece at the given coordinates, return an empty optional
    // If the coordinates are out of the board, return an empty optional
    std::optional<Piece> getPiece(long long int x, long long int y) const;

    // Get the piece at the given coordinates
    // * `coords` is the coordinates of the piece
    // Return the piece at the given coordinates
    // If there is no piece at the given coordinates, return an empty optional
    // If the coordinates are out of the board, return an empty optional
    std::optional<Piece> getPiece(const Coords &coords) const;

    // Get the size of the board
    size_t getSize() const;

    // Swap randomly two pieces
    void randomSwap();

    // Reverse the last swap
    void reverseLastRandomSwap();

    // Swap two pieces
    // * `coords1` is the coordinates of the first piece
    // * `coords2` is the coordinates of the second piece
    void swap(const Coords &coords1, const Coords &coords2);

    // Get the loss of the board
    // This method use the cache of the last loss
    // So, if the board has not changed since the last call to this method, the
    // loss is not recomputed If the board has changed, the loss is recomputed
    // but in a more efficient way than the method `globalLoss` because the last
    // loss and the loss of the last swap are used
    float loss();

    // Get a deep copy of the board
    Board copy() const;

    // Solve the board
    // * `epochMax` is the maximum number of epochs
    // * `initialTemperature` is the initial temperature (tips : use 1.0 or 2.0)
    // * `coldFactor` is the factor to decrease the temperature (tips : use
    // 0.9999)
    // * `heatFactor` is the factor to increase the temperature (tips : use
    // 0.999)
    // * `stuckCounterMax` is the maximum number of epochs without improvement.
    // After, the temperature is increased
    // * `verbose` is a boolean to print the loss at each epoch
    // Return true if the board is solved, false otherwise
    bool solve(const size_t epochMax, const float initialTemperature,
               const float coldFactor, const float heatFactor,
               const size_t stuckCounterMax, const bool verbose);
};

// Print the board
//
// For example :
// +-----+-----+
// |  0  |  1  |
// | 2 1 | 1 9 |
// |  3  |  1  |
// +-----+-----+
// |  2  |  3  |
// | 5@9 | 9 5 |
// |  1  |  0  |
// +-----+-----+
std::ostream &operator<<(std::ostream &os, const Board &board);

// Get a random float between 0 and 1
float normalizedRandom();

// Get a random float between min and max
// * `min` is the minimum value
// * `max` is the maximum value
float randomFloat(float min, float max);
