
#include "Raster.h"

namespace   CELL
{
    Raster::Raster( int w,int h,void* buffer )
    {
        _width  =   w;
        _height =   h;
        _buffer =   (Rgba*)buffer;
    }

    Raster::~Raster( void )
    {

    }

    void Raster::clear()
    {
        memset(_buffer,0,_width * _height * sizeof(Rgba));
    }

    void Raster::drawPoint( int x,int y, Rgba color,int ptSize )
    {
        switch(ptSize)
        {
        case 1:
            setPixel(x,y,color);
            break;
        case 2:
            setPixel(x + 0, y + 0,color);
            setPixel(x + 1, y + 0,color);
            setPixel(x + 0, y + 1,color);
            setPixel(x + 1, y + 1,color);
            break;
        case 3:

            setPixel(x - 1, y - 1,color);
            setPixel(x + 0, y - 1,color);
            setPixel(x + 1, y - 1,color);

            setPixel(x - 1, y + 0,color);
            setPixel(x + 0, y + 0,color);
            setPixel(x + 1, y + 0,color);

            setPixel(x - 1, y + 1,color);
            setPixel(x + 0, y + 1,color);
            setPixel(x + 1, y + 1,color);

            break;
        }
    }

    void Raster::drawLine( float2 pt1,float2 pt2,Rgba color1,Rgba color2 )
    {
        float   xOffset =   pt1.x - pt2.x;
        float   yOffset =   pt1.y - pt2.y;

        if (xOffset == 0 && yOffset == 0)
        {
            setPixel(pt1.x,pt1.y,color1);
        }

        if (fabs(xOffset) > fabs(yOffset))
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
            
            float   lenth   =   xMax - xMin;
            float   slope   =   yOffset / xOffset;
            for (float x = xMin; x <= xMax ; x += 1.0f)
            {
                float   y       =   pt1.y + (x - pt1.x) * slope;
                float   scaler  =   (x - xMin)/lenth;
                Rgba    color   =   colorLerp(color1,color2,scaler);
                setPixel(x,y,color);
            }
        }
        else
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

            float   lenth   =   yMax - yMin;
            float   slope   =   xOffset / yOffset;
            for (float y = yMin; y <= yMax ; y += 1.0f)
            {
                float   x       =   pt1.x + (y - pt1.y) * slope;
                float   scaler  =   (y - yMin)/lenth;
                Rgba    color   =   colorLerp(color1,color2,scaler);
                setPixel(x,y,color);
            }
        }
    }

    void Raster::drawArrays( DRAWMODE mode,const float2* points,int count )
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

    void Raster::drawFilleRect( int startX,int startY,int w,int h )
    {
        int left    =   tmax<int>(startX,0);
        int top     =   tmax<int>(startY,0);

        int right   =   tmin<int>(startX + w,_width);
        int bottom  =   tmin<int>(startY + h,_height);

        for (int x = left ; x <  right ; ++ x)
        {
            for (int y = top ; y <  bottom ; ++ y)
            {
                setPixelEx(x,y,_color);
            }
        }
    }

    void Raster::drawRect( const int2* points,const Rgba* colors )
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

}