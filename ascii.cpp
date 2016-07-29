/*! \file ascii.cpp
    \author Eugen(Yevhen) Brusilovskyy
    \brief Implementation of ASCII on-screen rendering of a maze.
*/

#include "ascii.h"
#include "maze.h"

#include <iostream>

/* Set of characters used for rendering */
static const char __output[] = { '!', '#', '@', '$', ' ' };

void AsciiRenderer::render(const Maze *maze)
{
    for (int row = 0; row < maze->rows(); row++)
    {
        for (int col = 0; col < maze->columns(); col++)
            std::cout << __output[maze->cellAt(row, col)];
        std::cout << std::endl;
    }
}
