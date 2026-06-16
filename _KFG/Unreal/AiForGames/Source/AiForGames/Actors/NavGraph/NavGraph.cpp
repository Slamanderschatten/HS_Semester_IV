#include "NavGraph.h"

bool NavGraph::addEdgeForSpots(const ANavGraphSpot* spotA, const ANavGraphSpot* spotB)
{
	{
		NavGraphNode* nodeA = nullptr;
		NavGraphNode* nodeB = nullptr;
		for (NavGraphNode& node : getNodes())
		{
			if (&node.getSpot() == spotA)
			{
				nodeA = &node;
				if (nodeB != nullptr)
					break;
			}
			else if (&node.getSpot() == spotB)
			{
				nodeB = &node;
				if (nodeA != nullptr)
					break;
			}
		}
		if (nodeA == nullptr || nodeB == nullptr)
			return false;
		addEdge(*nodeA, *nodeB);
		return true;
	}
}
