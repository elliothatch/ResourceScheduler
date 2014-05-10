#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <unordered_map>
#include <memory>
#include "ResourceNode.h"
class ResourceManager
{

protected:
	ResourceManager();
public:
	static ResourceManager& getInstance();
	static void cleanup();

	void addResource(const ResourceNode& resource);
	ResourceNode* getResource(ResourceNodeUID uid);

	~ResourceManager();

private:
	std::unordered_map<ResourceNodeUID, std::unique_ptr<ResourceNode>> m_resources;

};

#endif