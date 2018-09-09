#pragma once


namespace   CELL
{
    class   Image
    {
    protected:
        int     _width;
        int     _height;
        uint*   _pixel;
        int     _wrapType;
    public:
        Image(int w,int h,void* data)
        {
            _wrapType   =   0;
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


        void    setWrapType(int type)
        {
            _wrapType   =   type;
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
            if (_wrapType == 0)
            {
                return  pixelAt((unsigned)(x)%_width,(unsigned)(y)%_height);
            }
            else
            {
                if (x >= _width)
                {
                    x   =   _width - 1;
                }
                if (y >= _height)
                {
                    y   =   _height - 1;
                }
                return  pixelAt(x,y);
            }
        }

    public:
        static  Image*  loadFromFile(const char*);
    };
}