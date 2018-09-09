
#include "Raster.h"
#include "FreeImage.h"

namespace   CELL
{
    Image*    Image::loadFromFile(const char* fileName)
    {
        //1 获取图片格式
        FREE_IMAGE_FORMAT fifmt = FreeImage_GetFileType(fileName, 0);
        if (fifmt == FIF_UNKNOWN)
        {
            return  0;
        }
        //2 加载图片
        FIBITMAP    *dib = FreeImage_Load(fifmt, fileName,0);

        FREE_IMAGE_COLOR_TYPE type    =   FreeImage_GetColorType(dib);

        //! 获取数据指针
        FIBITMAP*   temp    =   dib;
        dib =   FreeImage_ConvertTo32Bits(dib);
        FreeImage_Unload(temp);

        BYTE*   pixels  =   (BYTE*)FreeImage_GetBits(dib);
        int     width   =   FreeImage_GetWidth(dib);
        int     height  =   FreeImage_GetHeight(dib);

        int     pitch   =   width*4;
        BYTE*   row     =   new BYTE[width*4];
        for(int j = 0; j < height / 2; j++) 
        {
            memcpy(row,pixels + j * pitch,pitch );

            memcpy(pixels + j * pitch,pixels + (height - j - 1) * pitch,pitch );

            memcpy(pixels + (height - j - 1) * pitch,row,pitch );

        }
        delete  []row;

        Image*  image   =   new Image(width,height,pixels);
        FreeImage_Unload(dib);

        return  image;
    }

    Raster::Raster( int w,int h,void* buffer )
    {
        _texture        =   0;
        _width          =   w;
        _height         =   h;
        _buffer         =   (uint*)buffer;
        memset(&_poitionPointer,0,  sizeof(_poitionPointer));
        memset(&_colorPointer,  0,  sizeof(_colorPointer));
        memset(&_uvPointer,     0,  sizeof(_uvPointer));

        _defaultColorPointer._size  =   4;
        _defaultColorPointer._type  =   DT_BYTE;
        _defaultColorPointer._stride=   sizeof(Rgba);
        _defaultColorPointer._data  =   _defaultColorArray;

        _defaultUVPointer._size     =   2;
        _defaultUVPointer._type     =   DT_FLOAT;
        _defaultUVPointer._stride   =   sizeof(float2);
        _defaultUVPointer._data     =   _detaultUVArray;

        _matModel                   =   CELL::matrix4(1);
    }

    Raster::~Raster( void )
    {
    }

    void Raster::clear()
    {
        memset(_buffer,0,_width * _height * sizeof(Rgba));
    }
}