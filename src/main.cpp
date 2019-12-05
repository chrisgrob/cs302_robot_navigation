#include "project_utils.h"
#include "robot.h"
#include "occupancy_grid_map.h"

#include <iostream>

int main()
{
  const IndexType map_size = 16;
  const Obstacle obstacle = Obstacle(0, 4, 0, 4);

  OccupancyGridMap robot_map = OccupancyGridMap(map_size, obstacle);

  Robot robot = Robot(std::make_pair(7, 8), CardinalDirection::North, robot_map);

  robot.RayCasting();

  std::cout << robot.get_map() << std::endl;
  std::cout << std::endl << std::endl;

  return 0;
}
