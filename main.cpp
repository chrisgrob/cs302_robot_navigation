#include "PhysicalMap.h"
#include <iostream>

int main() {
	auto obs = Obstacle(4, 8, 4, 8);
	
	auto map = PhysicalMap(obs);
	
	std::cout << map << std::endl;
	std::cout << map.vertexCount() << std::endl;
	std::cout << map.edgeCount() << std::endl;

  return 0;
}
