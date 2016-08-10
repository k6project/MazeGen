#include "Maze.h"

#include <algorithm>

Maze::RowProxy::RowProxy(CellType *row, Maze::IndexType max)
    : Row(row), Max(max)
{
}

CellType Maze::RowProxy::operator[](Maze::IndexType index)
{
    return (index < Max) ? Row[index] : CellType::INVALID;
}

Maze::RowProxy Maze::operator[](IndexType index)
{
    return (index < Rows) ? RowProxy(Cells.get() + (index * Columns), Columns) : RowProxy();
}

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
                Cells[r * Columns + c] = CellType::WALL;
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
        return CellType::INVALID;
    }
}

void Maze::SetCellAt(IndexType row, IndexType col, CellType type)
{
    if ((row >= 0 && row < GetRows()) && (col >= 0 && col < GetColumns()))
    {
        Cells[row * GetColumns() + col] = type;
    }
}

void Maze::PlaceWall(IndexType top, IndexType left, IndexType width, IndexType height)
{
    IndexType maxRow = top + height;
    IndexType maxColumn = left + width;
    if ((top >= 0 && maxRow <= Rows) && (left >= 0 && maxColumn <= Columns))
    {
        for (IndexType row = top; row < maxRow; ++row)
        {
            for (IndexType col = left; col < maxColumn; ++col)
            {
                Cells[row * Columns + col] = CellType::WALL;
            }
        }
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
