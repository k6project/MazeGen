/*! \file maze.h
    \author Eugen(Yevhen) Brusilovskyy
    \brief Declaration of Maze class, inline methods definition.
*/

#ifndef MAZE_H
#define MAZE_H

#include <string>
#include <boost/utility.hpp>

/*! Minimum number of rows in the maze    */
#define MAZE_MIN_ROWS       4

/*! Minimum number of columns in the maze */
#define MAZE_MIN_COLS       4

/*! Default number of rows in the maze    */
#define MAZE_DEFAULT_ROWS   32

/*! Default number of columns in the maze */
#define MAZE_DEFAULT_COLS   64

/*! \brief A class, which encapsulated maze data. */
class Maze : boost::noncopyable
{
public:

    /*! Default constructor, constructs maze with 0 rows and 0 columns*/
    Maze();

    /*! Destructor, frees dynamically allocated memory, used by maze*/
    ~Maze();

    /*! Maze cell value type */
    enum CellType
    {
        /*! Invalid cell */
        CT_INVALID,
        /*! Wall */
        CT_WALL,
        /*! Entry point of maze */
        CT_ENTRY,
        /*! Exit point of maze */
        CT_EXIT,
        /*! Passage */
        CT_PATH,
        /*! Cell types count */
        CT_TYPES
    };

    /*! Range of error IDs */
    enum MazeError
    {
        /*! All OK, no error */
        ME_NOERR,
        /*! Invalid number of rows */
        ME_INVROWS,
        /*! Invalid number of columns */
        ME_INVCOLS,
        /*! Memory allocation failed */
        ME_ALLOC
    };

    /*! \brief Template method, that builds a maze of size rows x cols, using
               random maze pattern generator, denoted by type G.

        The only requirement to G is having public implementation of unary
        function call operator, that takes pointer to Maze object as its
        parameter:
        \code
            void operator() (Maze*);
        \endcode
        The method also performs actual memory allocation for the required
        maze size.
        \param rows Number of rows to be allocated
        \param cols Number of columns to be allocated
        \return False, if if memory allocation has failed, or if invalid maze
                size was specified, otherwise true
    */
    template <typename G>
    bool build(int rows = MAZE_DEFAULT_ROWS, int cols = MAZE_DEFAULT_COLS);

    /*! Helper method, which retrieves a message, describing last error

        \return Reference to a string object with an error message
    */
    const std::string& errorMessage();

    /*! Check if last operation ended in error

        \return True if error has occured
    */
    bool error() const;

    /*! Getter method, returns cell value at (row,col)

        \param row Row index
        \param col Column index
        \return Type of cell at (row,col), or CT_INVALID if invalid coordinates
                were specified
    */
    CellType cellAt(int row, int col) const;

    /*! Setter method, sets cell value at (row,col)

        \param row Row index
        \param col Column index
        \param type Type of cell at (row,col)
    */
    void setCellAt(int row, int col, CellType type);

    /*! Getter method, returns number of rows in a maze

        \return Number of rows
    */
    int columns() const;

    /*! Getter method, returns number of columns in a maze

        \return Number of columns
    */
    int rows() const;

private:
    int _rows, _cols;
    CellType *_cells;
    MazeError _error;
};

/* Definition of some access methods as inline */

inline bool Maze::error() const
{
    return (_error != Maze::ME_NOERR);
}

inline int Maze::columns() const
{
    return _cols;
}

inline int Maze::rows() const
{
    return _rows;
}

#endif // MAZE_H

