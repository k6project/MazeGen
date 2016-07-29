/*! \file ascii.h
    \author Eugen(Yevhen) Brusilovskyy
    \brief Declaration of class for ASCII on-screen rendering of a maze.
*/

#ifndef ASCII_H
#define ASCII_H

#include "renderer.h"

class Maze;

/*! \brief Class that performs maze rendering with ASCII characters. */
class AsciiRenderer : public MazeRenderer
{
public:

    /*! Method, which performes maze rendering.

        \param maze Pointer to a Maze object
     */
    void render(const Maze *maze);
};

#endif // ASCII_H
