#include "ResourceManager.h"

ResourceManager* s_instance = nullptr;

ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
}

ResourceManager& ResourceManager::getInstance()
{
	if (s_instance == nullptr)
	{
		s_instance = new ResourceManager();
	}

	return *s_instance;
}

void ResourceManager::cleanup()
{
	if (s_instance)
	{
		delete s_instance;
		s_instance = nullptr;
	}
}

void ResourceManager::addResource(const ResourceNode& resource)
{
	m_resources.insert(std::pair<ResourceNodeUID, std::unique_ptr<ResourceNode>>(resource.getUID(), std::unique_ptr<ResourceNode>(new ResourceNode(resource))));
}


ResourceNode* ResourceManager::getResource(ResourceNodeUID uid)
{
	auto resource = m_resources.find(uid);
	if (resource == m_resources.end())
		return nullptr;

	return resource->second.get();
}