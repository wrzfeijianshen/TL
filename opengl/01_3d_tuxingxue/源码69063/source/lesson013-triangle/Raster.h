#pragma once

#include "CELLMath.hpp"

namespace   CELL
{
    enum    DRAWMODE
    {
        DM_POINTS       =   0,
        DM_LINES        =   1,
        DM_LINE_LOOP    =   2,
        DM_LINE_STRIP   =   3,
    };
    class Raster
    {
    public:
        Rgba*   _buffer;
        int     _width;
        int     _height;
        Rgba    _color;
    public:
        Raster(int w,int h,void* buffer);
        ~Raster(void);

        void    clear();

        void    drawPoint(int x,int y, Rgba color,int ptSize);

        

        void    drawArrays(DRAWMODE mode,const float2* points,int count);

        void    drawFilleRect(int startX,int startY,int w,int h);

        void    drawRect(const int2* points,const Rgba* colors);
  

    public:

        void    drawLine(int startX,int endX, int y,Rgba color1,Rgba color2)
        {
            float   length  =   tmax<int>(endX - startX,1);
            for (int x = startX ; x <= endX ; ++ x)
            {
                Rgba    color   =   colorLerp(color1,color2,( x - startX)/length);
                setPixel(x,y,color);
            }
        }
        void    drawLine(float2 pt1,float2 pt2,Rgba color1,Rgba color2);

        void    drawPoints(float2 pt1,Rgba4Byte color)
        {

        }
        inline  void    setPixelEx(unsigned x,unsigned y,Rgba color)
        {
            _buffer[y * _width + x]   =   color;
        }

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
