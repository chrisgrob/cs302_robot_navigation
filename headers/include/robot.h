#pragma once

#include "project_utils.h"
#include "occupancy_grid_map.h"

class Robot
{
private:
  VertexType occupied_vertex_;
  CardinalDirection orientation_; //Where the robot is currently facing
  // CoordinateType pos_; //The position on the map that it is currently in
  OccupancyGridMap map_; //The actual map that the robot is on

public:
  Robot(); //default ctor
  Robot(const CoordinateType pos, const CardinalDirection orientation, const OccupancyGridMap map); //parametrized ctor


  void set_pos(const CoordinateType pos); //sets position of the robot
  CoordinateType get_pos() const; //returns the current position of the robot

  void set_orientation(const CardinalDirection orientation); //sets orientation of the robot
  CardinalDirection get_orientation() const; //Returns the current orientation of the robot

  void set_map(const OccupancyGridMap map); //Sets the current map of the robot
  const OccupancyGridMap& get_map() const; //Returns what map the robot is on
  

  void RayCasting(); //The method to actually raycast depending on the position of the robot

private:
  //The following are helper methods for RayCasting
  void RayRange(const int start, const int end); //Determines the range of the cast
  void Ray(const int direction); //What the ray is going to be

  enum class CastType
  {
    Vertical,
    Diagonal,
    Normal,
  };
  void Cast(const SignPair steps, const int direction, CastType cast_type); //where the case is going to take place

  // Helpers for Cast()
  DoubleCoordinateType RayIncrement(
    const DoubleCoordinateType ray_pos, 
    const int direction, 
    const SignPair steps, 
    const CastType cast_type);

  std::pair<VertexType, Trilean> DesiredVertex(
    const VertexType read_vertex,
    const DoubleCoordinateType ray_pos,
    const SignPair steps,
    const CastType cast_type); //The desired vertex for where on the map the ray casting is occurring

  CardinalDirection DesiredDirection(
    const VertexType read_vertex, 
    const DoubleCoordinateType ray_pos, 
    const SignPair steps, 
    const CastType cast_type);

  CardinalDirection DesiredDirectionVertical(const SignPair steps);
  CardinalDirection DesiredDirectionDiagonal(const SignPair steps);
  CardinalDirection DesiredDirectionNormal(
    const VertexType read_vertex, 
    const DoubleCoordinateType ray_pos, 
    const SignPair steps);

  // Helper for DesiredDirectionNormal()
  CardinalDirection DesiredDirectionAxis(const int read_y, const double ray_y, const SignPair steps);

  std::pair<EdgeType, bool> DesiredEdge(const VertexType vertex, const CardinalDirection desired_direction);

  std::pair<VertexType, Trilean> VertexFromEdge(const std::pair<EdgeType, bool> desired_edge);


  // Cast will call this for each vertex it passes through
  void UpdateMap(VertexType vertex, double sensor_reading); //Updates the map depending on the vertex and the sensor reading of the vertex
  
  
  
  // Utility functions, defined in robot_utils.cpp
  unsigned int Quartile(const int degrees); //Returns an int for the quartile of wherever the vector is
  SignPair Steps(const unsigned int quartile); //Returns the sign pair in relation to the quartile
  bool Horizontal(const int read_y, const float ray_y, const Sign step_y); //Determines whether it can step horizontally or not
  bool IsFree(const VertexType vertex);
  bool HasEdges(const VertexType vertex);

};
