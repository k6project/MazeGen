/*! \file jpeg.h
    \author Eugen(Yevhen) Brusilovskyy
    \brief Declaration of JPEG image rendering class.
*/

#ifndef JPEG_H
#define JPEG_H

#include "renderer.h"

#include <string>

class Maze;

/*! \brief Class, that provides functionality to render maze as JPEG image
           (grayscale), and save in into file.
 */
class JpegRenderer : public MazeRenderer
{
public:

    /*! Range of error IDs */
    enum JpegError
    {
        /*! All OK, no error */
        JE_NOERR,
        /*! Invalid number of rows */
        JE_INVROWSIZE,
        /*! Invalid number of columns */
        JE_INVCOLSIZE,
        /*! File operation failed */
        JE_FILEIO,
        /*! Memory allocation failed */
        JE_ALLOC
    };

    /*! Constructor, initializes rendering context.

        \param w Width of maze cell in pixels
        \param h Height of maze cell in pixels
        \param file Reference to a string, containing output filename
     */
    JpegRenderer(int w, int h, const std::string &file);

    /*! Method, which performes maze rendering.

        \param maze Pointer to a Maze object
     */
    void render(const Maze  *maze);

    /*! Overriden method, which retrieves a message, describing last error

        \return Reference to a string object with an error message
    */
    virtual const std::string& errorMessage() const;

    /*! Check if last operation ended in error

        \return True if error has occured
    */
    virtual bool error() const;

private:
    int _cellW, _cellH;
    std::string _file;
    JpegError _error;
};

#endif // JPEG_H
