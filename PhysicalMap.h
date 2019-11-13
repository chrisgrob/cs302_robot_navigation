#pragma once

#include <iostream>

const size_t MAP_SIZE = 16;

struct Obstacle
{
	Obstacle(const size_t obsXMin, const size_t obsXMax, const size_t obsYMin, const size_t obsYMax)
		: xMin(obsXMin), xMax(obsXMax), yMin(obsYMin), yMax(obsYMax)
	{
	}

	size_t xMin;
	size_t xMax;
	size_t yMin;
	size_t yMax;
};

class PhysicalMap
{
public:
	// I made more ctors than were necessary for flexibility
	// The default and first parameterized ctor should be enough
	// The default ctor creates the obstacle specified by the project
	PhysicalMap();
	PhysicalMap(const size_t obsXMin, const size_t obsXMax, const size_t obsYMin, const size_t obsYMax);
	PhysicalMap(const Obstacle obs);
	PhysicalMap(const Obstacle * obsArray, const size_t numObstacles);
	PhysicalMap(const PhysicalMap & other);
	PhysicalMap & operator=(const PhysicalMap & rhs);

	bool isOccupied(const size_t x, const size_t y) const;

	void visualize() const;
	friend std::ostream & operator<<(std::ostream & os, const PhysicalMap & map);

private:
	bool map[MAP_SIZE][MAP_SIZE];

	void visualize(std::ostream & os) const;
};