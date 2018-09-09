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
}