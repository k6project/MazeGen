/*! \file main.cpp
    \author Eugen(Yevhen) Brusilovskyy
    \brief Main program entry point.
*/

#include "maze.h"
#include "maze_gen.h"
#include "renderer.h"
#include "errmsg.h"

#include <string>
#include <iostream>
#include <boost/program_options.hpp>

int main(int argc, char *argv[])
{
    Maze maze;
    std::string filename;
    int rows, columns, cellW, cellH;
    namespace po = boost::program_options;

    /* Define and parse command line options */
    po::variables_map vmap;
    po::options_description opts("Program options");
    opts.add_options()
        ("rows,r", po::value<int>(&rows)->default_value(MAZE_DEFAULT_ROWS),
          "Number of horizontal rows of a maze")
        ("cols,c", po::value<int>(&columns)->default_value(MAZE_DEFAULT_COLS),
         "Number of vertical columns")
        ("jpeg,j", po::value<std::string>(&filename),
         "Write maze to a specified JPEG file")
        ("jpeg-column,w", po::value<int>(&cellW)->default_value(16),
         "Width of column on JPEG image in pixels")
        ("jpeg-row,h", po::value<int>(&cellH)->default_value(16),
         "Height of row on JPEG image in pixels")
        ("help,?", "Display program options");
    po::store(po::parse_command_line(argc, argv, opts), vmap);
    po::notify(vmap);

    if (vmap.count("help"))
    {
        std::cout << opts << std::endl;
        return 0;
    }
    else if (!maze.build<RecursiveDivision>(rows, columns))
    {
        std::cerr << maze.errorMessage() << std::endl;
        return -1;
    }

    /* Create maze renderer and render maze */
    MazeRenderer *renderer = NULL;
    if (vmap.count("jpeg"))
        renderer = MazeRenderer::jpeg(cellW, cellH, filename);
    else
        renderer = MazeRenderer::ascii();
    if (renderer->error())
    {
        std::cerr << renderer->errorMessage() << std::endl;
        return -1;
    }
    renderer->render(&maze);

    return 0;
}
