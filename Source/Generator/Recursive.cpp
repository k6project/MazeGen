#include "Recursive.h"

#include <queue>
#include <algorithm>

#include <Generator/Maze.h>
#include <Generator/Random.h>

#define FL_HORIZONTAL 0x01
#define FL_VERTCICAL  0x02

struct Rect
{
    Maze::IndexType Top, Left, Width, Height;
    
    enum class Neighbour { ABOVE, BELOW, BEFORE, AFTER };
    
    bool UnBlock(Maze &maze, Maze::IndexType top, Maze::IndexType left, Neighbour neighbour)
    {
        Maze::IndexType t = top, l = left;
        switch (neighbour)
        {
            case Neighbour::ABOVE:  t = (t > 0) ? t - 1 : t; break;
            case Neighbour::BELOW:  t = (t < maze.GetRows() - 1) ? t + 1 : t; break;
            case Neighbour::BEFORE: l = (l > 0) ? l - 1 : l; break;
            case Neighbour::AFTER:  l = (l < maze.GetColumns() - 1) ? l + 1 : l; break;
        }
        if ((maze.GetCellAt(top, left) == CellType::CT_WALL) && (maze.GetCellAt(t, l) != CellType::CT_WALL))
        {
            maze.SetCellAt(top, left, CellType::CT_PATH);
            return true;
        }
        return false;
    }
    
    std::pair<Rect, Rect> HorizontalSplit(Maze &maze)
    {
        Rect one = *this, two = *this;
        Maze::IndexType wallOffset = Width >> 1; //TODO Randomize
        Maze::IndexType wallGlobalOffset = Left + wallOffset;
        maze.PlaceWall(Top, wallGlobalOffset, 1, Height);
        if (!UnBlock(maze, Top, wallGlobalOffset, Neighbour::ABOVE) &&
            !UnBlock(maze, Top + Height - 1, wallGlobalOffset, Neighbour::BELOW))
        {
            //TODO place random door
        }
        two.Left = wallGlobalOffset + 1;
        two.Width = Width - wallOffset - 1;
        one.Width = wallOffset;
        return std::make_pair(one, two);
    }
    
    int CanSubdivide() const
    {
        int retVal = (Width >= MAZE_MIN_COLS) ? FL_HORIZONTAL : 0;
        retVal |= (Height >= MAZE_MIN_ROWS) ? FL_VERTCICAL : 0;
        return retVal;
    }
    
};

bool RecursiveDivision(Maze &maze)
{
    std::queue<Rect> subAreas;
    Rect area = { 1, 1, 1, 1 };
    area.Height = maze.GetRows() - 2;
    area.Width = maze.GetColumns() - 2;
    
    subAreas.push(area);
    while (!subAreas.empty())
    {
        Rect current = subAreas.front();
        int canSubdivide = current.CanSubdivide();
        if (canSubdivide != 0)
        {
            int req = (current.Width > current.Height) ? FL_HORIZONTAL : FL_VERTCICAL;
            int subdivision = ((req & canSubdivide) > 0) ? req : canSubdivide;
            switch (subdivision)
            {
                case FL_HORIZONTAL:
                    //
                    break;
                case FL_VERTCICAL:
                    //
                    break;
            }
        }
        subAreas.pop();
    }
    
    return true;
}

