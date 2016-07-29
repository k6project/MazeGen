/*! \file renderer.h
    \author Eugen(Yevhen) Brusilovskyy
    \brief Declaration of Renderer interface for maze on-screen rendering.
*/

#ifndef RENDERER_H
#define RENDERER_H

#include <string>

class Maze;

/*! \brief Interface for maze on-screen rendering */
class MazeRenderer
{
public:

    /*! Static factory method to construct ASCII renderer.

        \return Pointer to allocated renderer object
     */
    static MazeRenderer* ascii();

    /*! Static factory method to construct JPEG renderer.

        \param cw Width of maze cell in pixels
        \param ch Height of maze cell in pixels
        \param fn Reference to a string, containing output filename
        \return Pointer to allocated renderer object
     */
    static MazeRenderer* jpeg(int cw, int ch, const std::string &fn);

    /*! Virtual method, which performes maze rendering.

        \param maze Pointer to a Maze object
     */
    virtual void render(const Maze *maze) = 0;

    /*! Helper method, which retrieves a message, describing last error

        \return Reference to a string object with an error message
    */
    virtual const std::string& errorMessage() const;

    /*! Check if last operation ended in error

        \return True if error has occured
    */
    virtual bool error() const;
};

#endif // RENDERER_H
