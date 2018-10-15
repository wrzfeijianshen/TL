#include "XqWindow.h"
#include <gdiplus.h>
#include <math.h>

#include <string>
#include <iostream>
#include <sstream>

using namespace Gdiplus;
using namespace std;

#pragma comment(lib, "GdiPlus.lib")

int width, height;
ULONG_PTR token;

// wchar_t to string
void Wchar_tToString(std::string& szDst, wchar_t *wchar)
{
	wchar_t * wText = wchar;
	DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, NULL, 0, NULL, FALSE);// WideCharToMultiByte的运用
	char *psText;  // psText为char*的临时数组，作为赋值给std::string的中间变量
	psText = new char[dwNum];
	WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, psText, dwNum, NULL, FALSE);// WideCharToMultiByte的再次运用
	szDst = psText;// std::string赋值
	delete[]psText;// psText的清除
}

// string to wstring
void StringToWstring(std::wstring& szDst, std::string str)
{
	std::string temp = str;
	int len = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)temp.c_str(), -1, NULL, 0);
	wchar_t * wszUtf8 = new wchar_t[len + 1];
	memset(wszUtf8, 0, len * 2 + 2);
	MultiByteToWideChar(CP_ACP, 0, (LPCSTR)temp.c_str(), -1, (LPWSTR)wszUtf8, len);
	szDst = wszUtf8;
	std::wstring r = wszUtf8;
	delete[] wszUtf8;
}


CXqWindow::CXqWindow(HINSTANCE hInst)
	:m_HWnd(NULL),
	m_HInstance(hInst),
	m_IPosX(0),
	m_IPosY(0),
	m_IWidth(500),
	m_IHight(500)
{
	memset(&m_WClassEx, 0, sizeof(m_WClassEx));

	GdiplusStartupInput gdipinput;
	GdiplusStartup(&token, &gdipinput, NULL);
}

CXqWindow::~CXqWindow()
{
	if (this->m_HWnd != NULL && ::IsWindow(this->m_HWnd)) // C++对象被销毁之前，销毁窗口对象
	{
		::DestroyWindow(this->m_HWnd);
	}
	GdiplusShutdown(token);
}

BOOL CXqWindow::OnInitDialog(WPARAM wParam, LPARAM lParam)
{
	return TRUE;
}

HWND CXqWindow::GetHandle()
{
	return this->m_HWnd;
}
void Printf(HDC hdc)
{
	WCHAR buf[128];
	int len;
	len = wsprintfW(buf, L"width:%d height:%d\n", width, height);

	SolidBrush b(Color(255, 100, 200, 150));
	HBITMAP bg = CreateCompatibleBitmap(hdc, width, height);
	HDC memdc = CreateCompatibleDC(hdc);
	SelectObject(memdc, bg);

	FontFamily fm(L"Consolas");
	Font f(&fm, 12, 2, UnitPoint);

	Graphics mg(memdc);
	mg.SetSmoothingMode(SmoothingModeHighQuality);
	mg.Clear(Color(255, 128, 128, 128));

	mg.DrawString(buf, len, &f, PointF(0.0, 0.0), &b);

	if (!BitBlt(hdc, 0, 0, width, height, memdc, 0, 0, SRCCOPY))
		MessageBox(NULL, L"BitBlt failed!", L"warning", MB_ICONWARNING);

	DeleteObject(bg);
	DeleteDC(memdc);
}

void PrintString(HDC &hdc,wstring str)
{
	Graphics graphics(hdc);
	Pen pen(Color(255, 0, 0, 255));
	SolidBrush brush(Color(255, 0, 0, 255));
	FontFamily fontFamily(L"宋体");
	Font font(&fontFamily, 24, FontStyleRegular, UnitPixel);
	graphics.DrawString(str.c_str(), -1, &font, PointF(5.0, 500.0), &brush);

}

