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

    class   Span
    {
    public:
        int     _xStart;
        int     _xEnd;
        int     _y;
    public:
        Span(int xStart,int xEnd,int y)
        {
            if (xStart < xEnd)
            {
                _xStart =   xStart;
                _xEnd   =   xEnd;
                _y      =   y;
            }
            else
            {
                _xStart =   _xEnd;
                _xEnd   =   _xStart;
                _y      =   y;
            }
        }
    };

    class   Ege
    {
    public:
        int     _x1;
        int     _y1;

        int     _x2;
        int     _y2;
        Ege(int x1,int y1,int x2,int y2)
        {
            if (y1 < y2)
            {
                _x1 =   x1;
                _y1 =   y1;

                _x2 =   x2;
                _y2 =   y2;
            }
            else
            {
                _x1 =   x2;
                _y1 =   y2;

                _x2 =   x1;
                _y2 =   y1;
            }
        }
    };
    class   Raster
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

        void    drawEge(const Ege& e1,const Ege& e2)
        {

            float   xOffset     =   e2._x2 - e2._x1;
            float   yOffset     =   e2._y2 - e2._y1;

            float   scale   =   0;
            float   step    =   1.0f/yOffset;


            float   xOffset1    =   e1._x2 - e1._x1;
            float   yOffset1    =   e1._y2 - e1._y1;
            float   scale1      =   0;
            float   step1       =   1.0f/yOffset1;

            for (int y = e2._y1 ; y <= e2._y2 ; ++ y)
            {
                int     x1  =   e1._x1 + scale1 * xOffset1;
                int     x2  =   e2._x1 + scale * xOffset;

                Span    span(x1,x2,y);
                drawSpan(span);

                scale   +=  step;
                scale1  +=  step1;

            }
        }

        void    drawSpan(const Span& span)
        {
            for (int x = span._xStart ; x <= span._xEnd; ++ x)
            {
                setPixel(x,span._y,_color);
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
