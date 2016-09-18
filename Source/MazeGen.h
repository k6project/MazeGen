#pragma once

#include <Generator/Maze.h>

#include <Engine/Application.h>
#include <Engine/Systems/SceneGraph.h>

class MazeGen : public SC::Application
{
    
protected:
    
    virtual bool OnInitialized() override;
    
private:
    
    friend class SC::Application;
    
    MazeGen();
    
    SC::SceneGraph Scene;
    
    Maze TheMaze;
    
};
