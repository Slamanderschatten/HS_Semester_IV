#pragma once
#include "GraphEdge.h"

template<typename nodeT>
class GraphNode
{
public:
private:
	TArray<GraphEdge<nodeT>*> edges;


public:
	const TArray<GraphEdge<nodeT>*>& getEdges() const
	{
		return edges;
	}
	void addEdge(GraphEdge<nodeT>& edge)
	{
		if (edges.Contains(&edge))
			return;
		edges.Add(&edge);
	}
	void removeEdge(GraphEdge<nodeT>& edge)
	{
		edges.Remove(&edge);
	}
};
