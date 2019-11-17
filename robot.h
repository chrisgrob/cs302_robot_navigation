#pragma once
#ifndef ROBOT_H
#define ROBOT_H
// #include "map.cpp" Doesn't exist? - Gage
#incldue <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>

const double pi = 3.14159265358979323846

// An x coord, a y coord, and a probability of being occupied
class Point {
	public:
		const int x;
		const int y;
		const float occupied;

		Point(int x, int y, float occupied);
}

class Ray {
	private:
		std::vector<Point> points;
	public:
		Ray(int direction, Map map);

		std::vector<Point> get_points();
}

class Robot {
  private:
    int direction; // 0 -north, 1-east, 2-south, 3-west
    int locX;
    int locY;
	Map m;
  public:
    Robot();

    Robot(int direction1, int locX1, int locY1);
	
	bool ableToMove();
	void rotate();
	void move(); //Moves one space
  std::vector<Point> ray_casting();
	
	private:
		
};
Robot::Robot()
{
	locX = 0;
	locY = 0;
	direction = 2; //Pointing south is defualt
}
Robot::Robot(int direction1, int locX1, int locY1)
{
	direction = direction1;
	locX = locX1;
	locY = locY1;
}
bool Robot::ableToMove() 
{
	if(direction == 1)
	{
		if (m.isOccupied(locX + 1,locY))
			return false;
	}
			
	if(direction == 0)
	{
		if (m.isOccupied(locX,locY+1))
			return false;
	}
			
	if(direction == 2)
	{
		if (m.isOccupied(locX,locY-1))
			return false;
	}
			
	if(direction == 3)
	{
		if (m.isOccupied(locX - 1,locY))
			return false;
	}
	return true; //It is able to move 
}
void Robot::rotate()
{
	if (direction < 3)
		direction++;
	else
		direction = 0;
}
void Robot::move()
{	
	if(direction == 1 && !(m.isOccupied(locX + 1,locY)))
	{
		locX + 1;
		
	}
			
	if(direction == 0 && !(m.isOccupied(locX,locY+1)))
	{
		locY + 1;
	}
			
	if(direction == 2 && !(m.isOccupied(locX,locY-1)))
	{
		locY - 1;
	}
			
	if(direction == 3 && !(m.isOccupied(locX - 1,locY)))
	{
		locX - 1;
	}
}

// returns a vector of points. Each point has information about whether it's occupied or not
std::vector<Point> Robot::ray_casting()
{
	std::vector points;

	int start_direction;
	int end_direction;
	if (direction == 0) {
		start_direction = 0;
		end_direction = 180;
	} else if (direction == 1) {
		start_direction = -90;
		end_direction = 90;
	} else if (direction == 2) {
		start_direction = 180;
		end_direction = 360;
	} else if (direction == 3) {
		start_direction = 90;
		end_direction = 270;
	}

	for (int i = 0; i <= 180; i += 15) {
		Ray some_ray = Ray(direction, m, locX, locY);

		std::vector<Point> some_points = some_ray.get_points();

		int i = 0;
		for (auto itr = some_points.begin(); itr != some_points.end(); itr++) {
			points.push(some_points[i]);
			i++;
		}
	}

	return points;
}

// I hate trig
Ray::Ray(const int direction, const Map map, const int robot_x, const int robot_y)
{
	const int radians = (direction * 2 * pi) / 360;

	std::vector points;

	int x_read = robot_x;
	int y_read = robot_y;
	bool occupied = false;
	float length = 0;
	while (!occupied && length < 50.0) {
		const x_read_to = x_read + 1;

		bool not_straight = (direction != 0 && direction != 90) && (direction != 180 && direction != 270);

		int y_read_to_temp;
		int halfway_point_temp;
		if (not_straight) {
			y_read_to_temp = y_read + tan(radians);
			halfway_point_temp = y_read + (0.5 * tan(radians));
		} else if (direction == 90 || direction == 270) {
			y_read_to_temp = y_read + 50;
			halfway_point_temp = y_read + 25;
		} else {
			y_read_to_temp = 0;
			halfway_point_temp = 0;
		}

		const y_read_to = y_read_to_temp;
		const halfway_point = halfway_point_temp;

		length += 1 / cos(radians)

		const int first_limit = ceil(halfway_point)
		for (int i = 1; i <= first_limit; i++) {
			points.push(Point(x_read, y_read + i, map[x_read, y_read + i]));

			if map[x_read, y_read + i] {
				occupied = true;
				break;				
			}
		}

		const int second_start = floor(halfway_point);
		const int second_limit = ceil(y_read_to);
		for (int i = second_start, i <= second_limit; i++) {
			points.push(Point(x_read_to, y_read + i, map[x_read_to, y_read + i]));

			if map[x_read_to, y_read + i] {
				occupied = true;
				break;
			}
		}
	}
}

#endif //ROBOT_H