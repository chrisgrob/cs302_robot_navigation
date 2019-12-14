#include "project_utils.h"
#include "robot.h"
#include "occupancy_grid_map.h"

#include <iostream>
#include <fstream>

int main()
{
  const IndexType map_size = 1000;
  const Obstacle obstacle = Obstacle(249, 499, 249, 499);

  std::cout << "Map is being set up" << std::endl;
  OccupancyGridMap robot_map = OccupancyGridMap(map_size, obstacle);
  std::cout << "Map is done being set up" << std::endl;

  // 1
  Robot robot = Robot(std::make_pair(0, 0), CardinalDirection::East, robot_map);
  robot.RayCasting();
  
  // 2
  robot.set_pos(std::make_pair(156, 147));
  robot.set_orientation(CardinalDirection::East);
  robot.RayCasting();
  
  // 3
  robot.set_pos(std::make_pair(76, 273));
  robot.set_orientation(CardinalDirection::East);
  robot.RayCasting();
  
  // 4
  robot.set_pos(std::make_pair(69, 421));
  robot.set_orientation(CardinalDirection::East);
  robot.RayCasting();
  
  // 5
  robot.set_pos(std::make_pair(72, 528));
  robot.set_orientation(CardinalDirection::East);
  robot.RayCasting();
  
  // 6
  robot.set_pos(std::make_pair(98, 678));
  robot.set_orientation(CardinalDirection::East);
  robot.RayCasting();
  
  // 7
  robot.set_pos(std::make_pair(377, 606));
  robot.set_orientation(CardinalDirection::North);
  robot.RayCasting();
  
  // 8
  robot.set_pos(std::make_pair(657, 434));
  robot.set_orientation(CardinalDirection::West);
  robot.RayCasting();
  
  // 9
  robot.set_pos(std::make_pair(682, 215));
  robot.set_orientation(CardinalDirection::North);
  robot.RayCasting();
  
  // 10th measurement
  robot.set_pos(std::make_pair(520, 300));
  robot.set_orientation(CardinalDirection::West);
  robot.RayCasting();

  std::ofstream out_file;
  out_file.open("probabilities.txt");
  robot.get_map().VisualizeProbabilities(out_file);

  return 0;
}
