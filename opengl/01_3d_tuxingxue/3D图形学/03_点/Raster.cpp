#include "Raster.h"

namespace   CELL
{

	Raster::Raster()
	{
	}


	Raster::~Raster()
	{
	}

	void CELL::Raster::clear()
	{
		memset(_buffer, 0, sizeof(_buffer));
	}

	void CELL::Raster::drawPoint(int x, int y, Rgba color, int ptSize)
	{
		switch (ptSize)
		{
		case 1:
			setPixel(x, y, color);
			break;
		case 2:
			setPixel(x + 0, y + 0, color);
			setPixel(x + 1, y + 0, color);
			setPixel(x + 0, y + 1, color);
			setPixel(x + 1, y + 1, color);
			break;
		case 3:

			setPixel(x - 1, y - 1, color);
			setPixel(x + 0, y - 1, color);
			setPixel(x + 1, y - 1, color);

			setPixel(x - 1, y + 0, color);
			setPixel(x + 0, y + 0, color);
			setPixel(x + 1, y + 0, color);

			setPixel(x - 1, y + 1, color);
			setPixel(x + 0, y + 1, color);
			setPixel(x + 1, y + 1, color);
			break;
		default:
			for (int i = 0; i < ptSize;i++)
			{
				for (int j = 0;j < ptSize;j++)
				{
					setPixel(x - i, y + j, color);
					setPixel(x - i, y - j, color);
					setPixel(x + i, y - j, color);
					setPixel(x + i, y + j, color);

				}
			}
			break;
		}
	}

	void CELL::Raster::setPixel(int x, int y, Rgba color)
	{
		if (x < 0 || y < 0 || x >= 256 || y >= 256)
		{
			return;
		}
		_buffer[y][x] = color;
	}
}