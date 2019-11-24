#pragma once

#include <iostream>
#include <algorithm>
#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/graphviz.hpp"
#include "boost/graph/properties.hpp"
#include "boost/property_map/property_map.hpp"
#include "boost/graph/named_function_params.hpp"

const size_t MAP_SIZE = 16;

struct VertexData
{
	float probTaken;
	float probEmpty;
};

struct EdgeData
{
	// Nothing?
};

typedef boost::adjacency_list<boost::vecS, boost::vecS,
                                boost::undirectedS,
                                VertexData,
                                boost::property<boost::edge_weight_t, float>
                                > MyGraphType;

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
	// PhysicalMap();
	// PhysicalMap(const size_t obsXMin, const size_t obsXMax, const size_t obsYMin, const size_t obsYMax);
	PhysicalMap(const Obstacle obs);
	// PhysicalMap(const Obstacle * obsArray, const size_t numObstacles);
	// PhysicalMap(const PhysicalMap & other);
	// PhysicalMap & operator=(const PhysicalMap & rhs);

	// bool isOccupied(const size_t x, const size_t y) const;

	void visualize() const;
	friend std::ostream & operator<<(std::ostream & os, const PhysicalMap & map);
	
	int vertexCount() const;
	int edgeCount() const;

private:
	MyGraphType map;

	void visualize(std::ostream & os) const;
<<<<<<< HEAD
	std::pair<int, int> coordinate(const int i, const int mapSize);

	bool pointIsObstacle(const int i, const Obstacle obs);
	bool pointIsBottom(const int i, const int map_size);
	bool pointIsLeftEdge(const int i, const int map_size);
	bool pointIsRightEdge(const int, const int map_size);
	bool attemptConnection(const int i, const int other, MyGraphType& g, const Obstacle obs);
};
=======
};

void graphDef(){
	typedef boost::adjacency_list<boost::listS, boost::vecS, boost::directedS, Vertex, Edge > Graph;
	//Some typedefs for simplicity
	typedef boost::graph_traits<Graph>::vertex_descriptor vertex_t;
	typedef boost::graph_traits<Graph>::edge_descriptor edge_t;

	//Instanciate a graph
	Graph g;

	// Create two vertices in that graph
	vertex_t u = boost::add_vertex(g);
	vertex_t v = boost::add_vertex(g);

	// Create an edge conecting those two verticesv
	edge_t e; bool b;
	boost::tie(e,b) = boost::add_edge(u,v,g); //adding different edges and stuff


	// Set the properties of a vertex and the edge
	g[u].probTaken = .42;
	g[u].probEmpty = .25;
	
}
>>>>>>> 3c996995ad5529d6db0c4cc1befda46c170d9db3
