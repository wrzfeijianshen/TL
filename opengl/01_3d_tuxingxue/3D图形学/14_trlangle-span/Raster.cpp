#include "Raster.h"

namespace   CELL
{

	Raster::Raster(int w, int h, void* buffer)
	{
		_width = w;
		_height = h;
		_buffer = (Rgba*)buffer;
	}


	Raster::~Raster()
	{
	}

	void CELL::Raster::clear()
	{
		memset(_buffer, 0, _width * _height * sizeof(_buffer));
	}

	void CELL::Raster::drawPoint(int x, int y, Rgba color, int ptSize)
	{
		if (ptSize <= 0)
		{
			return;
		}

		for (int i = 0; i < ptSize; i++)
		{
			for (int j = 0; j < ptSize; j++)
			{
				setPixel(x - i, y + j, color);
				setPixel(x - i, y - j, color);
				setPixel(x + i, y - j, color);
				setPixel(x + i, y + j, color);
			}
		}
	}

	void Raster::drawLine(int startX, int endX, int y, Rgba color1, Rgba color2)
	{
		float   length = tmax<int>(endX - startX, 1);
		for (int x = startX; x <= endX; ++x)
		{
			Rgba    color = colorLerp(color1, color2, (x - startX) / length);
			setPixel(x, y, color);
		}
	}

	void Raster::drawLine(float2 pt1, float2 pt2, Rgba color)
	{
		float   xOffset = pt1.x - pt2.x;
		float   yOffset = pt1.y - pt2.y;

		if (xOffset == 0 && yOffset == 0)
		{
			setPixel(pt1.x, pt1.y, color);
		}

		if (xOffset == 0)
		{
			float   yMin;
			float   yMax;
			if (pt1.y < pt2.y)
			{
				yMin = pt1.y;
				yMax = pt2.y;
			}
			else
			{
				yMin = pt2.y;
				yMax = pt1.y;
			}

			float   slope = yOffset / xOffset;
			for (float y = yMin; y <= yMax; y += 1.0f)
			{
				setPixel(pt2.x, y, color);
			}
		}
		else if (yOffset == 0)
		{
			float   xMin;
			float   xMax;
			if (pt1.x < pt2.x)
			{
				xMin = pt1.x;
				xMax = pt2.x;
			}
			else
			{
				xMin = pt2.x;
				xMax = pt1.x;
			}

			float   slope = yOffset / xOffset;
			for (float x = xMin; x <= xMax; x += 1.0f)
			{
				setPixel(x, pt2.y, color);
			}
		}
		else
		{

			if (fabs(xOffset) > fabs(yOffset))
			{
				float   slope = yOffset / xOffset;

				float   xMin;
				float   xMax;
				if (pt1.x < pt2.x)
				{
					xMin = pt1.x;
					xMax = pt2.x;
				}
				else
				{
					xMin = pt2.x;
					xMax = pt1.x;
				}

				for (float x = xMin; x <= xMax; x += 1.0f)
				{
					float   y = pt1.y + (x - pt1.x) * slope;
					setPixel(x, y, color);
				}
			}
			else
			{
				float   slope = xOffset / yOffset;

				float   yMin;
				float   yMax;
				if (pt1.y < pt2.y)
				{
					yMin = pt1.y;
					yMax = pt2.y;
				}
				else
				{
					yMin = pt2.y;
					yMax = pt1.y;
				}
				for (float y = pt1.y; y <= pt2.y; y += 1.0f)
				{
					float   x = pt1.x + (y - pt1.y) * slope;
					setPixel(pt2.x, y, color);
				}
			}
		}
	}
	void Raster::drawLine(float2 pt1, float2 pt2, Rgba color1, Rgba color2)
	{
		float   xOffset = pt1.x - pt2.x;
		float   yOffset = pt1.y - pt2.y;

		if (xOffset == 0 && yOffset == 0)
		{
			setPixel(pt1.x, pt1.y, color1);
		}

		if (fabs(xOffset) > fabs(yOffset))
		{
			float   slope = yOffset / xOffset;

			float   xMin;
			float   xMax;
			float   yValue = 0;

			if (pt1.x < pt2.x)
			{
				xMin = pt1.x;
				xMax = pt2.x;
				yValue = pt1.y;
			}
			else
			{
				xMin = pt2.x;
				xMax = pt1.x;
				yValue = pt2.y;

			}

			float   lenth = xMax - xMin;
			for (float x = xMin; x <= xMax; x += 1.0f)
			{
				float   y = yValue + (x - xMin) * slope;
				float   scaler = (x - xMin) / lenth;
				Rgba    color = colorLerp(color1, color2, scaler);
				setPixel(x, y, color);
			}
		}
		else
		{
			float   slope = xOffset / yOffset;

			float   yMin;
			float   yMax;
			float   xValue = 0;

			if (pt1.y < pt2.y)
			{
				yMin = pt1.y;
				yMax = pt2.y;
				xValue = pt1.x;
			}
			else
			{
				yMin = pt2.y;
				yMax = pt1.y;
				xValue = pt2.x;

			}

			float   lenth = yMax - yMin;
			for (float y = yMin; y <= yMax; y += 1.0f)
			{
				float   x = xValue + (y - yMin) * slope;
				float   scaler = (y - yMin) / lenth;
				Rgba    color = colorLerp(color1, color2, scaler);
				setPixel(x, y, color);
			}
		}
	}
	void Raster::drawArrays(DRAWMODE mode, const float2 * points, int count)
	{
		switch (mode)
		{
		case DM_POINTS:
		{
			for (int i = 0; i < count; ++i)
			{
				drawPoints(points[i], _color);
			}
		}
		break;
		case DM_LINES:
		{
			count = count / 2 * 2;
			for (int i = 0; i < count; i+=2)
			{
				drawLine(points[i], points[i + 1], _color, _color);
			}
		}
		break;
		case DM_LINE_LOOP:
		{
			drawLine(points[0], points[1], _color, _color);
			for (int i = 2; i < count; ++i)
			{
				drawLine(points[i - 1], points[i], _color, _color);
			}
			drawLine(points[0], points[count - 1], _color, _color);
		}
		break;
		case DM_LINE_STRIP:
		{
			drawLine(points[0], points[1], _color, _color);
			for (int i = 2; i < count; ++i)
			{
				drawLine(points[i - 1], points[i], _color, _color);
			}
		}
		break;
		default:
			break;
		}
	}
	void Raster::drawPoints(float2 pt1, Rgba4Byte color)
	{
	}
	void Raster::drawFilleRect(int startX, int startY, int w, int h)
	{
		int left = tmax<int>(startX, 0);
		int top = tmax<int>(startY, 0);
		int right = tmin<int>(startX +w, _width);
		int bottom = tmin<int>(startY+ h, _height);



		for (int i = left; i < right;i++)
		{
			for (int j = top; j < bottom; j++)
			{
				//setPixel(i, j, _color);
				setPixelEx(i, j, _color);
			}
		}
	}
	void Raster::drawRect(const int2 * points, const Rgba * colors)
	{
		int left = tmax<int>(points[0].x, 0);
		int top = tmax<int>(points[0].y, 0);
		int right = tmin<int>(points[2].x, _width);
		int bottom = tmin<int>(points[2].y, _height);

		float   w = right - left;
		float   h = bottom - top;

		for (int i = left; i < right; i++)
		{
			Rgba    color1 = colorLerp(colors[0], colors[1], (i - left) / w);
			Rgba    color2 = colorLerp(colors[3], colors[2], (i - left) / w);

			for (int j = top; j < bottom; j++)
			{
				//setPixel(i, j, _color);
				Rgba    color = colorLerp(color1, color2, (j - top) / h);
				setPixelEx(i, j, color);
			}
		}
	}
	void Raster::drawTriangle(int2 p0, int2 p1, int2 p2, Rgba c0, Rgba c1, Rgba c2)
	{
		Ege eges[3] =
		{
			Ege(p0.x,p0.y,c0,   p1.x,p1.y,c1),
			Ege(p1.x,p1.y,c1,   p2.x,p2.y,c2),
			Ege(p2.x,p2.y,c2,   p0.x,p0.y,c0),
		};
		int iMax = 0;
		int length = eges[0]._y2 - eges[0]._y1;

		for (int i = 1; i < 3; ++i)
		{
			int len = eges[i]._y2 - eges[i]._y1;
			if (len > length)
			{
				length = i;
			}
		}
		int iShort1 = (iMax + 1) % 3;
		int iShort2 = (iMax + 2) % 3;

		drawEge(eges[iMax], eges[iShort1]);
		drawEge(eges[iMax], eges[iShort2]);

	}

