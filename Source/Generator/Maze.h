#pragma once

#include <string>
#include <memory>
#include <cstdint>

#include <Core/Property.h>

#define MAZE_MIN_ROWS     3
#define MAZE_MIN_COLS     3
#define MAZE_DEFAULT_ROWS 32
#define MAZE_DEFAULT_COLS 32

enum class MazeError
{
    ME_NOERR, ME_INVROWS, ME_INVCOLS, ME_ALLOC
};

enum class CellType
{
    CT_INVALID = 0, CT_WALL, CT_ENTRY, CT_EXIT, CT_PATH, CT_TYPES
};

class Maze
{
    
public:
    
    typedef uint32_t SizeType;
    
    typedef uint16_t IndexType;
    
    enum ErrorCode
    {
        NOERR = 0, INVSIZE, BADALLOC
    };
    
    bool Generate(IndexType rows = MAZE_DEFAULT_ROWS, IndexType cols = MAZE_DEFAULT_COLS);
    
    CellType GetCellAt(IndexType row, IndexType col) const;
    
    void SetCellAt(IndexType row, IndexType col, CellType type);
    
    ErrorCode GetError() const;

    IndexType GetColumns() const;
    
    IndexType GetRows() const;
    
private:
    
    std::unique_ptr<CellType[]> Cells = nullptr;
    
    ErrorCode Error = NOERR;
    
    IndexType Columns = MAZE_MIN_COLS;
    
    IndexType Rows = MAZE_MIN_ROWS;

};

inline Maze::ErrorCode Maze::GetError() const
{
    return Error;
}

inline Maze::IndexType Maze::GetColumns() const
{
    return Columns;
}

inline Maze::IndexType Maze::GetRows() const
{
    return Rows;
}
