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

        void    drawLine(float2 pt1,float2 pt2,Rgba color)
        {
            float   xOffset =   pt1.x - pt2.x;
            float   yOffset =   pt1.y - pt2.y;

            if (xOffset == 0 && yOffset == 0)
            {
                setPixel(pt1.x,pt1.y,color);
            }

            if (xOffset == 0)
            {
                float   yMin;
                float   yMax;
                if (pt1.y < pt2.y)
                {
                    yMin    =   pt1.y;
                    yMax    =   pt2.y;
                }
                else
                {
                    yMin    =   pt2.y;
                    yMax    =   pt1.y;
                }

                float   slope   =   yOffset / xOffset;
                for (float y = yMin; y <= yMax ; y += 1.0f)
                {
                    setPixel(pt2.x,y,color);
                }
            }
            else if(yOffset == 0)
            {
                float   xMin;
                float   xMax;
                if (pt1.x < pt2.x)
                {
                    xMin    =   pt1.x;
                    xMax    =   pt2.x;
                }
                else
                {
                    xMin    =   pt2.x;
                    xMax    =   pt1.x;
                }

                float   slope   =   yOffset / xOffset;
                for (float x = xMin; x <= xMax ; x += 1.0f)
                {
                    setPixel(x,pt2.y,color);
                }
            }
            else
            {

                if (fabs(xOffset) > fabs(yOffset))
                {
                    float   slope   =   yOffset / xOffset;

                    float   xMin;
                    float   xMax;
                    if (pt1.x < pt2.x)
                    {
                        xMin    =   pt1.x;
                        xMax    =   pt2.x;
                    }
                    else
                    {
                        xMin    =   pt2.x;
                        xMax    =   pt1.x;
                    }

                    for (float x = xMin; x <= xMax ; x += 1.0f)
                    {
                        float   y   =   pt1.y + (x - pt1.x) * slope;
                        setPixel(x,y,color);
                    }
                }
                else
                {
                    float   slope   =   xOffset / yOffset;

                    float   yMin;
                    float   yMax;
                    if (pt1.y < pt2.y)
                    {
                        yMin    =   pt1.y;
                        yMax    =   pt2.y;
                    }
                    else
                    {
                        yMin    =   pt2.y;
                        yMax    =   pt1.y;
                    }
                    for (float y = pt1.y; y <= pt2.y ; y += 1.0f)
                    {
                        float   x   =   pt1.x + (y - pt1.y) * slope;
                        setPixel(pt2.x,y,color);
                    }
                }
            }
        }

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
