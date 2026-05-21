#pragma once
#include "NavGraphNode.h"
#include "AiForGames/Utils/graph/Graph.h"

class NavGraph : public Graph<NavGraphNode>
{
public:



public:
	bool addEdgeForSpots(const ANavGraphSpot* spotA, const ANavGraphSpot* spotB);
	
};
