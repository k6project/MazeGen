/*! \file jpeg.cpp
    \author Eugen(Yevhen) Brusilovskyy
    \brief Implementation of JPEG image rendering using LibJPEG.
*/

#include "jpeg.h"
#include "maze.h"

#include <jpeglib.h>
#include <cstdio>

/* Error message table */
static const std::string __jpeg_errors[] =
{
    "All OK",
    "Invalid row height specified",
    "Invalid column width specified",
    "Failed to create output file",
    "Memory allocation failed"
};

JpegRenderer::JpegRenderer(int w, int h, const std::string &file)
    : _cellW(w), _cellH(h), _file(file), _error(JE_NOERR)
{
    if (_cellW < 1)
        _error = JE_INVCOLSIZE;
    else if (_cellH < 1)
        _error = JE_INVROWSIZE;
}

void JpegRenderer::render(const Maze *maze)
{
    jpeg_error_mgr jerr;
    jpeg_compress_struct cinfo;
    JSAMPROW jpgRows[_cellH];

    JSAMPLE *jpgRow = new JSAMPLE[_cellW * maze->columns()];
    if (jpgRow == NULL)
    {
        _error = JE_ALLOC;
        return;
    }

    FILE *outfile = fopen(_file.c_str(), "wb");
    if (outfile == NULL)
    {
        _error = JE_FILEIO;
        delete [] jpgRow;
        return;
    }

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);
    jpeg_stdio_dest(&cinfo, outfile);
    cinfo.image_width = _cellW * maze->columns();
    cinfo.image_height = _cellH * maze->rows();
    cinfo.in_color_space = JCS_GRAYSCALE;
    cinfo.input_components = 1;
    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, 100, TRUE);
    jpeg_start_compress(&cinfo, TRUE);

    for (int row = 0; row < maze->rows(); row++)
    {
        for (int col = 0; col < maze->columns(); col++)
        {
            JSAMPLE *part = jpgRow + (col * _cellW);
            for (int pos = 0; pos < _cellW; pos++)
                part[pos] = (maze->cellAt(row, col) == Maze::CT_WALL)
                        ? 0x00 : 0xFF;
        }
        for (int pos = 0; pos < _cellH; pos++)
            jpgRows[pos] = jpgRow;
        jpeg_write_scanlines(&cinfo, jpgRows, _cellH);
    }

    jpeg_finish_compress(&cinfo);
    fclose(outfile);
    jpeg_destroy_compress(&cinfo);
    delete [] jpgRow;
}

const std::string &JpegRenderer::errorMessage() const
{
    return __jpeg_errors[_error];
}

bool JpegRenderer::error() const
{
    return (_error != JE_NOERR);
}
