
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
        _matProj                    =   CELL::matrix4(1);
        _matView                    =   CELL::matrix4(1);
    }

    Raster::~Raster( void )
    {
    }

    void Raster::clear()
    {
        memset(_buffer,0,_width * _height * sizeof(Rgba));
    }

    void Raster::drawImage( int startX,int startY,const Image* image )
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

    void Raster::drawArrays( DRAWMODE pri,int start,int count )
    {
        if (_poitionPointer._data == 0)
        {
            return;
        }

        DateElementDes  colorPointerdesc    =   _colorPointer;
        DateElementDes  uvPointerdesc       =   _uvPointer;
        if (colorPointerdesc._data == 0)
        {
            colorPointerdesc    =   _defaultColorPointer;
        }
        if (uvPointerdesc._data == 0)
        {
            uvPointerdesc       =   _defaultUVPointer;
        }
        char*   posData =   (char*)_poitionPointer._data;
        char*   cData   =   (char*)colorPointerdesc._data;
        char*   uvData  =   (char*)uvPointerdesc._data;

        _mvp    =   _matProj * _matView;
        matrix4 matMV   =   _matProj * _matView;
        matrix4 matRMVP =   matMV.transpose();

        _frust.loadFrustum(matRMVP);

        for(int i = start ;i < start + count; i += 3)
        {
            float*  fData   =   (float*)posData;
            float3  p01 (fData[0],fData[1],fData[2]);

            posData +=  _poitionPointer._stride;
            fData   =   (float*)(posData);
            

            float3  p11 (fData[0],fData[1],fData[2]);
            posData +=  _poitionPointer._stride;
            fData   =   (float*)(posData);
            

            float3  p21 (fData[0],fData[1],fData[2]);
            posData +=  _poitionPointer._stride;
            //! 这里注意需要做判断,裁减计算

            p01     =   p01 * _matModel;
            p11     =   p11 * _matModel;
            p21     =   p21 * _matModel;

            if(!(_frust.pointInFrustum(p01) ||  _frust.pointInFrustum(p11) || _frust.pointInFrustum(p21)))
            {
                continue;
            }
            
            p11     =   piplineTransform(p11);
            p01     =   piplineTransform(p01);
            p21     =   piplineTransform(p21);

            //! 转化为屏幕坐标
            int2    p0(p01.x,p01.y);
            int2    p1(p11.x,p11.y);
            int2    p2(p21.x,p21.y);

            Rgba*   pColor   =   (Rgba*)cData;
            Rgba    c0 (*pColor);
            cData   +=  _colorPointer._stride;
            Rgba    c1 (*(Rgba*)cData);
            cData   +=  _colorPointer._stride;
            Rgba    c2 (*(Rgba*)cData);
            cData   +=  _colorPointer._stride;

            float*  pUV     =   (float*)uvData;
            float2  uv0 (pUV[0],pUV[1]);
            uvData  +=  _uvPointer._stride;
            pUV     =   (float*)uvData;
            float2  uv1(pUV[0],pUV[1]);
            uvData  +=  _uvPointer._stride;
            pUV     =   (float*)uvData;
            float2  uv2(pUV[0],pUV[1]);
            uvData  +=  _uvPointer._stride;

            //! 这里可以做判断,如果三角形不在当前区域内部,则不进行绘制


            Ege eges[3]  =   
            {
                Ege(p0.x,p0.y,c0,  uv0, p1.x,p1.y,c1,  uv1),
                Ege(p1.x,p1.y,c1,  uv1, p2.x,p2.y,c2,  uv2),
                Ege(p2.x,p2.y,c2,  uv2, p0.x,p0.y,c0,  uv0),
            };
            drawTrianle(eges);

            if (_colorPointer._data == 0)
            {
                cData   =   (char*)colorPointerdesc._data;
            }
            if (_uvPointer._data == 0 )
            {

                uvData  =   (char*)uvPointerdesc._data;
            }
        }
    }

    void Raster::bindTexture( Image* image )
    {
        _texture    =   image;
    }

    void Raster::textureCoordPointer( int size,DATETYPE type,int stride,const void* data )
    {
        _uvPointer._size        =   size;
        _uvPointer._type        =   type;
        _uvPointer._stride      =   stride;
        _uvPointer._data        =   data;
    }

    void Raster::colorPointer( int size,DATETYPE type,int stride,const void* data )
    {
        _colorPointer._size     =   size;
        _colorPointer._type     =   type;
        _colorPointer._stride   =   stride;
        _colorPointer._data     =   data;
    }

    void Raster::vertexPointer( int size,DATETYPE type,int stride,const void* data )
    {
        _poitionPointer._size   =   size;
        _poitionPointer._type   =   type;
        _poitionPointer._stride =   stride;
        _poitionPointer._data   =   data;
    }

    

    void Raster::loadMatrix( const CELL::matrix4& mat )
    {
        _matModel   =   mat;
    }

    void Raster::loadIdentity()
    {
        _matModel   =   CELL::matrix4(1);
    }
    
    void Raster::loadProjMatrix( const CELL::matrix4& mat )
    {
        _matProj    =   mat;
    }
    void Raster::loadProjIdentity( const CELL::matrix4& mat )
    {
        _matProj    =   CELL::matrix4(1);
    }
    

    void Raster::loadViewMatrix( const CELL::matrix4& mat )
    {
        _matView    =   mat;
    }
    void Raster::loadViewIdentity( const CELL::matrix4& mat )
    {
        _matView    =   CELL::matrix4(1);
    }

    void Raster::setPerspective( float fovy, float aspect, float zNear, float zFar )
    {
        _matProj    =   CELL::perspective<float>(fovy,aspect,zNear,zFar);
    }

    void Raster::lookat( float3 const & eye,float3 const & center,float3 const & up )
    {
        _matView    =   CELL::lookAt(eye,center,up);
    }

    void Raster::setViewPort( int x,int y,int w,int h )
    {
        _viewPort.x =   w;
        _viewPort.y =   h;
    }

}