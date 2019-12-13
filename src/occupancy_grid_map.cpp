#include "occupancy_grid_map.h"



// Empty graph
OccupancyGridMap::OccupancyGridMap()
{
  map_size_ = 0;
}



// Free vertices have connections to every surrounding vertex
// Non-free vertices don't have any outward connections
OccupancyGridMap::OccupancyGridMap(const IndexType map_size, const Obstacle obstacle)
{
  map_size_ = map_size;

  map_ = MapType(map_size * map_size);
	
  VertexRange vertex_range = boost::vertices(map_);
	
  for (VertexIterator iter = vertex_range.first; iter != vertex_range.second; iter++) {
    map_[*iter] = 0; // Initial probabilities are 50/50, which in logodd terms means 0
    
    if (!VertexIsObstacle(*iter, obstacle)) {
      if (!VertexIsTop(*iter))
      {
        Connection(*iter, std::make_pair(0, -1), CardinalDirection::North);
        
        if (!VertexIsLeftEdge(*iter))
        {
          Connection(*iter, std::make_pair(-1, -1), CardinalDirection::NorthWest);
        }

        if (!VertexIsRightEdge(*iter))
        {
          Connection(*iter, std::make_pair(1, -1), CardinalDirection::NorthEast);
        }
      }

      if (!VertexIsRightEdge(*iter))
      {
        Connection(*iter, std::make_pair(1, 0), CardinalDirection::East);
      }

      if (!VertexIsBottom(*iter))
      {
        Connection(*iter, std::make_pair(0, 1), CardinalDirection::South);

        if (!VertexIsLeftEdge(*iter))
        {
          Connection(*iter, std::make_pair(-1, 1), CardinalDirection::SouthWest);
        }

        if (!VertexIsRightEdge(*iter))
        {
          Connection(*iter, std::make_pair(1, 1), CardinalDirection::SouthEast);
        }
      }

      if (!VertexIsLeftEdge(*iter))
      {
        Connection(*iter, std::make_pair(-1, 0), CardinalDirection::West);
      }
    }
  }
}



OccupancyGridMap::OccupancyGridMap(const OccupancyGridMap & other)
{
  map_size_ = other.map_size_;
  map_ = other.map_;
}



void OccupancyGridMap::set_map(const MapType map)
{
  map_ = map;
}



const MapType& OccupancyGridMap::get_map() const
{
  return map_;
}



MapType& OccupancyGridMap::get_map()
{
  return map_;
}



IndexType OccupancyGridMap::get_map_size() const
{
  return map_size_;
}



bool OccupancyGridMap::IsInBounds(const CoordinateType coordinate) const
{
  bool is_in_bounds;

  const bool x_in_bounds = coordinate.first >= 0 && coordinate.first < map_size_;
  const bool y_in_bounds = coordinate.second >= 0 && coordinate.second < map_size_;

  if (x_in_bounds && y_in_bounds)
  {
    is_in_bounds = true;
  }
  else
  {
    is_in_bounds = false;
  }

  return is_in_bounds;
}



void OccupancyGridMap::AddToVertex(const VertexType vertex, const double number)
{
  map_[vertex] += number;
}



VertexType OccupancyGridMap::Vertex(const CoordinateType coordinate) const
{
  VertexType vertex;

  const IndexType index = coordinate.first + (map_size_ * coordinate.second);

  vertex = boost::vertex(index, map_);

  return vertex;
}



CoordinateType OccupancyGridMap::Coordinate(const VertexType vertex) const
{
  CoordinateType coordinate = std::make_pair(0, 0);

  IndexType index = boost::get(boost::vertex_index, map_, vertex);

  coordinate.first = index;

  while (coordinate.first >= map_size_)
  {
    coordinate.first -= map_size_;
    coordinate.second += 1;
  }

  return coordinate;
}



void OccupancyGridMap::VisualizeObstacles() const
{
  IndexType x_pos = 0;

  const VertexRange vertex_range = boost::vertices(map_);

  for (VertexIterator iter = vertex_range.first; iter != vertex_range.second; iter++)
  {
    int count = 0;
    
    auto out = boost::out_edges(*iter, map_);
    
    for (auto iter = out.first; iter != out.second; iter++)
    {
      count++;
    }
    
    std::cout << count << " ";

    x_pos++;

    if (x_pos == map_size_)
    {
      std::cout << std::endl;
      x_pos = 0;
    }
  }
}



