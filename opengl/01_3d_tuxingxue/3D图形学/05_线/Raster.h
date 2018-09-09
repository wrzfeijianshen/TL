#pragma once
#include "CellMath.hpp"
namespace   CELL
{
	class Raster
	{
	public:
		Raster(int w, int h, void* buffer);
		~Raster();
	public:
		Rgba * _buffer;
		int    _width;
		int    _height;
	public:
		void    clear();
		void    drawPoint(int x, int y, Rgba color, int ptSize);
		void    drawLine(float2 pt1, float2 pt2, Rgba color);

		inline void setPixel(unsigned x, unsigned y, Rgba color)
		{
			if (x >= _width || y >= _height)
			{
				return;
			}
			_buffer[y * _width + x] = color;
		}
	};
}
