#pragma once
#include "NavGraphSpot.h"
#include "AiForGames/Utils/graph/GraphNode.h"

class NavGraphNode : public GraphNode<NavGraphNode>
{
public:

private:
	const ANavGraphSpot* spot = nullptr;


public:
	NavGraphNode(const ANavGraphSpot* spot);
	const ANavGraphSpot& getSpot() const;
	
};
