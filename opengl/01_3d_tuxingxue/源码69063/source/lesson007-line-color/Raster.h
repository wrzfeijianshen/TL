#pragma once

#include "CELLMath.hpp"

namespace   CELL
{
    class Raster
    {
    public:
        Rgba*   _buffer;
        int     _width;
        int     _height;
    public:
        Raster(int w,int h,void* buffer);
        ~Raster(void);

        void    clear();

        void    drawPoint(int x,int y, Rgba color,int ptSize);

        void    drawLine(float2 pt1,float2 pt2,Rgba color1,Rgba color2);

    public:
        inline  void    setPixel(unsigned x,unsigned y,Rgba color)
        {
            if (x >= _width ||  y >= _height)
            {
                return;
            }
            _buffer[y * _width + x]   =   color;
        }
    };
}
