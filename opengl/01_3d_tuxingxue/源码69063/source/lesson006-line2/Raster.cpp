
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
}