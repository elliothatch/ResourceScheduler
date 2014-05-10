#ifndef RESOURCENODE_H
#define RESOURCENODE_H

typedef int ResourceNodeUID;

//abstract wrapper for resources, subclass this to make concrete resources
//subclasses should only store weak references to the actual resources, as they may be copied several times
class ResourceNode
{
public:
	ResourceNode(ResourceNodeUID uid);

	ResourceNodeUID getUID() const;

private:
	ResourceNodeUID m_uid;
};

#endif