#include "ResourceNode.h"


ResourceNode::ResourceNode(ResourceNodeUID uid)
:m_uid(uid)
{
}

ResourceNodeUID ResourceNode::getUID() const
{
	return m_uid;
}