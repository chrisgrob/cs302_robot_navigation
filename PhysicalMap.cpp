#include "PhysicalMap.h"
#include <iostream>


PhysicalMap::PhysicalMap()
{
	size_t bottomLimit = MAP_SIZE / 4;
	size_t topLimit = 2 * bottomLimit;

	for (size_t i = 0; i < MAP_SIZE; i++)
	{
		for (size_t j = 0; j < MAP_SIZE; j++)
		{
			if ((i >= bottomLimit && i <= topLimit) && (j >= bottomLimit && j <= topLimit))
				map[j][i] = true;
			else
				map[j][i] = false;
		}
	}
}

PhysicalMap::PhysicalMap(const size_t obsXMin, const size_t obsXMax, const size_t obsYMin, const size_t obsYMax)
{
	

	for (size_t i = 0; i < MAP_SIZE; i++)
	{
		for (size_t j = 0; j < MAP_SIZE; j++)
		{
			if ((j >= obsXMin && j <= obsXMax) && (i >= obsYMin && i <= obsYMax))
				map[j][i] = true;
			else
				map[j][i] = false;
		}
	}
}

PhysicalMap::PhysicalMap(const Obstacle obs)
{
	for (size_t i = 0; i < MAP_SIZE; i++)
	{
		for (size_t j = 0; j < MAP_SIZE; j++)
		{
			if ((j >= obs.xMin && j <= obs.xMax) && (i >= obs.yMin && i <= obs.yMax))
				map[j][i] = true;
			else
				map[j][i] = false;
		}
	}
}

PhysicalMap::PhysicalMap(const Obstacle * obsArray, const size_t numObstacles)
{
	//creates first obstacle and the non-occupied spaces
	for (size_t i = 0; i < MAP_SIZE; i++)
	{
		for (size_t j = 0; j < MAP_SIZE; j++)
		{
			if ((j >= obsArray[0].xMin && j <= obsArray[0].xMax) &&
				(i >= obsArray[0].yMin && i <= obsArray[0].yMax))
				map[j][i] = true;
			else
				map[j][i] = false;
		}
	}

	//creates all remaining obstacles
	for (size_t obsIndex = 1; obsIndex < numObstacles; obsIndex++)
	{
		for (size_t i = 0; i < MAP_SIZE; i++)
		{
			for (size_t j = 0; j < MAP_SIZE; j++)
			{
				if ((j >= obsArray[0].xMin && j <= obsArray[0].xMax) &&
					(i >= obsArray[0].yMin && i <= obsArray[0].yMax))
					map[j][i] = true;
			}
		}
	}
}

PhysicalMap::PhysicalMap(const PhysicalMap & other)
{
	for (size_t i = 0; i < MAP_SIZE; i++)
	{
		for (size_t j = 0; j < MAP_SIZE; j++)
		{
			map[j][i] = other.map[j][i];
		}
	}
}

PhysicalMap & PhysicalMap::operator=(const PhysicalMap & rhs)
{
	if (this != &rhs)
	{
		for (size_t i = 0; i < MAP_SIZE; i++)
		{
			for (size_t j = 0; j < MAP_SIZE; j++)
			{
				map[j][i] = rhs.map[j][i];
			}
		}
	}

	return *this;
}

bool PhysicalMap::isOccupied(const size_t x, const size_t y) const
{
	//array indexing causes this to be (y, x)
	return map[y][x];
}

void PhysicalMap::visualize() const
{
	visualize(std::cout);
}

void PhysicalMap::visualize(std::ostream & os) const
{
	for (size_t i = 0; i < MAP_SIZE; i++)
	{
		for (size_t j = 0; j < MAP_SIZE; j++)
		{
			if (isOccupied(j, i))
				std::cout << "x ";
			else
				std::cout << ". ";
		}
		std::cout << "\n";
	}
}

std::ostream & operator<<(std::ostream & os, const PhysicalMap & map)
{
	map.visualize(os);
	return os;
}