void CXqWindow::OnDraw(HDC hdc)
{
#if 0 ///<-- 2-3 输出字体
	Graphics graphics(hdc);
	Pen pen(Color(255, 0, 0, 255));
	SolidBrush brush(Color(255, 0, 0, 255));
	FontFamily fontFamily(L"宋体");
	Font font(&fontFamily,24,FontStyleRegular,UnitPixel);
	graphics.DrawString(L"GDI+ 实例1", -1, &font, PointF(20.0, 20.0),&brush);
#endif

	
#if 0 ///<-- 2-5 在打印机设备中输出
	DOCINFO docinfo;
	ZeroMemory(&docinfo, sizeof(DOCINFO));// 清空文档信息
	docinfo.cbSize = sizeof(DOCINFO);
	docinfo.lpszDocName = L"GDIPlusPrint";// 文档名称

	PRINTDLG printDlg;// 建立打印对话
	ZeroMemory(&printDlg, sizeof(PRINTDLG));
	printDlg.lStructSize = sizeof(PRINTDLG);
	printDlg.Flags = PD_RETURNDC;// 返回dc

	if (!PrintDlg(&printDlg))
	{
		MessageBox(NULL, L"建立打印对话框失败", L"warning", MB_ICONWARNING);
		return;
	}
	else
	{
		// 开始记录文档
		StartDoc(printDlg.hDC, &docinfo);
		StartPage(printDlg.hDC);

		Graphics graphics(printDlg.hDC);// 使用打印机设备环境句柄建立绘图平面类

		// 以下输出都在打印机设备句柄中进行
		
		Image image(L"./gidplus_data/test.bmp");// 加载图片
		graphics.DrawImage(&image, 0.0f, 0.0f);

		Pen pen(Color(255, 0, 0, 0));
		graphics.DrawRectangle(&pen, 200, 500, 200, 150);
		graphics.DrawEllipse(&pen, 200, 500, 400, 650);
		graphics.DrawLine(&pen, 200, 500, 400, 650);

		// 开始打印
		EndPage(printDlg.hDC);
		EndDoc(printDlg.hDC);
	}

	// 释放打印资源
	if (printDlg.hDevMode)
	{
		GlobalFree(printDlg.hDevMode);
	}

	if (printDlg.hDevNames)
	{
		GlobalFree(printDlg.hDevNames);
	}
	if (printDlg.hDC)
	{
		GlobalFree(printDlg.hDC);
	}
#endif
	
#if 0 ///<-- 2-6 绘制直线
	Graphics graphics(hdc);
	Pen blackPen(Color(255, 0, 0, 0), 3);

	// 点的位置
	PointF point1(10.0f,10.0f);
	PointF point2(10.0f, 100.0f);
	PointF point3(50.0f, 50.0f);
	PointF point4(10.0f, 10.0f);
	PointF points[4] = { point1, point2, point3, point4 };
	PointF * pPoints = points;

	// 绘制多条线
	graphics.DrawLines(&blackPen, pPoints, 4);
	Pen redPen(Color(255, 255, 0, 0), 3);

	graphics.DrawLine(&redPen, PointF(20.0f, 100.0f), PointF(100.0f, 20.0f));
	graphics.DrawLine(&redPen, 50, 20, 100, 100);
#endif
	
#if 0 ///<-- 2-7 绘制矩形
	Graphics graphics(hdc);
	Pen blackPen(Color(255, 0, 0, 0),3);

	// 定义矩形
	RectF rect1(10.0f,10.0f,100.0f,50.0f);
	RectF rect2(40.0f, 40.0f, 100.0f, 50.0f);
	RectF rect3(80.0f, 4.0f, 50.0f, 100.0f);
	RectF rects[] = { rect1, rect2, rect3 };
	RectF * pRects = rects;
	//graphics.DrawRectangles(&blackPen,rects,3);
	graphics.DrawRectangles(&blackPen,pRects,3);
	Pen redPen(Color(255, 255, 0, 0), 3);
	RectF rect4(20.0f, 20.0f, 50.0f, 100.0f);
	graphics.DrawRectangle(&redPen, rect4);
#endif

#if 0 ///<-- 2-8 绘制简单曲线和贝塞尔曲线
	#if 0  // DrawCurve 绘制曲线
	Graphics graphics(hdc);
	Pen greenPen(Color::Green, 3);
	Pen redPen(Color::Red, 3);

	// 定义曲线经过的点
	Point point1(100, 100);
	Point point2(200,50);
	Point point3(700, 10);
	Point point4(500, 100);

	Point curvePoints[7] = { point1, point2, point3, point4 };
	// 绘制曲线
	graphics.DrawCurve(&greenPen, curvePoints, 7);
	
	// 使用红色画笔绘制弯曲强度为1.3的曲线
	graphics.DrawCurve(&redPen, curvePoints, 7, 1.3f);

	// 绘制曲线的定义点(红色)
	SolidBrush redBrush(Color::Red);
	graphics.FillEllipse(&redBrush, Rect(95, 95, 10, 10));
	graphics.FillEllipse(&redBrush, Rect(195, 75, 10, 10));
	graphics.FillEllipse(&redBrush, Rect(395, 5, 10, 10));
	graphics.FillEllipse(&redBrush, Rect(795, 95, 10, 10));
	#endif

	#if 0 // 使用DrawColosedCurve绘制曲线
	Graphics graphics(hdc);
	Pen greenPen(Color::Green, 3);
	PointF point1(100.f, 100.f);
	PointF point2(200.f, 50.f);
	PointF point3(400.f, 10.f);
	PointF point4(500.f, 100.f);
	PointF point5(600.f, 200.f);
	PointF point6(700.f, 400.f);
	PointF point7(500.f, 500.f);
	PointF curvePoints[7] = { point1, point2, point3, point4, point5, point6, point7 };
	graphics.DrawClosedCurve(&greenPen, curvePoints, 7);
	// 绘制曲线的定义点(红点)
	SolidBrush redBrush(Color::Red);
	graphics.FillEllipse(&redBrush, Rect(95, 95, 10, 10));
	graphics.FillEllipse(&redBrush, Rect(795, 95, 10, 10));
	graphics.FillEllipse(&redBrush, Rect(795, 495, 10, 10));
	graphics.FillEllipse(&redBrush, Rect(195, 45, 10, 10));
	graphics.FillEllipse(&redBrush, Rect(395, 5, 10, 10));
	graphics.FillEllipse(&redBrush, Rect(595, 195, 10, 10));
	graphics.FillEllipse(&redBrush, Rect(695, 395, 10, 10));

	#endif
#endif

#if 0 ///<-- 2-9 绘制贝塞尔曲线
	// 贝塞尔曲线通过4点来指定曲线，两个端点和两个控制点，曲线连接两个端点，不通过控制点，控制点的位置控制曲线的弯曲方向。
	Graphics graphics(hdc);
	Pen greenPen(Color::Green);
	Pen redPen(Color::Red);

	// 定义曲线起点
	Point startPoint(100, 100);
	
	// 定义两个控制点
	Point contronlPoint1(200, 10);
	Point contronlPoint2(350, 50);

	// 定义曲线终点
	Point endPoint(500, 100);

	// 绘制上述四个点位置，起点红色，控制点绿色
	graphics.FillEllipse(&SolidBrush(Color::Red),100,100,10,10);
	graphics.FillEllipse(&SolidBrush(Color::Red), 500, 100, 10, 10);
	graphics.FillEllipse(&SolidBrush(Color::Green), 200, 10, 10, 10);
	graphics.FillEllipse(&SolidBrush(Color::Green), 350, 50, 10, 10);
	graphics.DrawBezier(&greenPen, startPoint, contronlPoint1, contronlPoint2, endPoint);// 绘制贝塞尔曲线
#endif
#if 0 ///<-- 2-10 绘制多边形
	Graphics graphics(hdc);
	Pen blackPen(Color(255, 0, 0, 0), 3);

	// 定义多边形端点
	Point point1(100, 100);
	Point point2(200, 130);
	Point point3(150, 200);
	Point point4(45, 200);
	Point point5(0, 130);
	Point points[5] = { point1, point2, point3, point4, point5 };
	
	// 绘制多边形
	graphics.DrawPolygon(&blackPen, points, 5);
#endif

#if 0 ///<-- 2-11 绘制弧线
	Graphics graphics(hdc);
	Pen redPen(Color::Red, 3);

	Rect ellipseRect(10, 10, 200, 100);
	REAL startAngle = 0.f;
	REAL sweepAngle = 90.f;
	// 绘制矩形
	graphics.DrawRectangle(&Pen(Color::Black, 3), ellipseRect);
	// 绘制弧线
	graphics.DrawArc(&redPen, ellipseRect, startAngle, sweepAngle);
#endif

#if 0 ///<-- 2-12 扇形绘制
	Graphics graphics(hdc);
	Pen blackPen(Color(255, 0, 0, 0), 3);

	// 定义扇形: 矩形 + 角度,角度，顺时针
	Rect ellipseRect(0, 0, 200, 100);
	REAL startAngle = 0.f;
	REAL sweepAngle = 45.f;
	
	// 绘制椭圆扇形(长短半径不相等)
	graphics.DrawPie(&blackPen, ellipseRect, startAngle, sweepAngle);
#endif

#if 0 ///<-- 2-13 填充区域
	// 先构造画刷，后进行区域填充
	Graphics graphics(hdc);
	SolidBrush bluePen(Color::Blue);// Color(255,0,0,255)
	// 曲线定义点
	PointF point1(100.f, 100.f);
	PointF point2(200.f, 50.f);
	PointF point3(250.f, 200.f);
	PointF point4(50.f, 150.f);
	PointF points[4] = { point1, point2, point3, point4 };
	
	// 填充区域
	graphics.FillClosedCurve(&bluePen, points, 4,FillModeAlternate,1.);
	
	// 绘制曲线定义点
	for (int i = 0; i < 4;i++)
	{
		graphics.FillEllipse(&SolidBrush(Color::Red), RectF(points[i].X - 5, points[i].Y - 5, 10, 10));
	}

	// 填充矩形
	Rect ellipseRect(10, 240, 200, 100);
	graphics.FillRectangle(&bluePen, ellipseRect);
#endif

#if 0 ///<-- 2-14 往镜框中添加照片 ---- 2-15 略,因源码中无图片，待学习整理

#endif
#if 0 ///<-- 2-16输出文本
	Graphics graphics(hdc);
	Font myFont(L"Arial", 26);
	RectF layoutRect(10.f, 10.f, 200.f, 50.f);

	// 设置水平居中和垂直居中
	StringFormat format;
	format.SetAlignment(StringAlignmentCenter);
	format.SetLineAlignment(StringAlignmentCenter);
	SolidBrush blackBrush(Color::Black);

	//string str("Hello GDI+");
	//wstring szDst;
	//StringToWstring(szDst,str);
	wstring szDst(L"你好 GDI+");

	// 绘制字
	graphics.DrawString(szDst.c_str(), szDst.size(), &myFont, layoutRect, &format, &blackBrush);
	// 绘制矩形
	graphics.DrawRectangle(&Pen(Color::Green, 3), layoutRect);
#endif

#if 0 ///<-- 3-1 画刷中构造纹理画笔
	// 画刷没有宽度，画笔有宽度
	Graphics graphics(hdc);

	// 加载纹理图片
	Image image(L"./gidplus_data/Texture.bmp");
	
	// 构造纹理画刷
	TextureBrush tBrush(&image);

	// 将画刷传入画笔的构造函数
	Pen texturePen(&tBrush, 30);
	graphics.DrawEllipse(&texturePen, 100, 20, 200, 100);
	cout << texturePen.GetWidth() << endl;

	wostringstream oss;
	oss << L"画笔宽度 : "<< texturePen.GetWidth();
	wstring str = oss.str();
	PrintString(hdc, str);// 输出到屏幕
#endif

#if 0 ///<-- 3-2 画笔的线型风格
	Graphics graphics(hdc);
	Pen blackPen(Color::Black, 5);
	
	// 常用的线型绘制直线
	/*
		DashStyleSolid,          // 0 实线
		DashStyleDash,           // 1 虚线
		DashStyleDot,            // 2 点线
		DashStyleDashDot,        // 3 点划线
		DashStyleDashDotDot,     // 4 双点划线
		DashStyleCustom          // 5 不规则自定义画笔线型
		*/
	int i = 0;
	for (i = 0; i < 6; i++)
	{
		blackPen.SetDashStyle((DashStyle)i);
		graphics.DrawLine(&blackPen, 10,30 * i + 20, 300, 30 * i + 20);
	}

	// 使用自定义线型
	REAL dashVals[4] =
	{
		5.f,// 线长5像素
		2.f,// 间断2线束
		15.f,// 线长15像素
		4.f// 间断4像素
	};

	blackPen.SetDashPattern(dashVals,4);
	blackPen.SetColor(Color::Red);
	graphics.DrawLine(&blackPen, 10, 30 * i + 40, 300, 30 * i + 40);

	i++;
	REAL dashVals2[6] =
	{
		5.f,// 线长5像素
		2.f,// 间断2线束
		10.f,// 线长5像素
		4.f,// 间断2像素
		8.f,// 线长5像素
		2.f// 间断2像素
	};

	blackPen.SetDashPattern(dashVals2, 6);// 获取线型风格
	blackPen.SetColor(Color::Red);
	graphics.DrawLine(&blackPen, 10, 30 * i + 40, 600, 30 * i + 40);

	wostringstream oss;
	oss << L"线型定义点总数 : " << blackPen.GetDashPatternCount();
	wstring str = oss.str();
	PrintString(hdc, str);// 输出到屏幕
#endif

#if 0 ///<-- 3-3 画笔的两种对齐方式
	// PenAlignment 居中和嵌入
	Graphics graphics(hdc);
	Pen redPen(Color::Red, 1);
	Pen blackPen(Color::Black, 8);
	Pen greenPen(Color::Green, 16);

	// 绘制正方形基线
	graphics.DrawRectangle(&redPen, 10, 10, 100, 100);
	graphics.DrawRectangle(&redPen, 120, 10, 100, 100);

	// 设置对齐方式为居中, 画圆
	graphics.DrawEllipse(&greenPen, 10, 10, 100, 100);
	graphics.DrawEllipse(&blackPen, 10, 10, 100, 100);

	// 设置对齐方式为Inset
	greenPen.SetAlignment(PenAlignmentInset);
	blackPen.SetAlignment(PenAlignmentInset);
	graphics.DrawEllipse(&greenPen, 120, 10, 100, 100);
	graphics.DrawEllipse(&blackPen, 120, 10, 100, 100);
#endif

#if 0 ///<-- 3-4 画笔的缩放和旋转变换
	Graphics graphics(hdc);

	// 构造宽度为5的蓝色画笔
	Pen pen(Color::Blue, 5);
	graphics.DrawEllipse(&pen, 50, 50, 200, 200);

	// 将画笔在垂直方向上扩充6倍，水平方向保持不变
	pen.ScaleTransform(1, 6);

	// 使用未经旋转处理的画笔画圆
	graphics.DrawEllipse(&pen, 300, 50, 200, 200);

	// 依次将画笔旋转60°、120°、180°
	pen.RotateTransform(60,MatrixOrderAppend);
	graphics.DrawEllipse(&pen, 600, 50, 200, 200);

	pen.RotateTransform(60, MatrixOrderAppend);
	graphics.DrawEllipse(&pen, 50, 300, 200, 200);

	pen.RotateTransform(60, MatrixOrderAppend);
	graphics.DrawEllipse(&pen, 300, 300, 200, 200);

	pen.RotateTransform(90, MatrixOrderAppend);
	graphics.DrawEllipse(&pen, 600, 300, 200, 200);
#endif

#if 0 ///<-- 3-5 画笔的自定义线帽
	Graphics graphics(hdc);
	GraphicsPath startPath, endPath;

	// 路径中添加一个矩形
	startPath.AddRectangle(Rect(-10, -5, 20, 10));

	// 构造结束点线帽的外观和箭头
	endPath.AddLine(0, -20, 10, 0);
	endPath.AddLine(0, -20, -10, 0);
	endPath.AddLine(0, -10, 10, 0);
	endPath.AddLine(0, -10, -10, 0);
	
	Rect rect(10, - 5, 20, 10);
	Pen pen(Color::Red, 2);
	// 将路径作为线帽外观
	CustomLineCap custCap(NULL, &startPath);
	CustomLineCap endCap(NULL, &endPath);

	// 设置画笔起点终点的自定义线帽
	pen.SetCustomStartCap(&custCap);
	pen.SetCustomEndCap(&endCap);
	graphics.DrawLine(&pen, 20, 30, 300, 30);

	//pen.SetStartCap(LineCapRound);
	//pen.SetEndCap(LineCapTriangle);
	//graphics.DrawLine(&pen, 20, 60, 200, 60);

	for (float i = 0.f; i < 6.28f;i+=0.15f)
	{
		graphics.DrawLine(&pen, 300.f, 300.f, 300+200.f*cos(i), 300+200*sin(i));
	}

#endif

#if 0 ///<-- 3-7 动态绘制含有透明度的线条
	Graphics graphics(hdc);
	Pen bluePen(Color::Blue);
	Pen redPen(Color::Red);

	// 绘制网线
	int y = 256;
	for (int x = 0; x < 256; x+=5)
	{
		graphics.DrawLine(&bluePen, 0, y, x, 0);
		graphics.DrawLine(&redPen, 256, y, x, 256);
		y -= 5;
		Sleep(50);// 延时看到效果
	}

	// 透明度从上到下递减
	for (y = 0; y < 256;y++)
	{
		Pen greenPen(Color(y,0,255,0));
		graphics.DrawLine(&greenPen,0,y,256, y);
		Sleep(20);// 延时看到效果
	}
	// 透明度从左到右递减
	for (int x = 0; x < 256; x++)
	{
		Pen greenPen(Color(x, 0, 255, 0));
		graphics.DrawLine(&greenPen, x, 100, x, 200);
		Sleep(20);// 延时看到效果
	}
#endif
#if 0 ///<-- 3-8 单色画刷填充区域
	// 画刷只是填充区域，无宽度长度而言
	Graphics graphics(hdc);
	SolidBrush greenBrush(Color::Green);
	PointF Point1(100.f, 100.f);
	PointF Point2(200.f, 50.f);
	PointF Point3(250.f, 200.f);
	PointF Point4(50.f, 150.f);
	PointF Point5(100.f, 100.f);

	// 填充闭合曲线
	PointF points[4] = { Point1, Point2, Point3, Point4 };
	graphics.FillClosedCurve(&greenBrush, points, 4, FillModeAlternate, 1.);
	
	PointF Point6(400.f, 100.f);
	PointF Point7(500.f, 50.f);
	PointF Point8(550.f, 200.f);
	PointF Point9(350.f, 150.f);
	PointF Point10(400.f, 100.f);
	PointF pointsPoly[5] = { Point6, Point7, Point8, Point9, Point10 };
	// 填充多边形区域
	graphics.FillPolygon(&greenBrush, pointsPoly, 5);
#endif

#if 1 // 3-9 填充正叶曲线
	Graphics graphics(hdc);

	// 创建绿色画刷
	SolidBrush greenBrush(Color::Green);

	// 指定中心点
	int cx = 300;
	int cy = 300;
	int leafLength = 100;// 设置叶长
	int leafNum = 5;// 叶片数量
	float PI = 3.14;
	int x2, y2;
	int x, y, r;

	// 创建图形路径对象，容纳正叶曲线边界线
	GraphicsPath tmpPath(FillModeAlternate);

	// 生成曲线边界数据，角度变化一周为PI*2;
	for (float i = 0.f; i < PI * 2 + 0.f;i+=PI/180)
	{
		r = abs(leafLength*cos(leafNum*i));
		x = r*cos(i);
		y = r*sin(i);
		x2 = cx + x;
		y2 = cy + y;
		//graphics.DrawLine(&Pen, x2, y2, x2 - 1, y2 - 1);
		tmpPath.AddLine(x2, y2, x2, y2);
	}
	graphics.FillPath(&greenBrush, &tmpPath);

	// 绘制中心坐标轴
	Pen pen(Color::Gray, 1);
	graphics.DrawLine(&pen, 0, cy, cx * 2, cy);
	graphics.DrawLine(&pen, cx, 0, cx, cy*2);

#endif
}

