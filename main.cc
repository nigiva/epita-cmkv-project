#include <iostream>

#include "piece.hh"

int main()
{
    Piece p = Piece(1, 2, 3, 4, false);
    std::cout << p << std::endl;
    return 0;
}