	void Raster::drawEge(const Ege & e1, const Ege & e2)
	{
		float   yOffset1 = e1._y2 - e1._y1;
		if (yOffset1 == 0)
		{
			return;
		}

		float   yOffset = e2._y2 - e2._y1;
		if (yOffset == 0)
		{
			return;
		}
		float   xOffset = e2._x2 - e2._x1;
		float   scale = 0;
		float   step = 1.0f / yOffset;


		float   xOffset1 = e1._x2 - e1._x1;
		float   scale1 = (float)(e2._y1 - e1._y1) / yOffset1;
		float   step1 = 1.0f / yOffset1;

		for (int y = e2._y1; y < e2._y2; ++y)
		{
			int     x1 = e1._x1 + (int)(scale1 * xOffset1);
			int     x2 = e2._x1 + (int)(scale * xOffset);
			Rgba    color2 = colorLerp(e2._color1, e2._color2, scale);
			Rgba    color1 = colorLerp(e1._color1, e1._color2, scale1);

			Span    span(x1, x2, y, color1, color2);
			drawSpan(span);

			scale += step;
			scale1 += step1;

		}
	}

	void Raster::drawSpan(const Span & span)
	{
		float   length = span._xEnd - span._xStart;
		for (int x = span._xStart; x < span._xEnd; ++x)
		{
			Rgba    color = colorLerp(
				span._colorStart
				, span._colorEnd
				, (float)(x - span._xStart) / length
			);
			setPixel(x, span._y, color);
		}
	}
	Ege::Ege(int x1, int y1, Rgba color1, int x2, int y2, Rgba color2)
	{
		if (y1 < y2)
		{
			_x1 = x1;
			_y1 = y1;
			_color1 = color1;

			_x2 = x2;
			_y2 = y2;
			_color2 = color2;
		}
		else
		{
			_x1 = x2;
			_y1 = y2;
			_color1 = color2;

			_x2 = x1;
			_y2 = y1;
			_color2 = color1;
		}
	}

	Span::Span(int xStart, int xEnd, int y, Rgba colorStart, Rgba colorEnd)
	{
		if (xStart < xEnd)
		{
			_xStart = xStart;
			_xEnd = xEnd;
			_colorStart = colorStart;
			_colorEnd = colorEnd;
			_y = y;
		}
		else
		{
			_xStart = _xEnd;
			_xEnd = _xStart;

			_colorStart = colorEnd;
			_colorEnd = colorStart;
			_y = y;
		}
	}
}