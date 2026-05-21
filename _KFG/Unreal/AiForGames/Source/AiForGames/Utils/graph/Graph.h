#pragma once
#include "GraphEdge.h"
#include "GraphNode.h"

template<typename nodeT>
class Graph
{
public:
private:
	TArray<GraphEdge<nodeT>> edges;
	TArray<nodeT> nodes;



public:
	void addNode(nodeT node)
	{
		nodes.Add(node);
	}
	void addEdge(nodeT& nodeA, nodeT& nodeB)
	{
		edges.Add(GraphEdge<nodeT>(nodeA, nodeB));
		nodeA->addEdge(edges.back());
		nodeB->addEdge(edges.back());
	}
	void removeEdge(size_t edgeIndex)
	{
		GraphEdge<nodeT>& edge = edges[edgeIndex];
		edge.nodeA->removeEdge(edge);
		edge.nodeB->removeEdge(edge);
		edges.RemoveAt(edgeIndex);
	}
	void removeEdge(nodeT& nodeA, GraphNode<nodeT>& nodeB)
	{
		edges.Remove(&nodeA, &nodeB);
	}
	TArray<nodeT>& getNodes()
	{
		return nodes;
	}

	
};
