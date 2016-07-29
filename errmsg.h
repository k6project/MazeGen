/*! \file errmsg.h
    \author Eugen(Yevhen) Brusilovskyy
    \brief Definition of error message constants.
*/

#ifndef ERRMSG_H
#define ERRMSG_H

#include <string>

#ifdef MAZE_ERRMSG
/* Maze-related error messages */

#endif

#ifdef RNDR_ERRMSG
/* Renderer-related error messages */
static const std::string __rndr_errors[] =
{
    "All OK"
};
#endif

#endif // ERRMSG_H
