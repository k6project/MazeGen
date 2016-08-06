#include "Maze.h"

Maze::Maze()
    : Cells(nullptr)
    , Error(MazeError::ME_NOERR)
    , Rows(0)
    , Columns(0)
{
}

bool Maze::Generate(SizeType rows, SizeType cols)
{
    Rows = (rows < MAZE_MIN_ROWS) ? MAZE_MIN_ROWS : rows;
    Columns = (cols < MAZE_MIN_COLS) ? MAZE_MIN_COLS : cols;
    std::size_t size = Rows * Columns;
    Cells.reset(new CellType[size]);

    /// add a new generation parameter - minimum dimensions of a room
    /// if minimum size is 2, then to be split in each dimension room has to be at least 5 in size
    /// so room 10 rows by 2 columns can be split only vertically
    /// terminal condition: if one of area dimensions is 1, skip it
    /// eventually there will be no areas left to subdivide
    
    for (SizeType r = 0; r < Rows; r++)
    {
        for (SizeType c = 0; c < Columns; c++)
        {
            //
        }
    }
    
    return true;
}

CellType Maze::GetCellAt(SizeType row, SizeType col) const
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

void Maze::SetCellAt(SizeType row, SizeType col, CellType type)
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
