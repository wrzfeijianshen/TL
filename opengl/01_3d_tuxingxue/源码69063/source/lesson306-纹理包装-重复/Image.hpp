#pragma once


namespace   CELL
{
    class   Image
    {
    protected:
        int     _width;
        int     _height;
        uint*   _pixel;
    public:
        Image(int w,int h,void* data)
        {
            if (w == 0 || h == 0 || data== 0)
            {
                _width  =   0;
                _height =   0;
                _pixel  =   0;
            }
            else
            {
                _width  =   w;
                _height =   h;
                _pixel  =   new uint[w * h];
                memcpy(_pixel,data,w * h * sizeof(uint));
            }
        }
        ~Image()
        {
            delete []_pixel;
        }

        int     width() const
        {
            return  _width;
        }
        int     height() const
        {
            return  _height;
        }

        Rgba    pixelAt(int x,int y) const
        {
            return  Rgba(_pixel[y * _width + x]);
        }

        Rgba    pixelUV(float u,float v)
        {
            float x   =   u * _width;
            float y   =   v * _height;

            return  pixelAt((unsigned)(x)%_width,(unsigned)(y)%_height);

        }

    public:
        static  Image*  loadFromFile(const char*);
    };
}