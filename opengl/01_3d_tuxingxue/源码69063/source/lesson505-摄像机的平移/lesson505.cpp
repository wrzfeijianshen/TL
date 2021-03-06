#include <windows.h>
#include <tchar.h>

#include "Raster.h"

#include "CELLTimestamp.hpp"
#include "CELLCamera.hpp"

CELL::CELLCamera    g_camera;
CELL::int2          g_rButtonDown;
bool                g_rButtonFlag   =   false;
CELL::int2          g_lButtonDown;
bool                g_lButtonFlag   =   false;


CELL::float3  calcIntersectPoint( CELL::Ray& ray )
{
    CELL::float3    pos     =   ray.getOrigin();
    float           tm      =   abs((pos.y) / ray.getDirection().y); 
    CELL::float3    target  =   ray.getPoint(tm);
    return  CELL::float3(target.x,0,target.z);
}



LRESULT CALLBACK    windowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
    case WM_SIZE:
        break;
    case WM_LBUTTONDOWN:
        {
            g_lButtonDown.x =   LOWORD(lParam);
            g_lButtonDown.y =   HIWORD(lParam);
            g_lButtonFlag   =   true;
        }
        break;
    case  WM_LBUTTONUP:
        {
            g_lButtonFlag   =   false;
        }
        break;
    case WM_MOUSEMOVE:
        {
            int x   =   LOWORD(lParam);
            int y   =   HIWORD(lParam);
            if (g_rButtonFlag)
            {
                int     offsetX =   x - g_rButtonDown.x;
                int     offsetY =   y - g_rButtonDown.y;
                g_camera.rotateViewY(offsetX);
                g_camera.rotateViewX(offsetY);
                g_rButtonDown.x =   x;
                g_rButtonDown.y =   y;
            }
            if (g_lButtonFlag)
            {
                /**
                *   首先计算出来一个像素和当前场景的比例
                */
                CELL::Ray   ray0    =   g_camera.createRayFromScreen(x,y);
                CELL::Ray   ray1    =   g_camera.createRayFromScreen(g_lButtonDown.x,g_lButtonDown.y);

                CELL::float3  pos0    =   calcIntersectPoint(ray0);
                CELL::float3  pos1    =   calcIntersectPoint(ray1);

                CELL::float3  offset  =   pos1 - pos0;
             
                g_lButtonDown   =   CELL::int2(x,y);

                CELL::float3  newEye  =   g_camera.getEye() + offset;
                CELL::float3  newTgt  =   g_camera.getTarget() + offset;


                g_camera.setEye(newEye);
                g_camera.setTarget(newTgt);

                g_camera.update();
            }
        }
        break;
    case WM_RBUTTONDOWN:
        {
            g_rButtonDown.x =   LOWORD(lParam);
            g_rButtonDown.y =   HIWORD(lParam);
            g_rButtonFlag   =   true;
        }
        break;
    case WM_RBUTTONUP:
        {
            g_rButtonFlag   =   false;
        }
        break;
    case WM_MOUSEWHEEL:
        {
            short   delta   =   GET_WHEEL_DELTA_WPARAM(wParam);
            if (delta > 0)
            {
                float   len =   CELL::length(g_camera._eye-g_camera._target);
                        len *=  1.2f;
                g_camera._eye   =   g_camera._target - g_camera._dir * len;
            }
            else
            {
                float   len =   CELL::length(g_camera._eye-g_camera._target);
                        len *=  0.9f;
                g_camera._eye   =   g_camera._target - g_camera._dir * len;
            }
            g_camera.update();
        }
        break;
    case WM_CLOSE:
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        break;
    }

    return  DefWindowProc( hWnd, msg, wParam, lParam );
}


void  getResourcePath(HINSTANCE hInstance,char pPath[1024])
{
    char    szPathName[1024];
    char    szDriver[64];
    char    szPath[1024];
    GetModuleFileNameA(hInstance,szPathName,sizeof(szPathName));
    _splitpath( szPathName, szDriver, szPath, 0, 0 );
    sprintf(pPath,"%s%s",szDriver,szPath);
}

