#include "NavGraphNode.h"


NavGraphNode::NavGraphNode(const ANavGraphSpot* spot)
{
	this->spot = spot;
}

const ANavGraphSpot& NavGraphNode::getSpot() const
{
	return *spot;
}