std::ostream& operator<<(std::ostream& os, const OccupancyGridMap& map)
{
  map.Visualize(os);
  
  return os;
}



void OccupancyGridMap::Visualize(std::ostream& os) const
{
  IndexType x_pos = 0;

  const VertexRange vertex_range = boost::vertices(map_);
  
  os << std::fixed << std::setprecision(1) << std::setfill(' ');

  for (VertexIterator iter = vertex_range.first; iter != vertex_range.second; iter++)
  {
    os << std::setw(6) << map_[*iter] << " ";

    x_pos++;

    if (x_pos == map_size_)
    {
      os << std::endl;
      x_pos = 0;
    }
  }
}



void OccupancyGridMap::VisualizeProbabilities(std::ostream& os) const
{
  IndexType x_pos = 0;

  const VertexRange vertex_range = boost::vertices(map_);

  for (VertexIterator iter = vertex_range.first; iter != vertex_range.second; iter++)
  {
    os << prob(map_[*iter]) << " ";

    x_pos++;

    if (x_pos == map_size_)
    {
      os << std::endl;
      x_pos = 0;
    }
  }
}



bool OccupancyGridMap::VertexIsObstacle(const VertexType vertex, const Obstacle obstacle)
{
  bool vertex_is_obstacle;

  CoordinateType coordinate = Coordinate(vertex);

  const bool in_x_range = coordinate.first >= obstacle.x_min && coordinate.first <= obstacle.x_max;
  const bool in_y_range = coordinate.second >= obstacle.y_min && coordinate.second <= obstacle.y_max;

  if (in_x_range && in_y_range)
  {
    vertex_is_obstacle = true;
  }
  else
  {
    vertex_is_obstacle = false;
  }

  return vertex_is_obstacle;
}



bool OccupancyGridMap::VertexIsTop(const VertexType vertex)
{
  bool vertex_is_top;

  CoordinateType coordinate = Coordinate(vertex);

  if (coordinate.second == 0)
  {
    vertex_is_top = true;
  }
  else
  {
    vertex_is_top = false;
  }

  return vertex_is_top;
}



bool OccupancyGridMap::VertexIsBottom(const VertexType vertex)
{
  bool vertex_is_bottom;

  CoordinateType coordinate = Coordinate(vertex);

  if (coordinate.second == map_size_ - 1)
  {
    vertex_is_bottom = true;
  }
  else
  {
    vertex_is_bottom = false;
  }

  return vertex_is_bottom;
}



bool OccupancyGridMap::VertexIsLeftEdge(const VertexType vertex)
{
  bool vertex_is_left_edge;

  CoordinateType coordinate = Coordinate(vertex);

  if (coordinate.first == 0)
  {
    vertex_is_left_edge = true;
  }
  else
  {
    vertex_is_left_edge = false;
  }

  return vertex_is_left_edge;
}



bool OccupancyGridMap::VertexIsRightEdge(const VertexType vertex)
{
  bool vertex_is_right_edge;

  CoordinateType coordinate = Coordinate(vertex);

  if (coordinate.first == map_size_ - 1)
  {
    vertex_is_right_edge = true;
  }
  else
  {
    vertex_is_right_edge = false;
  }

  return vertex_is_right_edge;
}



void OccupancyGridMap::Connection(const VertexType vertex, const CoordinateType coordinate_change, const CardinalDirection direction)
{
  const CoordinateType coordinate = Coordinate(vertex);
  const CoordinateType other_coordinate = std::make_pair(
    coordinate.first + coordinate_change.first, 
    coordinate.second + coordinate_change.second);

  const VertexType other_vertex = Vertex(other_coordinate);

  std::pair<EdgeType, bool> new_edge = boost::add_edge(vertex, other_vertex, map_);
  
  if (new_edge.second) {
    map_[new_edge.first] = direction;
  }
}
