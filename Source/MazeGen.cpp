#include "MazeGen.hpp"

#include <cstdio>

#include <Generator/Maze.hpp>
#include <Generator/Recursive.hpp>

int main(int _argc, const char **_argv)
{
    Maze maze;
    maze.Generate(16, 16);
    
    for (Maze::SizeType r = 0; r < maze.GetRows(); r++)
    {
        for (Maze::SizeType c = 0; c < maze.GetColumns(); c++)
        {
            putc('.', stdout);
        }
        putc('\n', stdout);
    }
    
    // create window
    // setup renderer capable of clearing screen with black
    
    // in render loop:
    //   if no setup has been done: setup buffers, textures and shaders
    //   else if no geometry has been set: generate maze, create geometry
    //   else render frame(dt clamped to 0.1 sec)
    //   swap buffers
    
    return 0;
}