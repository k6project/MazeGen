/*! \file maze_gen.h
    \author Eugen(Yevhen) Brusilovskyy
    \brief Declaration of maze generator classes (RecursiveDivision).
*/

#ifndef MAZE_GEN_H
#define MAZE_GEN_H

#include "random.h"

#include <queue>

class Maze;

/*! \brief A sample maze generation implementation using recursive division
           algorithm.

    Recursive division starts with a maze arranged as a single empty area,
    enclosed by walls, with entry and exit points on opposite walls. It proceeds
    by separating this area into two with a randomly positioned wall with a
    single passage through it. The resulting sub-areas become branches of a
    binary tree. The tree is traversed further and expanded by dividing every
    new sub-area into two. Algorithm finishes, when there are no areas which can
    be further divided.
*/
struct RecursiveDivision
{

    /*! Algorithm entry point, generates maze from scratch.

        \param maze Pointer maze object
    */
    void operator()(Maze *maze);

private:

    /*! \brief Data structure to describe a sub-area of the maze.

        This sctrucutre describes an area which has its top left point at cell
        (top, left) and which is rows x cols in size.
    */
    struct Area
    {
        /*! Default constructor, creates zero-sized area */
        Area();

        /*! Constructor, creates area of defined size and location

            \param t Topmost row index (in terms of maze coordinates)
            \param l Leftmost column index
            \param r Number of rows in the area
            \param c Number of columns in the area
        */
        Area(int t, int l, int r, int c);

        /*! Test if it is possible to split a sub-area into two

            \return True if area can be split, false otherwise
        */
        bool canBeSplit();

        int top, left, rows, cols;
    };

    /*! Method to generate initial maze and place entry end exit points

        \param maze Pointer to a maze object
    */
    void initialize(Maze *maze);

    /*! Method to split vertically stretched sub-area and place a new wall

        \param area Reference to the area in question
        \param maze Pointer to maze object
    */
    void verticalSplit(const Area &area, Maze *maze);

    /*! Method to split horizontally stretched sub-area and place a new wall

        \param area Reference to the area in question
        \param maze Pointer to maze object
    */
    void horizontalSplit(const Area &area, Maze *maze);

    std::queue<Area> _areas;
    Random _random;
};

#endif // MAZE_GEN_H

