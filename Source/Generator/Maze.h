#pragma once

#include <string>
#include <memory>

#include <Core/Property.h>
#include <Engine/Platform/IntTypes.h>

#define MAZE_MIN_ROWS     3
#define MAZE_MIN_COLS     3
#define MAZE_DEFAULT_ROWS 32
#define MAZE_DEFAULT_COLS 32

enum class CellType
{
    INVALID = 0, WALL, ENTRY, EXIT, PATH, MAX
};

class Maze
{
    
public:
    
    typedef uint32 SizeType;
    
    typedef uint16 IndexType;
    
    enum ErrorCode
    {
        NOERR = 0, INVSIZE, BADALLOC
    };
    
    class RowProxy
    {
        
    public:
        
        RowProxy(CellType *row = nullptr, IndexType max = 0);
        
        CellType operator [](IndexType index);
    
    private:
        
        CellType *Row;
        
        IndexType Max;
    
    };
    
    RowProxy operator[](IndexType index);
    
    bool Generate(IndexType rows = MAZE_DEFAULT_ROWS, IndexType cols = MAZE_DEFAULT_COLS);
    
    CellType GetCellAt(IndexType row, IndexType col) const;
    
    void SetCellAt(IndexType row, IndexType col, CellType type);
    
    void PlaceWall(IndexType top, IndexType left, IndexType width, IndexType height);
    
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