int CXqWindow:: GetWindth()
{
	return m_IWidth;
}

int CXqWindow::GetHight()
{
	return m_IHight;
}

void CXqWindow::OnLButtonDown(HWND hwnd, int x, int y)
{

	InvalidateRect(hwnd, NULL, FALSE);
}

void CXqWindow::OnLButtonUp(HWND hwnd, int x, int y)
{
	InvalidateRect(hwnd, NULL, FALSE);
}

void CXqWindow::OnMouseMove(HWND hwnd, int x, int y)
{
	InvalidateRect(hwnd, NULL, FALSE);
}

void CXqWindow::OnSize(HWND hwnd, int w, int h)
{
	width = w;
	height = h;
	InvalidateRect(hwnd, NULL, FALSE);
}

void OnCreate(HWND hwnd)
{
}

void CXqWindow::Create()
{
	m_WClassEx.cbSize = sizeof(WNDCLASSEX);
	m_WClassEx.lpfnWndProc = WndProc;
	m_WClassEx.hInstance = m_HInstance;
	m_WClassEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	m_WClassEx.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	m_WClassEx.lpszClassName = L"windows";
	m_WClassEx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	m_WClassEx.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&m_WClassEx)) {
		MessageBox(NULL, L"Window Registration Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
		return ;
	}

	m_HWnd = CreateWindowEx(WS_EX_CLIENTEDGE, L"windows", L"GDI+ [feijianshen]", WS_VISIBLE | WS_OVERLAPPEDWINDOW,
		m_IPosX,
		m_IPosY,
		m_IWidth,
		m_IHight,
		NULL, NULL, m_HInstance, NULL);

	if (m_HWnd == NULL)
	{
		MessageBox(NULL, L"Window Creation Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
		return ;
	}
}

void CXqWindow::Create(LPCWSTR lpszClassName)
{
	memset(&m_WClassEx, 0, sizeof(m_WClassEx));
	m_WClassEx.cbSize = sizeof(WNDCLASSEX);
	m_WClassEx.lpfnWndProc = WndProc;
	m_WClassEx.hInstance = m_HInstance;
	m_WClassEx.hCursor = LoadCursor(NULL, IDC_ARROW);
	m_WClassEx.hbrBackground = (HBRUSH)(COLOR_WINDOW);
	m_WClassEx.lpszClassName = lpszClassName;
	m_WClassEx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	m_WClassEx.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&m_WClassEx)) {
		MessageBox(NULL, L"Window Registration Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
		return;
	}

	m_HWnd = CreateWindowEx(WS_EX_CLIENTEDGE, lpszClassName, lpszClassName, WS_VISIBLE | WS_OVERLAPPEDWINDOW,
		m_IPosX, 
		m_IPosY,
		m_IWidth,
		m_IHight,
		NULL, NULL, m_HInstance, NULL);

	if (m_HWnd == NULL)
	{
		MessageBox(NULL, L"Window Creation Failed!", L"Error!", MB_ICONEXCLAMATION | MB_OK);
		return;
	}
}