//
//RecursiveDivision::Area::Area()
//    : top(0), left(0), rows(0), cols(0)
//{
//}
//
//RecursiveDivision::Area::Area(int t, int l, int r, int c)
//    : top(t), left(l), rows(r), cols(c)
//{
//}
//
//bool RecursiveDivision::Area::canBeSplit()
//{
//    return (rows > 1 && cols > 1 && (rows + cols) > 5);
//}
//
//void RecursiveDivision::initialize(Maze &maze)
//{
//    int bottom = maze.rows() - 1;
//    int right = maze.columns() - 1;
//
//    /* Make walls around empty maze */
//    for (int row = 0; row < maze.rows(); row++)
//    {
//        for (int col = 0; col < maze.columns(); col++)
//        {
//            if ((row == 0 || row == bottom) || (col == 0 || col == right))
//                maze.setCellAt(row, col, Maze::CT_WALL);
//            else
//                maze.setCellAt(row, col, Maze::CT_PATH);
//        }
//    }
//
//    /* Add start point and exit point */
//    if (maze.columns() > maze.rows())
//    {
//        maze.setCellAt(bottom - 1, right, Maze::CT_EXIT);
//        maze.setCellAt(1, 0, Maze::CT_ENTRY);
//    }
//    else
//    {
//        maze.setCellAt(bottom, right - 1, Maze::CT_EXIT);
//        maze.setCellAt(0, 1, Maze::CT_ENTRY);
//    }
//}
//
//void RecursiveDivision::verticalSplit(const Area &area, Maze &maze)
//{
//    int r_offs = Random::UInt32(1, area.rows - 2);
//
//    /* Place a new horizontal wall inside existing maze */
//    for (int col = area.left; col < area.left + area.cols; col++)
//        maze.setCellAt(area.top + r_offs, col, Maze::CT_WALL);
//
//    /*  Make sure that we didn't block other passage with endpoints of the
//        new wall. If we do, create passage at blocking point. Otherwise,
//        place new passage at random along new wall.
//    */
//    if (maze.cellAt(area.top + r_offs, area.left - 1) != Maze::CT_WALL
//            || maze.cellAt(area.top + r_offs, area.left + area.cols) != Maze::CT_WALL)
//    {
//        if (maze.cellAt(area.top + r_offs, area.left - 1) != Maze::CT_WALL)
//            maze.setCellAt(area.top + r_offs, area.left, Maze::CT_PATH);
//        if (maze.cellAt(area.top + r_offs, area.left + area.cols) != Maze::CT_WALL)
//            maze.setCellAt(area.top + r_offs, area.left + area.cols - 1, Maze::CT_PATH);
//    }
//    else
//    {
//        int c_offs = Random::UInt32(0, area.cols - 1);
//        maze.setCellAt(area.top + r_offs, area.left + c_offs, Maze::CT_PATH);
//    }
//
//    /* Add sub-areas to the queue */
//    _areas.push(Area(area.top, area.left, r_offs, area.cols));
//    _areas.push(Area(area.top + r_offs + 1, area.left,
//                     area.rows - r_offs - 1, area.cols));
//}
//
//void RecursiveDivision::horizontalSplit(const Area &area, Maze &maze)
//{
//    int c_offs = _random(1, area.cols - 2);
//
//    /* Place a new vertical wall inside existing maze */
//    for (int row = area.top; row < area.top + area.rows; row++)
//        maze.setCellAt(row, area.left + c_offs, Maze::CT_WALL);
//
//    /*  Make sure that we didn't block other passage with endpoints of the
//        new wall. If we do, create passage at blocking point. Otherwise,
//        place new passage at random along new wall.
//    */
//    if (maze.cellAt(area.top - 1, area.left + c_offs) != Maze::CT_WALL
//            || maze.cellAt(area.top + area.rows, area.left + c_offs) != Maze::CT_WALL)
//    {
//        if (maze.cellAt(area.top - 1, area.left + c_offs) != Maze::CT_WALL)
//            maze.setCellAt(area.top, area.left + c_offs, Maze::CT_PATH);
//        if (maze.cellAt(area.top + area.rows, area.left + c_offs) != Maze::CT_WALL)
//            maze.setCellAt(area.top + area.rows - 1, area.left + c_offs, Maze::CT_PATH);
//    }
//    else
//    {
//        int r_offs = _random(0, area.rows - 1);
//        maze.setCellAt(area.top + r_offs, area.left + c_offs, Maze::CT_PATH);
//    }
//
//    /* Add sub-areas to the queue */
//    _areas.push(Area(area.top, area.left, area.rows, c_offs));
//    _areas.push(Area(area.top, area.left + c_offs + 1,
//                     area.rows, area.cols - c_offs - 1));
//}
//
//bool RecursiveDivision::operator()(Maze &maze)
//{
//    initialize(maze);
//
//    /* Add entire maze space as starting area */
//    _areas.push(Area(1, 1, maze->rows() - 2, maze->columns() - 2));
//
//    /* Traverse sub-areas in breadth-first order */
//    while (!_areas.empty())
//    {
//        if (_areas.front().canBeSplit())
//        {
//            /* If current sub-area has more columns then rows, we split it
//               horizontally, otherwise vertically
//            */
//            if (_areas.front().rows <= _areas.front().cols)
//                horizontalSplit(_areas.front(), maze);
//            else
//                verticalSplit(_areas.front(), maze);
//        }
//        _areas.pop();
//    }
//}
