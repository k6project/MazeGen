#include "Engine/Global.h"

#include "MazeGen.h"

#include <Generator/Maze.h>
#include <Generator/Recursive.h>
#include <Engine/Platform/Logger.h>

using namespace SC;

Application * CreateSCApplication()
{
    return Application::Create<MazeGen>();
}

static void DumpNode(const SceneNode &node, const string &prefix = "")
{
    printf("%s%s\n", prefix.c_str(), node.GetName());
    SceneNode::Siblings children = node.GetChildren();
    while (children)
    {
        SceneNode child = children++;
        DumpNode(child, prefix + "    ");
    }
}

bool MazeGen::OnInitialized()
{
    if (TheMaze.Generate(32, 20))
    {
        Scene.GetRootNode()
            .AddChild("One")
                .AddChild("One-and-a-quater")
                    //.SetTransform(..., ..., ..., false)
                    .GetParent()
                .AddChild("One-and-a-half")
                    .GetParent()
                .GetParent()
            .AddChild("Two")
        ;
        //construct geometry
        //SceneNode &root = Scene.GetRootNode();
        //root.AddChild("Floor", vec3(1,2,3), vec3(0), vec3(32.f, 20.f, 1.f))
        //    .SetMesh()
        //    .SetMaterial("")
        //    .AddChild(...)
        //        .SetMesh()
        //        ...
        //        .GetParent()
        //    .AddChild(...)
        //
        //
        /*
         node contains entityID, which is used to fetch components
         
         */
    }
    DumpNode(Scene.GetRootNode());
    return true;
}

MazeGen::MazeGen()
    : Scene("MazeScene")
{
}
