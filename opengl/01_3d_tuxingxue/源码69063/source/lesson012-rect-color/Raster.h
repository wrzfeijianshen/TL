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

        void    drawRect(const int2* points,const Rgba* colors)
        {
            int left    =   tmax<int>(points[0].x,0);
            int top     =   tmax<int>(points[0].y,0);

            int right   =   tmin<int>(points[2].x,_width);
            int bottom  =   tmin<int>(points[2].y,_height);

            float   w   =   right - left;
            float   h   =   bottom - top;

            for (int x = left ; x <  right ; ++ x)
            {
                Rgba    color1  =   colorLerp(colors[0],colors[1],(x - left)/w);
                Rgba    color2  =   colorLerp(colors[3],colors[2],(x - left)/w);

                for (int y = top ; y <  bottom ; ++ y)
                {
                    Rgba    color  =   colorLerp(color1,color2,(y - top)/h);
                    setPixelEx(x,y,color);
                }
            }
        }
  

    public:

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
