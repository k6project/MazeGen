/*! \file maze.cpp
    \author Eugen(Yevhen) Brusilovskyy
    \brief Implementation of Maze class.
*/

#include "maze.h"
#include "maze_gen.h"

/* Error message table */
static const std::string __maze_errors[] =
{
    "All OK",
    "Invalid rows number specified",
    "Invalid columns number specified",
    "Memory allocation failed"
};

#include <algorithm>

Maze::Maze()
    : _rows(0),
      _cols(0),
      _cells(NULL),
      _error(Maze::ME_NOERR)
{
}

Maze::~Maze()
{
    delete[] _cells;
}

Maze::CellType Maze::cellAt(int row, int col) const
{
    if ((row >= 0 && row < _rows)
            && (col >= 0 && col < _cols))
        return _cells[row * _cols + col];
    else
        return CT_INVALID;
}

void Maze::setCellAt(int row, int col, CellType type)
{
    if ((row >= 0 && row < _rows)
            && (col >= 0 && col < _cols))
        _cells[row * _cols + col] = type;
}

const std::string& Maze::errorMessage()
{
    return __maze_errors[_error];
}

/* Explicit instantiations of Maze::build() */
template bool Maze::build<RecursiveDivision>(int, int);

template <typename G>
bool Maze::build(int rows, int cols)
{
    G generator;

    /* Check minimum size constraints */
    if (rows < MAZE_MIN_ROWS)
    {
        _error = Maze::ME_INVROWS;
        return false;
    }

    if(cols < MAZE_MIN_COLS)
    {
        _error = Maze::ME_INVCOLS;
        return false;
    }

    /* Allocate memory and reset all cells to CT_INVALID */
    try
    {
        size_t size = rows * cols;
        _cells = new CellType[size];
        std::fill_n(_cells, size, CT_INVALID);
        _rows = rows;
        _cols = cols;
    }
    catch (const std::bad_alloc &e)
    {
        _error = Maze::ME_ALLOC;
        return false;
    }

    /* Run specified generator function */
    generator(this);

    return true;
}
