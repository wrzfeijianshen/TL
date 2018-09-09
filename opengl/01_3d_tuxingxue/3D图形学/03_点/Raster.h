#pragma once
#include "CellMath.hpp"
namespace   CELL
{
	class Raster
	{
	public:
		Raster();
		~Raster();
	public:
		Rgba _buffer[256][256];
	public:
		void    clear();
		void    drawPoint(int x, int y, Rgba color, int ptSize);
		void    setPixel(int x, int y, Rgba color);
	};
}
