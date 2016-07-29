/*! \file renderer.cpp
    \author Eugen(Yevhen) Brusilovskyy
    \brief Implementation of static and common methods of Renderer class.
*/

#include "errmsg.h"
#include "renderer.h"
#include "ascii.h"
#include "jpeg.h"

static const std::string __rndr_errors[] =
{
    "All OK"
};

MazeRenderer* MazeRenderer::ascii()
{
    return new AsciiRenderer();
}

MazeRenderer *MazeRenderer::jpeg(int cw, int ch, const std::string &fn)
{
    return new JpegRenderer(cw, ch, fn);
}

const std::string& MazeRenderer::errorMessage() const
{
    return __rndr_errors[0];
}

bool MazeRenderer::error() const
{
    return false;
}
