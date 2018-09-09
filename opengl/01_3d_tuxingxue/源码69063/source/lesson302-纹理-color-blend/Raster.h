#pragma once

#include "CELLMath.hpp"

#include "Image.hpp"

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

        float2  _uvStart;
        float2  _uvEnd;

        int     _y;

    public:
        Span(int xStart,int xEnd,int y,Rgba colorStart,Rgba colorEnd,float2 uvStart,float2 uvEnd)
        {
            if (xStart < xEnd)
            {
                _xStart     =   xStart;
                _xEnd       =   xEnd;
                _colorStart =   colorStart;
                _colorEnd   =   colorEnd;

                _uvStart    =   uvStart;
                _uvEnd      =   uvEnd;

                _y          =   y;
            }
            else
            {
                _xStart     =   xEnd;
                _xEnd       =   xStart;

                _colorStart =   colorEnd;
                _colorEnd   =   colorStart;

                _uvStart    =   uvEnd;
                _uvEnd      =   uvStart;
                _y          =   y;
            }
        }
    };

    class   Ege
    {
    public:
        int     _x1;
        int     _y1;
        float2  _uv1;   
        Rgba    _color1;

        int     _x2;
        int     _y2;
        float2  _uv2;  
        Rgba    _color2;

        Ege(int x1,int y1,Rgba color1,float2 uv1,int x2,int y2,Rgba color2,float2 uv2)
        {
            if (y1 < y2)
            {
                _x1     =   x1;
                _y1     =   y1;
                _uv1    =   uv1;
                _color1 =   color1;

                _x2     =   x2;
                _y2     =   y2;
                _uv2    =   uv2;
                _color2 =   color2;
            }
            else
            {
                _x1     =   x2;
                _y1     =   y2;
                _uv1    =   uv2;
                _color1 =   color2;

                _x2     =   x1;
                _y2     =   y1;
                _uv2    =   uv1;
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

        struct  Vertex
        {
            int2    p0;
            float2  uv0;
            Rgba    c0;

            int2    p1;
            float2  uv1;
            Rgba    c1;

            int2    p2;
            float2  uv2;
            Rgba    c2;

        };
        
        void    drawImage(int startX,int startY,const Image* image)
        {
            int left    =   tmax<int>(startX,0);
            int top     =   tmax<int>(startY,0);

            int right   =   tmin<int>(startX + image->width(),_width);
            int bottom  =   tmin<int>(startY + image->height(),_height);

            for (int x = left ; x <  right ; ++ x)
            {
                for (int y = top ; y <  bottom ; ++ y)
                {
                    Rgba    color   =   image->pixelAt(x - left,y - top);
                    setPixelEx(x,y,color);
                }
            }
        }
    public:
        void    drawTriangle(const Vertex& vertex,Image* image)
        {
            Ege eges[3]  =   
            {
                Ege(vertex.p0.x,vertex.p0.y,vertex.c0,  vertex.uv0, vertex.p1.x,vertex.p1.y,vertex.c1,  vertex.uv1),
                Ege(vertex.p1.x,vertex.p1.y,vertex.c1,  vertex.uv1, vertex.p2.x,vertex.p2.y,vertex.c2,  vertex.uv2),
                Ege(vertex.p2.x,vertex.p2.y,vertex.c2,  vertex.uv2, vertex.p0.x,vertex.p0.y,vertex.c0,  vertex.uv0),
            };
            int iMax    =   0;
            int length  =   eges[0]._y2 - eges[0]._y1;
            
            for (int i = 1 ;i < 3 ; ++ i)
            {
                int len =   eges[i]._y2 - eges[i]._y1;
                if (len > length)
                {
                    length  =   len;
                    iMax    =   i;
                }
            }
            int iShort1 =   (iMax + 1)%3;
            int iShort2 =   (iMax + 2)%3;

            drawEge(eges[iMax],eges[iShort1],image);
            drawEge(eges[iMax],eges[iShort2],image);

        }

        void    drawEge(const Ege& e1,const Ege& e2,Image* image)
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

                float2  uvStart =   uvLerp(e1._uv1,e1._uv2,scale1);
                float2  uvEnd   =   uvLerp(e2._uv1,e2._uv2,scale);

                Span    span(x1,x2,y,color1,color2,uvStart,uvEnd);
                drawSpan(span,image);

                scale   +=  step;
                scale1  +=  step1;

            }
        }

        void    drawSpan(const Span& span,Image* image)
        {
            float   length  =   span._xEnd - span._xStart;
            float   scale   =   0;
            float   step    =   1.0f/length;
            for (int x = span._xStart ; x < span._xEnd; ++ x)
            {
                Rgba    color   =   colorLerp(span._colorStart,span._colorEnd,scale);

                float2  uv      =   uvLerp(span._uvStart,span._uvEnd,scale);

                Rgba    pixel   =   image->pixelUV(uv.x,uv.y);

                Rgba    dst     =   color + pixel;
                scale   +=  step;

                setPixel(x,span._y,dst);
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

        inline  Rgba    getPixel(unsigned x,unsigned y)
        {
            return  Rgba(_buffer[y * _width + x]);
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
