
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

    void Raster::drawLine( float2 pt1,float2 pt2,Rgba color )
    {
        float   xOffset =   pt1.x - pt2.x;
        float   yOffset =   pt1.y - pt2.y;

        if (xOffset == 0)
        {
            float   slope   =   yOffset / xOffset;
            for (float y = pt1.y; y <= pt2.y ; y += 1.0f)
            {
                setPixel(pt2.x,y,color);
            }
        }
        else if(yOffset == 0)
        {
            float   slope   =   yOffset / xOffset;
            for (float x = pt1.x; x <= pt2.x ; x += 1.0f)
            {
                setPixel(x,pt2.y,color);
            }
        }
        else
        {
            float   slope   =   yOffset / xOffset;
            for (float x = pt1.x; x <= pt2.x ; x += 1.0f)
            {
                float   y   =   pt1.y + (x - pt1.x) * slope;
                setPixel(x,y,color);
            }
        }
    }

}