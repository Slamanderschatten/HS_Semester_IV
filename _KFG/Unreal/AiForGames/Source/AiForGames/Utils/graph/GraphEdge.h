#pragma once

template<typename nodeT>
class GraphNode;

template<typename nodeT>
class GraphEdge
{
public:

private:
	GraphNode<nodeT>* nodeA;
	GraphNode<nodeT>* nodeB;


public:
	GraphEdge(GraphNode<nodeT>& nodeA, GraphNode<nodeT>& nodeB)
	{
		this->nodeA = &nodeA;
		this->nodeB = &nodeB;
	}
	GraphNode<nodeT>& GetNodeA()
	{
		return *nodeA;
	}
	GraphNode<nodeT>& GetNodeB()
	{
		return *nodeB;
	}
	GraphNode<nodeT>& GetOtherNode(GraphNode<nodeT>& node)
	{
		if (nodeA == &node)
			return nodeB;
		return nodeA;
	}
	
};
