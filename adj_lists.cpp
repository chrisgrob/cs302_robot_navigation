#include <iostream>
#include "boost/graph/adjacency_list.hpp"
#include "boost/graph/graphviz.hpp"
#include "boost/graph/properties.hpp"
#include "boost/property_map/property_map.hpp"
#include "boost/graph/named_function_params.hpp"

// the predefined property types are listed here:
// http://www.boost.org/doc/libs/1_64_0/libs/graph/doc/using_adjacency_list.html#sec:adjacency-list-properties
// http://www.boost.org/doc/libs/1_64_0/libs/graph/doc/bundles.html

struct VertexData
{
  float probTaken;
	float probEmpty;


};

struct EdgeData
{
	// Nothing?
};

void example0()
{
  // a simple adjaceny list with no extra properties.
  typedef boost::adjacency_list<boost::vecS, boost::vecS,
                                boost::undirectedS,
                                boost::no_property,
                                boost::no_property
                                > MyGraphType;

  MyGraphType G;
  auto v1 = add_vertex(G);
  auto v2 = add_vertex(G);
  auto e = add_edge(v1, v2, G);


  auto vpair = vertices(G);
  for(auto iter=vpair.first; iter!=vpair.second; iter++) {
    std::cout << "vertex " << *iter << std::endl;
  }

  auto epair = edges(G);
  for(auto iter=epair.first; iter!=epair.second; iter++) {
    std::cout << "edge " << source(*iter, G) << " - " << target(*iter, G) << std::endl;
  }
  
}

void example0a()
{

  // a simple graph with bundled properties for vertex and a predefined property
  // for the edge.
  // for a list of predefined properties, you can look here:
  // http://www.boost.org/doc/libs/1_64_0/libs/graph/doc/using_adjacency_list.html#sec:adjacency-list-properties
  typedef boost::adjacency_list<boost::vecS, boost::vecS,
                                boost::undirectedS,
                                VertexData,
                                boost::property<boost::edge_weight_t, float>
                                > MyGraphType;
  MyGraphType G(5);
  G[0].probTaken = .25;

  // first is the edge. second is a bool telling you whether this is a new edge
  // or an existing one.
  auto e = add_edge(1,2,G).first;

  std::cout << "Probability of being taken " << G[0].probTaken << std::endl;
  std::cout << "Probability getter: " << get(&VertexData::probTaken, G)[0] << std::endl;

}


void example1()
{

  typedef boost::adjacency_list<boost::vecS, boost::vecS,
                                boost::undirectedS,
                                VertexData,
                                boost::property<boost::edge_weight_t, double, EdgeData>
                                > MyGraphType;
  MyGraphType G(5);
  G[0].probTaken = .69;

  // first is the edge. second is a bool telling you whether this is a new edge
  // or an existing one.



  std::cout << "probability of being taken:  " << G[0].probTaken << std::endl;
  std::cout << "Probability of being empty:  " << get(&VertexData::probEmpty, G)[0] << std::endl;

}






int
main(int, char *[])
{
  example0();
  example0a();
  example1();
}
