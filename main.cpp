#include "PhysicalMap.h"
#include "robot.h"
#include <iostream>
#include <ctime>
#include <random>
#include <cstdlib>
int main() {
	auto obs = Obstacle(250, 500, 250, 500);
	
	auto map = PhysicalMap(obs);

	std::cout << "Now onto ray casting\n From position 0,0 \t Facing East\n";
	
	Robot rob(0,0,East,map); //1 = North direction, (X,Y) (0,0)

	rob.rayCasting();
	int x = 157;
	int y = 148;
	CardinalDirection dir = East;
	std::cout << "From position " << x <<","<< y <<"\t Facing East\n";
	rob.setX(x);
	rob.setY(y);
	rob.setOrientation(dir);//2

	rob.rayCasting();
	x = 77;
	y = 274;
	dir = East;
	std::cout << "From position " << x <<","<< y <<"\t Facing East\n";
	rob.setX(x);
	rob.setY(y);
	rob.setOrientation(dir);//3

	rob.rayCasting();
	x = 70;
	y = 422;
	dir = East;
	std::cout << "From position " << x <<","<< y <<"\t Facing East\n";
	rob.setX(x);
	rob.setY(y);
	rob.setOrientation(dir);//4

	rob.rayCasting();
	x = 73;
	y = 529;
	dir = East;
	std::cout << "From position " << x <<","<< y <<"\t Facing East\n";
	rob.setX(x);
	rob.setY(y);
	rob.setOrientation(dir);//5
	
	rob.rayCasting();
	x = 99;
	y = 679;
	dir = East;
	std::cout << "From position " << x <<","<< y <<"\t Facing East\n";
	rob.setX(x);
	rob.setY(y);
	rob.setOrientation(dir); //6

	rob.rayCasting();
	x = 378;
	y = 607;
	dir = North;
	std::cout << "From position " << x <<","<< y <<"\t Facing North\n";
	rob.setX(x);
	rob.setY(y);
	rob.setOrientation(dir);//7

	rob.rayCasting();
	x = 658;
	y = 435;
	dir = South;
	std::cout << "From position " << x <<","<< y <<"\t Facing West\n";
	rob.setX(x);
	rob.setY(y);
	rob.setOrientation(dir); //8

	rob.rayCasting();
	x = 683;
	y = 216;
	dir = North;
	std::cout << "From position " << x <<","<< y <<"\t Facing North\n";
	rob.setX(x);
	rob.setY(y);
	rob.setOrientation(dir);//9
	srand(time(NULL));
	x = rand()%1000;
	y = rand()%1000;
	dir = (fromNumber(rand()%3));
	std:: cout << "Now for #10 - TASK 3 - AT RANDOM POSITION "<< x <<","<< y <<"\t Facing ";
	if (dir == 0)
		std::cout << "North\n";
	else if (dir == 1)
		std::cout << "East\n";
	else if (dir == 2)
		std::cout << "South\n";
	else
		std::cout << "West\n";
	
	std::cout << "\n\n\n";
  return 0;
}
