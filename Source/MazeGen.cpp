#include "Engine/Global.h"

#include "MazeGen.h"

#include <Generator/Maze.h>
#include <Generator/Recursive.h>
#include <Engine/Platform/Logger.h>
#include <Engine/Resource/Material.h>

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
                    .SetDrawable("DefaultQuadMesh", "TexCoordView")
                    .GetParent()
                .AddChild("One-and-a-half")
                    .GetParent()
                .GetParent()
            .AddChild("Two")
        ;
    }
    
    Material test;
    test.Init({ { "Byte", ValueType::INT8 }, { "QWord", ValueType::INT64 } });
    test.Set<int8_t>("Byte", -128);
    test.Set<int64_t>("QWord", 1);
    
    DumpNode(Scene.GetRootNode());
    return true;
}

MazeGen::MazeGen()
    : Scene("MazeScene")
{
}
