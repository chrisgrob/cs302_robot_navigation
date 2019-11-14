#pragma once
#ifndef ROBOT_H
#define ROBOT_H
#include "map.cpp"
#incldue <iostream>
#include <cstdlib>
#include <vector>



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
    bool ray_casting();
	
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
bool Robot::ray_casting() //Hey Gage do this
{
	return false;
}
#endif //ROBOT_H
