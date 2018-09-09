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
        Rgba    _colorStart;
        Rgba    _colorEnd;
        int     _y;

    public:
        Span(int xStart,int xEnd,int y,Rgba colorStart,Rgba colorEnd)
        {
            if (xStart < xEnd)
            {
                _xStart     =   xStart;
                _xEnd       =   xEnd;
                _colorStart =   colorStart;
                _colorEnd   =   colorEnd;
                _y          =   y;
            }
            else
            {
                _xStart =   _xEnd;
                _xEnd   =   _xStart;

                _colorStart =   colorEnd;
                _colorEnd   =   colorStart;
                _y      =   y;
            }
        }
    };

    class   Ege
    {
    public:
        int     _x1;
        int     _y1;
        Rgba    _color1;

        int     _x2;
        int     _y2;
        Rgba    _color2;

        Ege(int x1,int y1,Rgba color1,int x2,int y2,Rgba color2)
        {
            if (y1 < y2)
            {
                _x1     =   x1;
                _y1     =   y1;
                _color1 =   color1;

                _x2     =   x2;
                _y2     =   y2;
                _color2 =   color2;
            }
            else
            {
                _x1     =   x2;
                _y1     =   y2;
                _color1 =   color2;

                _x2     =   x1;
                _y2     =   y1;
                _color2 =   color1;
            }
        }
    };
    class   Raster
    {
    public:
        uint*   _buffer;
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
        void    drawTriangle(int2 p0,int2 p1,int2 p2,Rgba c0,Rgba c1,Rgba c2)
        {
            Ege eges[3]  =   
            {
                Ege(p0.x,p0.y,c0,   p1.x,p1.y,c1),
                Ege(p1.x,p1.y,c1,   p2.x,p2.y,c2),
                Ege(p2.x,p2.y,c2,   p0.x,p0.y,c0),
            };
            int iMax    =   0;
            int length  =   eges[0]._y2 - eges[0]._y1;
            
            for (int i = 1 ;i < 3 ; ++ i)
            {
                int len =   eges[i]._y2 - eges[i]._y1;
                if (len > length)
                {
                    length  =   i;
                }
            }
            int iShort1 =   (iMax + 1)%3;
            int iShort2 =   (iMax + 2)%3;

            drawEge(eges[iMax],eges[iShort1]);
            drawEge(eges[iMax],eges[iShort2]);

        }

        void    drawEge(const Ege& e1,const Ege& e2)
        {
            float   yOffset1    =   e1._y2 - e1._y1;
            if (yOffset1 == 0)
            {
                return;
            }

            float   yOffset     =   e2._y2 - e2._y1;
            if (yOffset == 0)
            {
                return;
            }
            float   xOffset =   e2._x2 - e2._x1;
            float   scale   =   0;
            float   step    =   1.0f/yOffset;


            float   xOffset1    =   e1._x2 - e1._x1;
            float   scale1      =   (float)(e2._y1 - e1._y1)/yOffset1;
            float   step1       =   1.0f/yOffset1;

            for (int y = e2._y1 ; y < e2._y2 ; ++ y)
            {
                int     x1      =   e1._x1 + (int)(scale1 * xOffset1);
                int     x2      =   e2._x1 + (int)(scale * xOffset);
                Rgba    color2  =   colorLerp(e2._color1,e2._color2,scale);
                Rgba    color1  =   colorLerp(e1._color1,e1._color2,scale1);

                Span    span(x1,x2,y,color1,color2);
                drawSpan(span);

                scale   +=  step;
                scale1  +=  step1;

            }
        }

        void    drawSpan(const Span& span)
        {
            float   length  =   span._xEnd - span._xStart;
            float   scale   =   0;
            float   step    =   1.0f/length;
            for (int x = span._xStart ; x < span._xEnd; ++ x)
            {
                Rgba    color   =   colorLerp(
                     span._colorStart
                    ,span._colorEnd
                    ,scale
                    );
                scale   +=  step;

                setPixel(x,span._y,color);
            }
        }
        void    drawLine(float2 pt1,float2 pt2,Rgba color1,Rgba color2);

        void    drawPoints(float2 pt1,Rgba4Byte color)
        {

        }
        inline  void    setPixelEx(unsigned x,unsigned y,Rgba color)
        {
            _buffer[y * _width + x]   =   color._color;
        }

        inline  void    setPixel(unsigned x,unsigned y,Rgba color)
        {
            if (x >= _width ||  y >= _height)
            {
                return;
            }
            _buffer[y * _width + x]   =   color._color;
        }
    };
}
