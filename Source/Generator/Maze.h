#pragma once

#include <string>
#include <memory>
#include <cstdint>

#include <Core/Property.h>

#define MAZE_MIN_ROWS     4
#define MAZE_MIN_COLS     4
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
    
    Maze();
    
    typedef uint16_t SizeType;
    
    bool Generate(SizeType rows = MAZE_DEFAULT_ROWS, SizeType cols = MAZE_DEFAULT_COLS);
    
    CellType GetCellAt(SizeType row, SizeType col) const;
    
    void SetCellAt(SizeType row, SizeType col, CellType type);

private:
    
    Maze(const Maze&);
    
    void operator=(const Maze&);
    
    PROPERTY(std::unique_ptr<CellType[]>, Cells)
    
    PROPERTY_R(MazeError, Error)
    
    PROPERTY_R(SizeType, Rows)

    PROPERTY_R(SizeType, Columns)

};
