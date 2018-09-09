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

        

        void    drawArrays(DRAWMODE mode,const float2* points,int count)
        {
            switch (mode)
            {
            case DM_POINTS:
                {
                    for (int i = 0 ;i < count ; ++ i)
                    {
                        drawPoints(points[i],_color);
                    }
                }
                break;
            case DM_LINES:
                {
                    count   =   count/2 * 2;
                    for (int i = 0 ;i < count ; i += 2)
                    {
                        drawLine(points[i],points[i + 1],_color,_color);
                    }
                }
                break;
            case DM_LINE_LOOP:
                {
                    drawLine(points[0],points[1],_color,_color);
                    for (int i = 2 ;i < count ; ++ i)
                    {
                        drawLine(points[i - 1],points[i],_color,_color);
                    }
                    drawLine(points[0],points[count - 1],_color,_color);
                }
                break;
            case DM_LINE_STRIP:
                {
                    drawLine(points[0],points[1],_color,_color);
                    for (int i = 2 ;i < count ; ++ i)
                    {
                        drawLine(points[i - 1],points[i],_color,_color);
                    }
                }
                break;
            default:
                break;
            }
        }
  

    public:

        void    drawLine(float2 pt1,float2 pt2,Rgba color1,Rgba color2);

        void    drawPoints(float2 pt1,Rgba4Byte color)
        {

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
