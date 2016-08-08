#include "Maze.h"

bool Maze::Generate(IndexType rows, IndexType cols)
{
    Rows = (rows < MAZE_MIN_ROWS) ? MAZE_MIN_ROWS : rows;
    Columns = (cols < MAZE_MIN_COLS) ? MAZE_MIN_COLS : cols;
    std::size_t size = Rows * Columns;
    Cells.reset(new CellType[size]);
    
    for (IndexType r = 0; r < Rows; r++)
    {
        for (IndexType c = 0; c < Columns; c++)
        {
            if (((c == 0) || (c == Columns - 1)) &&
                ((r == 0) || (r == Rows - 1)))
            {
                Cells[r * Columns + c] = CellType::CT_WALL;
            }
        }
    }
    
    return true;
}

CellType Maze::GetCellAt(IndexType row, IndexType col) const
{
    if ((row >= 0 && row < GetRows()) && (col >= 0 && col < GetColumns()))
    {
        return Cells[row * GetColumns() + col];
    }
    else
    {
        return CellType::CT_INVALID;
    }
}

void Maze::SetCellAt(IndexType row, IndexType col, CellType type)
{
    if ((row >= 0 && row < GetRows()) && (col >= 0 && col < GetColumns()))
    {
        Cells[row * GetColumns() + col] = type;
    }
}

/*
template <typename G>
bool Maze::build(int rows, int cols)
{
    G generator;

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

    generator(this);

    return true;
}*/