int     WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd )
{
    //  1   注册窗口类
    ::WNDCLASSEXA winClass;
    winClass.lpszClassName  =   "Raster";
    winClass.cbSize         =   sizeof(::WNDCLASSEX);
    winClass.style          =   CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS;
    winClass.lpfnWndProc    =   windowProc;
    winClass.hInstance      =   hInstance;
    winClass.hIcon	        =   0;
    winClass.hIconSm	    =   0;
    winClass.hCursor        =   LoadCursor(NULL, IDC_ARROW);
    winClass.hbrBackground  =   (HBRUSH)(BLACK_BRUSH);
    winClass.lpszMenuName   =   NULL;
    winClass.cbClsExtra     =   0;
    winClass.cbWndExtra     =   0;
    RegisterClassExA(&winClass);

    //  2 创建窗口
    HWND    hWnd   =   CreateWindowExA(
        NULL,
        "Raster",
        "Raster",
        WS_OVERLAPPEDWINDOW,
        0,
        0,
        800,
        600, 
        0, 
        0,
        hInstance, 
        0
        );

    UpdateWindow( hWnd );
    ShowWindow(hWnd,SW_SHOW);

    RECT    rt      =   {0};
    GetClientRect(hWnd,&rt);

    int     width   =   rt.right - rt.left;
    int     height  =   rt.bottom - rt.top;
    void*   buffer  =   0;

    HDC     hDC     =   GetDC(hWnd);
    HDC     hMem    =   ::CreateCompatibleDC(hDC);

    BITMAPINFO	bmpInfor;
    bmpInfor.bmiHeader.biSize			=	sizeof(BITMAPINFOHEADER);
    bmpInfor.bmiHeader.biWidth			=	width;
    bmpInfor.bmiHeader.biHeight			=	-height;
    bmpInfor.bmiHeader.biPlanes			=	1;
    bmpInfor.bmiHeader.biBitCount		=	32;
    bmpInfor.bmiHeader.biCompression	=	BI_RGB;
    bmpInfor.bmiHeader.biSizeImage		=	0;
    bmpInfor.bmiHeader.biXPelsPerMeter	=	0;
    bmpInfor.bmiHeader.biYPelsPerMeter	=	0;
    bmpInfor.bmiHeader.biClrUsed		=	0;
    bmpInfor.bmiHeader.biClrImportant	=	0;

    HBITMAP	hBmp    =	CreateDIBSection(hDC,&bmpInfor,DIB_RGB_COLORS,(void**)&buffer,0,0);
    SelectObject(hMem,hBmp);

    char    szPath[1024];
    getResourcePath(0,szPath);

    char    szImage[1024];
    sprintf(szImage,"%s/image/bg.png",szPath);
    CELL::Image*    image   =   CELL::Image::loadFromFile(szImage);

    sprintf(szImage,"%s/image/1.jpg",szPath);
    CELL::Image*    image1  =   CELL::Image::loadFromFile(szImage);


    CELL::Raster    raster(width,height,buffer);

    g_camera.setViewSize(width,height);
    g_camera.perspective(60,(float)(width)/(float)(height),0.1,10000);
    g_camera.update();

    raster.setViewPort(0,0,width,height);
    raster.setPerspective(60,(float)(width)/(float)(height),0.1,10000);


    struct  Vertex
    {
        float       x,y,z;
        float       u,v;
        CELL::Rgba  color;
    };

    MSG     msg =   {0};
    while(true)
    {
        if (msg.message == WM_DESTROY  
            ||msg.message == WM_CLOSE
            ||msg.message == WM_QUIT)
        {
            break;
        }
        if( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
        { 
            TranslateMessage( &msg );
            DispatchMessage( &msg );
        }
        raster.clear();

        CELL::CELLTimestamp tms;

        tms.update();
        double  mis =   tms.getElapsedTimeInMicroSec();

        char    szBuf[128];
        sprintf(szBuf,"%f ",mis);

        raster.setView(g_camera.getView());

        Vertex    vertexs[]   =   
        {
            {-1, 0,   1,  0,  0,    CELL::Rgba(255,0,0)},
            { 1, 0,   1,  1,  0,    CELL::Rgba(0,255,0)},
            { 1, 0,  -1,  1,  1,    CELL::Rgba(0,0,255)},

            {-1, 0,   1,  0,  0,    CELL::Rgba(255,0,0)},
            { 1, 0,  -1,  1,  1,    CELL::Rgba(0,0,255)},
            {-1, 0,  -1,  0,  1,    CELL::Rgba(255,255)},
        };

        for (int i = 0 ;i  < 6 ; ++ i)
        {
            vertexs[i].x    *=   100;
            vertexs[i].z    *=   100;

            vertexs[i].u    *=   10;
            vertexs[i].v    *=   10;
        }

        image1->setWrapType(0);

        raster.bindTexture(image1);

        raster.vertexPointer(2,CELL::DT_FLOAT,      sizeof(Vertex),&vertexs[0].x);
        raster.textureCoordPointer(2,CELL::DT_FLOAT,sizeof(Vertex),&vertexs[0].u);
        raster.colorPointer(4,CELL::DT_BYTE,        sizeof(Vertex),&vertexs[0].color);

        raster.drawArrays(CELL::DM_TRIANGES,0,6);

        //TextOut(hMem,10,10,szBuf,strlen(szBuf));
        BitBlt(hDC,0,0,width,height,hMem,0,0,SRCCOPY);

    }


    delete  image;
    delete  image1;

    return  0;
}