void CXqWindow::MoveWindow(int x, int y, int width, int hight, BOOL bRepaint)
{
	::MoveWindow(m_HWnd,x, y, width, hight, bRepaint);
}
void CXqWindow::ShowWindow(int nCmdShow)
{
	::ShowWindow(m_HWnd, nCmdShow);
	UpdateWindow();
}

void CXqWindow::UpdateWindow(void)
{
	::UpdateWindow(m_HWnd);
}

WPARAM CXqWindow::MessageLoop(void)
{
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}



int CXqWindow::HandleMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return 0;
}


LRESULT CALLBACK CXqWindow::WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) 
{
	switch (Message) {
	case WM_CREATE:
		OnCreate(hwnd);
		return 0;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		BeginPaint(hwnd, &ps);
		OnDraw(ps.hdc);
		EndPaint(hwnd, &ps);
		return 0;
	}
	case WM_DESTROY:
	{
		PostQuitMessage(0);
		break;
	}
	case WM_LBUTTONDOWN:
	{
		OnLButtonDown(hwnd, LOWORD(lParam), HIWORD(lParam));
		return 0;
	}
	case WM_LBUTTONUP:
	{
		OnLButtonUp(hwnd, LOWORD(lParam), HIWORD(lParam));
		return 0;
	}
	case WM_MOUSEMOVE:
	{
		OnMouseMove(hwnd, LOWORD(lParam), HIWORD(lParam));
		return 0;
	}
	case WM_SIZE:
	{
		OnSize(hwnd, LOWORD(lParam), HIWORD(lParam));
		return 0;
	}
	default:
		return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}