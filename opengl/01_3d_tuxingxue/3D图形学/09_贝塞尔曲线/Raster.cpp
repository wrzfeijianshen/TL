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
}